/*
 * C header file for the floating-point units, picked by architecture.
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

#if defined(__x86_64__)
    #include <arch/x86_64/_fpu.h>
    #define _FPU_FAILED      _FPU_X86_64_FAILED
    #define _FPU_INVALID     _FPU_X86_64_INVALID
    #define _FPU_DIVBYZERO   _FPU_X86_64_DIVBYZERO
    #define _FPU_OVERFLOW    _FPU_X86_64_OVERFLOW
    #define _FPU_UNDERFLOW   _FPU_X86_64_UNDERFLOW
    #define _FPU_INEXACT     _FPU_X86_64_INEXACT
    #define _FPU_EXCEPTS     _FPU_X86_64_EXCEPTS
    #define _FPU_TONEAREST   _FPU_X86_64_TONEAREST
    #define _FPU_DOWNWARD    _FPU_X86_64_DOWNWARD
    #define _FPU_UPWARD      _FPU_X86_64_UPWARD
    #define _FPU_TOWARDZERO  _FPU_X86_64_TOWARDZERO
    #define _FPU_ROUND_MASK  _FPU_X86_64_ROUND_MASK
    #define _FPU_DEFAULT_ENV _FPU_X86_64_DEFAULT_ENV
    #define _Fpu_Env         _Fpu_x86_64_Env
    #define _Fpu_StoreEnv    _Fpu_x86_64_StoreEnv
    #define _Fpu_ClearFlags  _Fpu_x86_64_ClearFlags
    #define _Fpu_RaiseFlags  _Fpu_x86_64_RaiseFlags
    #define _Fpu_WriteFlags  _Fpu_x86_64_WriteFlags
    #define _Fpu_TestFlags   _Fpu_x86_64_TestFlags
    #define _Fpu_ReadRound   _Fpu_x86_64_ReadRound
    #define _Fpu_WriteRound  _Fpu_x86_64_WriteRound
    #define _Fpu_HoldEnv     _Fpu_x86_64_HoldEnv
    #define _Fpu_WriteEnv    _Fpu_x86_64_WriteEnv
#else
    #error "_fpu.h: no floating-point unit for this architecture"
#endif

#endif // _FPU_H
