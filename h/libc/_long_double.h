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

#ifndef _LONG_DOUBLE_H
#define _LONG_DOUBLE_H

#if defined(__x86_64__)
    #include <arch/x86_64/_long_double.h>
#else
    #error "_long_double.h: no long double format for this architecture"
#endif

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
unsigned long long _Long_Double_ReadSignificand(long double x);
unsigned int       _Long_Double_ReadExponent(long double x);
_Bool              _Long_Double_IsNegative(long double x);
long double        _Long_Double_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig);

// Classes
_Long_Double_Class _Long_Double_ReadClass(long double x);
_Bool              _Long_Double_IsNan(long double x);
_Bool              _Long_Double_IsInf(long double x);

// Signs
long double _Long_Double_ClearSign(long double x);
long double _Long_Double_CopySign(long double x, long double y);

// Values
unsigned long long _Long_Double_SplitValue(long double x, int *exp);
long double        _Long_Double_JoinValue(int exp, unsigned long long sig);
long double        _Long_Double_StepValue(long double x, _Long_Double_Step step);
long double        _Long_Double_MakeNan(unsigned long long payload);

#endif // _LONG_DOUBLE_H
