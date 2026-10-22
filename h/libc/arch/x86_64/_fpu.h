/*
 * C header file for the x86-64 floating-point units' controls and flags.
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

#ifndef _ARCH_X86_64_FPU_H
#define _ARCH_X86_64_FPU_H

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
#define _FPU_X86_64_X87_POINTERS 4

// The environment a program starts with, as an environment's address.
#define _FPU_X86_64_DEFAULT_ENV ((const _Fpu_x86_64_Env *) -1)

// Both units' environments, the x87's image and then MXCSR.
typedef struct _Fpu_x86_64_Env _Fpu_x86_64_Env;
struct _Fpu_x86_64_Env {
    unsigned short fe_control;                    // the x87 control word
    unsigned short fe_unused1;                    // reserved
    unsigned short fe_status;                     // the x87 status word
    unsigned short fe_unused2;                    // reserved
    unsigned short fe_tags;                       // the x87 tag word
    unsigned short fe_unused3;                    // reserved
    unsigned int fe_pointers[_FPU_X86_64_X87_POINTERS];  // the last opcode and addresses
    unsigned int fe_mxcsr;                        // SSE's control and status
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

#endif // _ARCH_X86_64_FPU_H
