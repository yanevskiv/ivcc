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

#ifndef _ARCH_X86_64_LONG_DOUBLE_H
#define _ARCH_X86_64_LONG_DOUBLE_H

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

// The x87's sign and exponent word.
unsigned int _Long_Double_x86_64_ReadTop(long double x);
long double  _Long_Double_x86_64_MakeTop(unsigned int top, unsigned long long sig);

#endif // _ARCH_X86_64_LONG_DOUBLE_H
