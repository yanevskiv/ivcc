/*
 * C header file for the characteristics of floating types on x86-64.
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

#ifndef _ARCH_X86_64_FLOAT_H
#define _ARCH_X86_64_FLOAT_H

// The x87's extended format as long double's characteristics.
#define _FLOAT_LDBL_MANT_DIG   64
#define _FLOAT_DECIMAL_DIG     21
#define _FLOAT_LDBL_DIG        18
#define _FLOAT_LDBL_MIN_EXP    (-16381)
#define _FLOAT_LDBL_MIN_10_EXP (-4931)
#define _FLOAT_LDBL_MAX_EXP    16384
#define _FLOAT_LDBL_MAX_10_EXP 4932
#define _FLOAT_LDBL_MAX        1.18973149535723176502126385303097021e+4932L
#define _FLOAT_LDBL_EPSILON    1.08420217248550443400745280086994171e-19L
#define _FLOAT_LDBL_MIN        3.36210314311209350626267781732175260e-4932L

#endif // _ARCH_X86_64_FLOAT_H
