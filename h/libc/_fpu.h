/*
 * C header file for the x86-64 floating-point units and long double's format.
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

#ifndef _FPU_H
#define _FPU_H

// What a function returns when it does not do what it was asked.
#define _FPU_X86_64_FAILED 1

// The exception flags of the x87 and MXCSR, C99's five and all of those.
#define _FPU_X86_64_INVALID   0x01
#define _FPU_X86_64_DIVBYZERO 0x04
#define _FPU_X86_64_OVERFLOW  0x08
#define _FPU_X86_64_UNDERFLOW 0x10
#define _FPU_X86_64_INEXACT   0x20
#define _FPU_X86_64_EXCEPTS   0x3D

// All six of the x87's and MXCSR's flags, the denormal operand's among them.
#define _FPU_X86_64_FLAGS 0x3F

// The rounding directions as the x87 control word holds them, and its field.
#define _FPU_X86_64_TONEAREST  0x0000
#define _FPU_X86_64_DOWNWARD   0x0400
#define _FPU_X86_64_UPWARD     0x0800
#define _FPU_X86_64_TOWARDZERO 0x0C00
#define _FPU_X86_64_ROUND_MASK 0x0C00

// How far above the x87 control word's fields MXCSR holds the same ones.
#define _FPU_X86_64_SSE_ROUND_SHIFT 3
#define _FPU_X86_64_SSE_MASK_SHIFT  7

// The dwords of the x87 environment that hold its last pointers and opcode.
#define _FPU_X86_64_POINTERS 4

// The environment a program starts with, as an environment's address.
#define _FPU_X86_64_DEFAULT_ENV ((const _Fpu_x86_64_Env *) -1)

// A long double's significand bits and its biased exponent's bits.
#define _FPU_X86_64_LDBL_MANT     64
#define _FPU_X86_64_LDBL_EXP_BITS 15

// A long double's least and greatest exponents, one below C's.
#define _FPU_X86_64_LDBL_EXP_MIN (-16382)
#define _FPU_X86_64_LDBL_EXP_MAX 16383

// A long double's least normal, greatest, least subnormal and epsilon.
#define _FPU_X86_64_LDBL_MIN      0x1p-16382L
#define _FPU_X86_64_LDBL_MAX      0xf.fffffffffffffffp+16380L
#define _FPU_X86_64_LDBL_TRUE_MIN 0x1p-16445L
#define _FPU_X86_64_LDBL_EPSILON  0x1p-63L

// The least magnitude of a long double that is always an integer.
#define _FPU_X86_64_LDBL_INTEGRAL 0x1p63L

// The bits of a split significand, its top bit's place, and its top bit.
#define _FPU_SPLIT_BITS  64
#define _FPU_SPLIT_SHIFT 63
#define _FPU_SPLIT_TOP   0x8000000000000000ULL

// What a long double's bits make it.
typedef enum _Fpu_Class _Fpu_Class;
enum _Fpu_Class {
    _FPU_CLASS_ZERO,      // a zero of either sign
    _FPU_CLASS_SUBNORMAL, // below the least normal magnitude
    _FPU_CLASS_NORMAL,    // a normal number
    _FPU_CLASS_INFINITE,  // an infinity
    _FPU_CLASS_NAN,       // not a number
    _FPU_CLASS_COUNT      // the classes
};

// Which way a step moves a magnitude.
typedef enum _Fpu_Step _Fpu_Step;
enum _Fpu_Step {
    _FPU_STEP_UP,  // away from zero
    _FPU_STEP_DOWN // toward zero
};

// Both units' environments, the x87's image and then MXCSR.
typedef struct _Fpu_x86_64_Env _Fpu_x86_64_Env;
struct _Fpu_x86_64_Env {
    unsigned short fe_control;                      // the x87 control word
    unsigned short fe_unused1;                      // reserved
    unsigned short fe_status;                       // the x87 status word
    unsigned short fe_unused2;                      // reserved
    unsigned short fe_tags;                         // the x87 tag word
    unsigned short fe_unused3;                      // reserved
    unsigned int fe_pointers[_FPU_X86_64_POINTERS]; // last opcode and addresses
    unsigned int fe_mxcsr;                          // SSE's control and status
};

// Both units' environments, and a division on SSE.
void  _Fpu_x86_64_StoreEnv(_Fpu_x86_64_Env *env);
void  _Fpu_x86_64_LoadEnv(const _Fpu_x86_64_Env *env);
float _Fpu_x86_64_DivideSingle(float a, float b);

// The flags.
void _Fpu_x86_64_ClearFlags(int flags);
void _Fpu_x86_64_RaiseFlags(int flags);
void _Fpu_x86_64_WriteFlags(int flags, int mask);
int  _Fpu_x86_64_TestFlags(int flags);

// The rounding direction.
int _Fpu_x86_64_ReadRound(void);
int _Fpu_x86_64_WriteRound(int round);

// The whole environment.
void _Fpu_x86_64_HoldEnv(_Fpu_x86_64_Env *env);
void _Fpu_x86_64_WriteEnv(const _Fpu_x86_64_Env *env);

// A long double's fields.
unsigned long long _Fpu_x86_64_ReadSignificand(long double x);
unsigned int       _Fpu_x86_64_ReadExponent(long double x);
_Bool              _Fpu_x86_64_IsNegative(long double x);
long double        _Fpu_x86_64_MakeValue(_Bool negative, unsigned int exp, unsigned long long sig);

// A long double's class.
_Fpu_Class _Fpu_x86_64_ReadClass(long double x);
_Bool      _Fpu_x86_64_IsNan(long double x);
_Bool      _Fpu_x86_64_IsInf(long double x);

// A long double's sign.
long double _Fpu_x86_64_ClearSign(long double x);
long double _Fpu_x86_64_CopySign(long double x, long double y);

// A long double's value, split, joined, stepped or made a NaN.
unsigned long long _Fpu_x86_64_SplitValue(long double x, int *exp);
long double        _Fpu_x86_64_JoinValue(int exp, unsigned long long sig);
long double        _Fpu_x86_64_StepValue(long double x, _Fpu_Step step);
long double        _Fpu_x86_64_MakeNan(unsigned long long payload);

// The x87's sign and exponent word.
unsigned int _Fpu_x86_64_ReadTop(long double x);
long double  _Fpu_x86_64_MakeTop(unsigned int top, unsigned long long sig);

#endif // _FPU_H
