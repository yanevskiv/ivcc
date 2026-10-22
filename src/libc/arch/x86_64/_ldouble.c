/*
 * C source file for long double's fields on x86-64.
 *
 * Copyright (C) 2026 Ivan Janevski
 *
 * ivcc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * ivcc is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with ivcc; see
 * the files LICENSE and COPYING.RUNTIME respectively.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

// Module header.
#include <_ldouble.h>

// The loop that copies a value's bytes.
#include <_str.h>

// The bytes of the x87's significand and of its sign and exponent word.
#define _LDOUBLE_X86_64_SIGNIFICAND 0
#define _LDOUBLE_X86_64_TOP         8

// The x87's integer bit, its fraction, and every bit of its significand.
#define _LDOUBLE_X86_64_INT_BIT   0x8000000000000000ULL
#define _LDOUBLE_X86_64_FRAC_MASK 0x7FFFFFFFFFFFFFFFULL
#define _LDOUBLE_X86_64_ALL_BITS  (~0ULL)

// The sign bit of the x87's top word and its exponent of every bit set.
#define _LDOUBLE_X86_64_SIGN     0x8000U
#define _LDOUBLE_X86_64_EXP_ONES 0x7FFFU

// The significand of the x87's quiet NaN without a payload.
#define _LDOUBLE_X86_64_QUIET 0xC000000000000000ULL

// Read x's significand, its integer bit among its bits.
unsigned long long _Ldouble_ReadSignificand(long double x)
{
    unsigned long long sig;

    _Str_CopyBytes(&sig, (unsigned char *) &x + _LDOUBLE_X86_64_SIGNIFICAND, sizeof(sig));
    return sig;
}

// Read x's biased exponent.
unsigned int _Ldouble_ReadExponent(long double x)
{
    return _Ldouble_x86_64_ReadTop(x) & _LDOUBLE_X86_64_EXP_ONES;
}

// Return whether x's sign is negative.
_Bool _Ldouble_IsNegative(long double x)
{
    return (_Ldouble_x86_64_ReadTop(x) & _LDOUBLE_X86_64_SIGN) != 0;
}

// Make a long double of its sign, its biased exponent and its significand.
long double _Ldouble_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig)
{
    return _Ldouble_x86_64_MakeTop(negative ? exp | _LDOUBLE_X86_64_SIGN : exp, sig);
}

// Read x's class, the x87's refused encodings as glibc takes them.
_Ldouble_Class _Ldouble_ReadClass(long double x)
{
    unsigned int exp = _Ldouble_ReadExponent(x);
    unsigned long long sig = _Ldouble_ReadSignificand(x);

    if (exp == 0 && (sig & _LDOUBLE_X86_64_INT_BIT) != 0) {
        return _LDOUBLE_CLASS_NORMAL;
    }
    if (exp == 0) {
        return sig != 0 ? _LDOUBLE_CLASS_SUBNORMAL : _LDOUBLE_CLASS_ZERO;
    }
    if ((sig & _LDOUBLE_X86_64_INT_BIT) == 0) {
        return _LDOUBLE_CLASS_NAN;
    }
    if (exp == _LDOUBLE_X86_64_EXP_ONES) {
        return (sig & _LDOUBLE_X86_64_FRAC_MASK) != 0 ? _LDOUBLE_CLASS_NAN : _LDOUBLE_CLASS_INFINITE;
    }
    return _LDOUBLE_CLASS_NORMAL;
}

// Return whether x is a NaN.
_Bool _Ldouble_IsNan(long double x)
{
    return _Ldouble_ReadClass(x) == _LDOUBLE_CLASS_NAN;
}

// Return whether x is an infinity.
_Bool _Ldouble_IsInf(long double x)
{
    return _Ldouble_ReadClass(x) == _LDOUBLE_CLASS_INFINITE;
}

// Clear x's sign.
long double _Ldouble_ClearSign(long double x)
{
    return _Ldouble_x86_64_MakeTop(_Ldouble_x86_64_ReadTop(x) & ~_LDOUBLE_X86_64_SIGN, _Ldouble_ReadSignificand(x));
}

// Copy y's sign to x.
long double _Ldouble_CopySign(long double x, long double y)
{
    return _Ldouble_x86_64_MakeTop((_Ldouble_x86_64_ReadTop(x) & ~_LDOUBLE_X86_64_SIGN) | (_Ldouble_x86_64_ReadTop(y) & _LDOUBLE_X86_64_SIGN), _Ldouble_ReadSignificand(x));
}

// Split a long double into its significand split at its top and its exponent.
unsigned long long _Ldouble_SplitValue(long double x, int *exp)
{
    unsigned long long sig = _Ldouble_ReadSignificand(x);
    unsigned int biased = _Ldouble_ReadExponent(x);

    *exp = biased == 0 ? _LDOUBLE_EXP_MIN : (int) biased - _LDOUBLE_EXP_MAX;
    for (; (sig & _LDOUBLE_X86_64_INT_BIT) == 0; sig <<= 1) {
        (*exp)--;
    }
    return sig;
}

// Join an exponent and a significand split at its top into a long double.
long double _Ldouble_JoinValue(int exp, unsigned long long sig)
{
    int shift;
    unsigned long long bits = sig;

    if (bits == 0) {
        return 0.0L;
    }
    for (; (bits & _LDOUBLE_X86_64_INT_BIT) == 0; bits <<= 1) {
        exp--;
    }
    if (exp >= _LDOUBLE_EXP_MIN) {
        return _Ldouble_x86_64_MakeTop((unsigned int) (exp + _LDOUBLE_EXP_MAX), bits);
    }
    shift = _LDOUBLE_EXP_MIN - exp;
    return _Ldouble_x86_64_MakeTop(0, shift > _LDOUBLE_SPLIT_SHIFT ? 0 : bits >> shift);
}

// Step a long double's magnitude to the next value up or down.
long double _Ldouble_StepValue(long double x, _Ldouble_Step step)
{
    unsigned int top = _Ldouble_x86_64_ReadTop(x);
    unsigned long long sig = _Ldouble_ReadSignificand(x);

    if (step == _LDOUBLE_STEP_UP && sig == _LDOUBLE_X86_64_ALL_BITS) {
        sig = _LDOUBLE_X86_64_INT_BIT;
        top++;
    } else if (step == _LDOUBLE_STEP_UP) {
        sig++;
    } else if ((top & _LDOUBLE_X86_64_EXP_ONES) != 0 && sig == _LDOUBLE_X86_64_INT_BIT) {
        top--;
        sig = (top & _LDOUBLE_X86_64_EXP_ONES) == 0 ? _LDOUBLE_X86_64_FRAC_MASK : _LDOUBLE_X86_64_ALL_BITS;
    } else {
        sig--;
    }
    if ((top & _LDOUBLE_X86_64_EXP_ONES) == 0 && sig >= _LDOUBLE_X86_64_INT_BIT) {
        top++;
    }
    return _Ldouble_x86_64_MakeTop(top, sig);
}

// Make a quiet NaN of a clear sign and the payload's low bits.
long double _Ldouble_MakeNan(unsigned long long payload)
{
    return _Ldouble_x86_64_MakeTop(_LDOUBLE_X86_64_EXP_ONES, _LDOUBLE_X86_64_QUIET | (payload & _LDOUBLE_X86_64_FRAC_MASK));
}

// Read the x87's sign and biased exponent word.
unsigned int _Ldouble_x86_64_ReadTop(long double x)
{
    unsigned short top;

    _Str_CopyBytes(&top, (unsigned char *) &x + _LDOUBLE_X86_64_TOP, sizeof(top));
    return top;
}

// Make a long double of the x87's sign and exponent word and its significand.
long double _Ldouble_x86_64_MakeTop(unsigned int top, unsigned long long sig)
{
    long double x = 0.0L;
    unsigned long long low = sig;
    unsigned short high = (unsigned short) top;

    _Str_CopyBytes((unsigned char *) &x + _LDOUBLE_X86_64_SIGNIFICAND, &low, sizeof(low));
    _Str_CopyBytes((unsigned char *) &x + _LDOUBLE_X86_64_TOP, &high, sizeof(high));
    return x;
}
