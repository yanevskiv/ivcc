/*
 * C header file for long double's fields on x86-64.
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

#ifndef _LONG_DOUBLE_H
#define _LONG_DOUBLE_H

// A long double's significand bits and its biased exponent's bits.
#define _LONG_DOUBLE_X86_64_MANT     64
#define _LONG_DOUBLE_X86_64_EXP_BITS 15

// A long double's least and greatest exponents, one below C's.
#define _LONG_DOUBLE_X86_64_EXP_MIN (-16382)
#define _LONG_DOUBLE_X86_64_EXP_MAX 16383

// A long double's least normal, greatest, least subnormal and epsilon.
#define _LONG_DOUBLE_X86_64_MIN      0x1p-16382L
#define _LONG_DOUBLE_X86_64_MAX      0xf.fffffffffffffffp+16380L
#define _LONG_DOUBLE_X86_64_TRUE_MIN 0x1p-16445L
#define _LONG_DOUBLE_X86_64_EPSILON  0x1p-63L

// The least magnitude of a long double that is always an integer.
#define _LONG_DOUBLE_X86_64_INTEGRAL 0x1p63L

// The bits of a split significand, its top bit's place, and its top bit.
#define _LONG_DOUBLE_SPLIT_BITS  64
#define _LONG_DOUBLE_SPLIT_SHIFT 63
#define _LONG_DOUBLE_SPLIT_TOP   0x8000000000000000ULL

// What a long double's bits make it.
typedef enum _Long_Double_Class _Long_Double_Class;
enum _Long_Double_Class {
    _LONG_DOUBLE_CLASS_ZERO,      // a zero of either sign
    _LONG_DOUBLE_CLASS_SUBNORMAL, // below the least normal magnitude
    _LONG_DOUBLE_CLASS_NORMAL,    // a normal number
    _LONG_DOUBLE_CLASS_INFINITE,  // an infinity
    _LONG_DOUBLE_CLASS_NAN,       // not a number
    _LONG_DOUBLE_CLASS_COUNT      // the classes
};

// Which way a step moves a magnitude.
typedef enum _Long_Double_Step _Long_Double_Step;
enum _Long_Double_Step {
    _LONG_DOUBLE_STEP_UP,  // away from zero
    _LONG_DOUBLE_STEP_DOWN // toward zero
};

// Fields
unsigned long long _Long_Double_x86_64_ReadSignificand(long double x);
unsigned int       _Long_Double_x86_64_ReadExponent(long double x);
_Bool              _Long_Double_x86_64_IsNegative(long double x);
long double        _Long_Double_x86_64_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig);

// Classes
_Long_Double_Class _Long_Double_x86_64_ReadClass(long double x);
_Bool              _Long_Double_x86_64_IsNan(long double x);
_Bool              _Long_Double_x86_64_IsInf(long double x);

// Signs
long double _Long_Double_x86_64_ClearSign(long double x);
long double _Long_Double_x86_64_CopySign(long double x, long double y);

// Values
unsigned long long _Long_Double_x86_64_SplitValue(long double x, int *exp);
long double        _Long_Double_x86_64_JoinValue(int exp, unsigned long long sig);
long double        _Long_Double_x86_64_StepValue(long double x, _Long_Double_Step step);
long double        _Long_Double_x86_64_MakeNan(unsigned long long payload);

// The x87's sign and exponent word.
unsigned int _Long_Double_x86_64_ReadTop(long double x);
long double  _Long_Double_x86_64_MakeTop(unsigned int top, unsigned long long sig);

#endif // _LONG_DOUBLE_H
