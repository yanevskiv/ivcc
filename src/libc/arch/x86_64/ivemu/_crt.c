/*
 * C source file for the startup on x86-64 under ivemu.
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
#include <_crt.h>

// The ivemu machine's halt register.
#define _CRT_X86_64_IVEMU_HALT "0x10000008"

// Call main, then halt the machine with its status.
__asm__(
    "  .text\n"
    "  .globl _start\n"
    "_start:\n"
    "  call main\n"
    "  mov $" _CRT_X86_64_IVEMU_HALT ", %rdi\n"
    "  mov %al, (%rdi)\n"
    ".Lhang:\n"
    "  jmp .Lhang\n"
);
