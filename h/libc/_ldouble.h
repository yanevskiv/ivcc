/*
 * C header file for long double's fields, picked by architecture.
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

#ifndef _LDOUBLE_H
#define _LDOUBLE_H

#if defined(__x86_64__)
    #include <arch/x86_64/_ldouble.h>
#else
    #error "_ldouble.h: no long double format for this architecture"
#endif

// The bits of a split significand, its top bit's place, and its top bit.
#define _LDOUBLE_SPLIT_BITS  64
#define _LDOUBLE_SPLIT_SHIFT 63
#define _LDOUBLE_SPLIT_TOP   0x8000000000000000ULL

// What a long double's bits make it.
typedef enum _Ldouble_Class _Ldouble_Class;
enum _Ldouble_Class {
    _LDOUBLE_CLASS_ZERO,      // a zero of either sign
    _LDOUBLE_CLASS_SUBNORMAL, // below the least normal magnitude
    _LDOUBLE_CLASS_NORMAL,    // a normal number
    _LDOUBLE_CLASS_INFINITE,  // an infinity
    _LDOUBLE_CLASS_NAN,       // not a number
    _LDOUBLE_CLASS_COUNT      // the classes
};

// Which way a step moves a magnitude.
typedef enum _Ldouble_Step _Ldouble_Step;
enum _Ldouble_Step {
    _LDOUBLE_STEP_UP,  // away from zero
    _LDOUBLE_STEP_DOWN // toward zero
};

// Fields
unsigned long long _Ldouble_ReadSignificand(long double x);
unsigned int       _Ldouble_ReadExponent(long double x);
_Bool              _Ldouble_IsNegative(long double x);
long double        _Ldouble_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig);

// Classes
_Ldouble_Class _Ldouble_ReadClass(long double x);
_Bool          _Ldouble_IsNan(long double x);
_Bool          _Ldouble_IsInf(long double x);

// Signs
long double _Ldouble_ClearSign(long double x);
long double _Ldouble_CopySign(long double x, long double y);

// Values
unsigned long long _Ldouble_SplitValue(long double x, int *exp);
long double        _Ldouble_JoinValue(int exp, unsigned long long sig);
long double        _Ldouble_StepValue(long double x, _Ldouble_Step step);
long double        _Ldouble_MakeNan(unsigned long long payload);

#endif // _LDOUBLE_H
