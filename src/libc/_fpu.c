/*
 * C source file for the x86-64 floating-point units' controls and flags.
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
#include <_fpu.h>

// The loop that copies a value's bytes.
#include <_str.h>

// The control words a program starts with: all masked, to nearest, 64 bits.
#define _FPU_X86_64_DEFAULT_CONTROL 0x037F
#define _FPU_X86_64_DEFAULT_MXCSR   0x1F80

// The operands _Fpu_x86_64_RaiseFlags divides, an exception for each quotient.
#define _FPU_X86_64_ZERO      0.0f
#define _FPU_X86_64_ONE       1.0f
#define _FPU_X86_64_THREE     3.0f
#define _FPU_X86_64_FLOAT_MAX 0x1.fffffep127f
#define _FPU_X86_64_FLOAT_MIN 0x1p-126f

// The bytes of the x87's significand and of its sign and exponent word.
#define _FPU_X86_64_LDBL_SIGNIFICAND 0
#define _FPU_X86_64_LDBL_TOP         8

// The x87's integer bit, its fraction, and every bit of its significand.
#define _FPU_X86_64_LDBL_INT_BIT   0x8000000000000000ULL
#define _FPU_X86_64_LDBL_FRAC_MASK 0x7FFFFFFFFFFFFFFFULL
#define _FPU_X86_64_LDBL_ALL_BITS  (~0ULL)

// The sign bit of the x87's top word and its exponent of every bit set.
#define _FPU_X86_64_LDBL_SIGN     0x8000U
#define _FPU_X86_64_LDBL_EXP_ONES 0x7FFFU

// The significand of the x87's quiet NaN without a payload.
#define _FPU_X86_64_LDBL_QUIET 0xC000000000000000ULL

#ifdef __x86_64__
// Store both units' environments in env, the x87's masks left as they were.
__asm__(
    "  .text\n"
    "  .globl _Fpu_x86_64_StoreEnv\n"
    "_Fpu_x86_64_StoreEnv:\n"
    "  fnstenv (%rdi)\n"
    "  fldenv (%rdi)\n"
    "  stmxcsr 28(%rdi)\n"
    "  ret\n"
);

// Load both units' environments from env.
__asm__(
    "  .text\n"
    "  .globl _Fpu_x86_64_LoadEnv\n"
    "_Fpu_x86_64_LoadEnv:\n"
    "  fldenv (%rdi)\n"
    "  ldmxcsr 28(%rdi)\n"
    "  ret\n"
);

// Return a divided by b on SSE, raising what the division raises.
__asm__(
    "  .text\n"
    "  .globl _Fpu_x86_64_DivideSingle\n"
    "_Fpu_x86_64_DivideSingle:\n"
    "  divss %xmm1, %xmm0\n"
    "  ret\n"
);
#else
    #error "_fpu.c: no floating-point environment for this architecture"
#endif

// Clear the flags of flags in both units.
void _Fpu_x86_64_ClearFlags(int flags)
{
    _Fpu_x86_64_Env env;

    _Fpu_x86_64_StoreEnv(&env);
    env.fe_status &= (unsigned short) ~(flags & _FPU_X86_64_EXCEPTS);
    env.fe_mxcsr &= (unsigned int) ~(flags & _FPU_X86_64_EXCEPTS);
    _Fpu_x86_64_LoadEnv(&env);
}

// Raise each exception of flags by a division that raises it.
void _Fpu_x86_64_RaiseFlags(int flags)
{
    if (flags & _FPU_X86_64_INVALID) {
        _Fpu_x86_64_DivideSingle(_FPU_X86_64_ZERO, _FPU_X86_64_ZERO);
    }
    if (flags & _FPU_X86_64_DIVBYZERO) {
        _Fpu_x86_64_DivideSingle(_FPU_X86_64_ONE, _FPU_X86_64_ZERO);
    }
    if (flags & _FPU_X86_64_OVERFLOW) {
        _Fpu_x86_64_DivideSingle(_FPU_X86_64_FLOAT_MAX, _FPU_X86_64_FLOAT_MIN);
    }
    if (flags & _FPU_X86_64_UNDERFLOW) {
        _Fpu_x86_64_DivideSingle(_FPU_X86_64_FLOAT_MIN, _FPU_X86_64_FLOAT_MAX);
    }
    if (flags & _FPU_X86_64_INEXACT) {
        _Fpu_x86_64_DivideSingle(_FPU_X86_64_ONE, _FPU_X86_64_THREE);
    }
}

// Write the flags of mask in both units as flags holds them.
void _Fpu_x86_64_WriteFlags(int flags, int mask)
{
    _Fpu_x86_64_Env env;

    mask &= _FPU_X86_64_EXCEPTS;
    _Fpu_x86_64_StoreEnv(&env);
    env.fe_status = (unsigned short) ((env.fe_status & ~mask) | (flags & mask));
    env.fe_mxcsr = (env.fe_mxcsr & (unsigned int) ~mask) | (unsigned int) (flags & mask);
    _Fpu_x86_64_LoadEnv(&env);
}

// Return which flags of flags either unit has set.
int _Fpu_x86_64_TestFlags(int flags)
{
    _Fpu_x86_64_Env env;

    _Fpu_x86_64_StoreEnv(&env);
    return (int) ((env.fe_status | env.fe_mxcsr) & (unsigned int) (flags & _FPU_X86_64_EXCEPTS));
}

// Read the rounding direction, the x87's, which SSE's is kept to.
int _Fpu_x86_64_ReadRound(void)
{
    _Fpu_x86_64_Env env;

    _Fpu_x86_64_StoreEnv(&env);
    return env.fe_control & _FPU_X86_64_ROUND_MASK;
}

// Write both units' rounding direction, if round names one.
int _Fpu_x86_64_WriteRound(int round)
{
    _Fpu_x86_64_Env env;

    if (round & ~_FPU_X86_64_ROUND_MASK) {
        return _FPU_X86_64_FAILED;
    }
    _Fpu_x86_64_StoreEnv(&env);
    env.fe_control = (unsigned short) ((env.fe_control & ~_FPU_X86_64_ROUND_MASK) | round);
    env.fe_mxcsr &= (unsigned int) ~(_FPU_X86_64_ROUND_MASK << _FPU_X86_64_SSE_ROUND_SHIFT);
    env.fe_mxcsr |= (unsigned int) round << _FPU_X86_64_SSE_ROUND_SHIFT;
    _Fpu_x86_64_LoadEnv(&env);
    return 0;
}

// Store the environment in env, then clear the flags and mask every exception.
void _Fpu_x86_64_HoldEnv(_Fpu_x86_64_Env *env)
{
    _Fpu_x86_64_Env held;

    _Fpu_x86_64_StoreEnv(env);
    held = *env;
    held.fe_control |= _FPU_X86_64_FLAGS;
    held.fe_status &= (unsigned short) ~_FPU_X86_64_FLAGS;
    held.fe_mxcsr |= _FPU_X86_64_FLAGS << _FPU_X86_64_SSE_MASK_SHIFT;
    held.fe_mxcsr &= (unsigned int) ~_FPU_X86_64_FLAGS;
    _Fpu_x86_64_LoadEnv(&held);
}

// Write both units' controls and flags from env, the x87's stack kept.
void _Fpu_x86_64_WriteEnv(const _Fpu_x86_64_Env *env)
{
    _Fpu_x86_64_Env now;

    _Fpu_x86_64_StoreEnv(&now);
    now.fe_status &= (unsigned short) ~_FPU_X86_64_FLAGS;
    if (env == _FPU_X86_64_DEFAULT_ENV) {
        now.fe_control = _FPU_X86_64_DEFAULT_CONTROL;
        now.fe_mxcsr = _FPU_X86_64_DEFAULT_MXCSR;
    } else {
        now.fe_control = env->fe_control;
        now.fe_status |= env->fe_status & _FPU_X86_64_FLAGS;
        now.fe_mxcsr = env->fe_mxcsr;
    }
    _Fpu_x86_64_LoadEnv(&now);
}

// Read x's significand, its integer bit among its bits.
unsigned long long _Fpu_x86_64_ReadSignificand(long double x)
{
    unsigned long long sig;

    _Str_CopyBytes(&sig, (unsigned char *) &x + _FPU_X86_64_LDBL_SIGNIFICAND, sizeof(sig));
    return sig;
}

// Read x's biased exponent.
unsigned int _Fpu_x86_64_ReadExponent(long double x)
{
    return _Fpu_x86_64_ReadTop(x) & _FPU_X86_64_LDBL_EXP_ONES;
}

// Return whether x's sign is negative.
_Bool _Fpu_x86_64_IsNegative(long double x)
{
    return (_Fpu_x86_64_ReadTop(x) & _FPU_X86_64_LDBL_SIGN) != 0;
}

// Make a long double of its sign, its biased exponent and its significand.
long double _Fpu_x86_64_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig)
{
    return _Fpu_x86_64_MakeTop(negative ? exp | _FPU_X86_64_LDBL_SIGN : exp, sig);
}

// Read x's class, the x87's refused encodings as glibc takes them.
_Fpu_Class _Fpu_x86_64_ReadClass(long double x)
{
    unsigned int exp = _Fpu_x86_64_ReadExponent(x);
    unsigned long long sig = _Fpu_x86_64_ReadSignificand(x);

    if (exp == 0 && (sig & _FPU_X86_64_LDBL_INT_BIT) != 0) {
        return _FPU_CLASS_NORMAL;
    }
    if (exp == 0) {
        return sig != 0 ? _FPU_CLASS_SUBNORMAL : _FPU_CLASS_ZERO;
    }
    if ((sig & _FPU_X86_64_LDBL_INT_BIT) == 0) {
        return _FPU_CLASS_NAN;
    }
    if (exp == _FPU_X86_64_LDBL_EXP_ONES) {
        return (sig & _FPU_X86_64_LDBL_FRAC_MASK) != 0 ? _FPU_CLASS_NAN : _FPU_CLASS_INFINITE;
    }
    return _FPU_CLASS_NORMAL;
}

// Return whether x is a NaN.
_Bool _Fpu_x86_64_IsNan(long double x)
{
    return _Fpu_x86_64_ReadClass(x) == _FPU_CLASS_NAN;
}

// Return whether x is an infinity.
_Bool _Fpu_x86_64_IsInf(long double x)
{
    return _Fpu_x86_64_ReadClass(x) == _FPU_CLASS_INFINITE;
}

// Clear x's sign.
long double _Fpu_x86_64_ClearSign(long double x)
{
    return _Fpu_x86_64_MakeTop(_Fpu_x86_64_ReadTop(x) & ~_FPU_X86_64_LDBL_SIGN, _Fpu_x86_64_ReadSignificand(x));
}

// Copy y's sign to x.
long double _Fpu_x86_64_CopySign(long double x, long double y)
{
    return _Fpu_x86_64_MakeTop((_Fpu_x86_64_ReadTop(x) & ~_FPU_X86_64_LDBL_SIGN) | (_Fpu_x86_64_ReadTop(y) & _FPU_X86_64_LDBL_SIGN), _Fpu_x86_64_ReadSignificand(x));
}

// Split a long double into its significand split at its top and its exponent.
unsigned long long _Fpu_x86_64_SplitValue(long double x, int *exp)
{
    unsigned long long sig = _Fpu_x86_64_ReadSignificand(x);
    unsigned int biased = _Fpu_x86_64_ReadExponent(x);

    *exp = biased == 0 ? _FPU_X86_64_LDBL_EXP_MIN : (int) biased - _FPU_X86_64_LDBL_EXP_MAX;
    for (; (sig & _FPU_X86_64_LDBL_INT_BIT) == 0; sig <<= 1) {
        (*exp)--;
    }
    return sig;
}

// Join an exponent and a significand split at its top into a long double.
long double _Fpu_x86_64_JoinValue(int exp, unsigned long long sig)
{
    int shift;
    unsigned long long bits = sig;

    if (bits == 0) {
        return 0.0L;
    }
    for (; (bits & _FPU_X86_64_LDBL_INT_BIT) == 0; bits <<= 1) {
        exp--;
    }
    if (exp >= _FPU_X86_64_LDBL_EXP_MIN) {
        return _Fpu_x86_64_MakeTop((unsigned int) (exp + _FPU_X86_64_LDBL_EXP_MAX), bits);
    }
    shift = _FPU_X86_64_LDBL_EXP_MIN - exp;
    return _Fpu_x86_64_MakeTop(0, shift > _FPU_SPLIT_SHIFT ? 0 : bits >> shift);
}

// Step a long double's magnitude to the next value up or down.
long double _Fpu_x86_64_StepValue(long double x, _Fpu_Step step)
{
    unsigned int top = _Fpu_x86_64_ReadTop(x);
    unsigned long long sig = _Fpu_x86_64_ReadSignificand(x);

    if (step == _FPU_STEP_UP && sig == _FPU_X86_64_LDBL_ALL_BITS) {
        sig = _FPU_X86_64_LDBL_INT_BIT;
        top++;
    } else if (step == _FPU_STEP_UP) {
        sig++;
    } else if ((top & _FPU_X86_64_LDBL_EXP_ONES) != 0 && sig == _FPU_X86_64_LDBL_INT_BIT) {
        top--;
        sig = (top & _FPU_X86_64_LDBL_EXP_ONES) == 0 ? _FPU_X86_64_LDBL_FRAC_MASK : _FPU_X86_64_LDBL_ALL_BITS;
    } else {
        sig--;
    }
    if ((top & _FPU_X86_64_LDBL_EXP_ONES) == 0 && sig >= _FPU_X86_64_LDBL_INT_BIT) {
        top++;
    }
    return _Fpu_x86_64_MakeTop(top, sig);
}

// Make a quiet NaN of a clear sign and the payload's low bits.
long double _Fpu_x86_64_MakeNan(unsigned long long payload)
{
    return _Fpu_x86_64_MakeTop(_FPU_X86_64_LDBL_EXP_ONES, _FPU_X86_64_LDBL_QUIET | (payload & _FPU_X86_64_LDBL_FRAC_MASK));
}

// Read the x87's sign and biased exponent word.
unsigned int _Fpu_x86_64_ReadTop(long double x)
{
    unsigned short top;

    _Str_CopyBytes(&top, (unsigned char *) &x + _FPU_X86_64_LDBL_TOP, sizeof(top));
    return top;
}

// Make a long double of the x87's sign and exponent word and its significand.
long double _Fpu_x86_64_MakeTop(unsigned int top, unsigned long long sig)
{
    long double x = 0.0L;
    unsigned long long low = sig;
    unsigned short high = (unsigned short) top;

    _Str_CopyBytes((unsigned char *) &x + _FPU_X86_64_LDBL_SIGNIFICAND, &low, sizeof(low));
    _Str_CopyBytes((unsigned char *) &x + _FPU_X86_64_LDBL_TOP, &high, sizeof(high));
    return x;
}
