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

// The control words a program starts with: all masked, to nearest, 64 bits.
#define _FPU_X86_64_DEFAULT_CONTROL 0x037F
#define _FPU_X86_64_DEFAULT_MXCSR   0x1F80

// The operands _Fpu_x86_64_RaiseFlags divides, an exception for each quotient.
#define _FPU_X86_64_ZERO      0.0f
#define _FPU_X86_64_ONE       1.0f
#define _FPU_X86_64_THREE     3.0f
#define _FPU_X86_64_FLOAT_MAX 0x1.fffffep127f
#define _FPU_X86_64_FLOAT_MIN 0x1p-126f

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
