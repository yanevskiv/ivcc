/*
 * C source file for the system layer's entry to the kernel on x86-64 Linux.
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
#include <_sys.h>

// Linux's rt_sigreturn number on x86-64, as the restorer's assembly writes it.
#define _SYS_X86_64_LINUX_NR_RT_SIGRETURN "15"

// Invoke a syscall by its number, with six arguments.
__asm__(
    "  .text\n"
    "  .globl _Sys_InvokeSyscall\n"
    "_Sys_InvokeSyscall:\n"
    "  mov %rdi, %rax\n"
    "  mov %rsi, %rdi\n"
    "  mov %rdx, %rsi\n"
    "  mov %rcx, %rdx\n"
    "  mov %r8, %r10\n"
    "  mov %r9, %r8\n"
    "  mov 8(%rsp), %r9\n"
    "  syscall\n"
    "  ret\n"
);

// Invoke rt_sigreturn to return from a handler to what the signal interrupted.
__asm__(
    "  .text\n"
    "  .globl _Sys_InvokeRtSigreturn\n"
    "_Sys_InvokeRtSigreturn:\n"
    "  mov $" _SYS_X86_64_LINUX_NR_RT_SIGRETURN ", %rax\n"
    "  syscall\n"
);
