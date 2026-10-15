/*
 * C header file for complex arithmetic.
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


#ifndef _COMPLEX_H
#define _COMPLEX_H

// The compiler's helpers for * and / of two complex values, libgcc's names
// [C99:G.5.1p4]: * and /, an infinite operand giving an infinite or zero result
// [C99:G.5.1p5]: * and / of complex operands, spurious exceptions allowed
float _Complex       __mulsc3(float a, float b, float c, float d);
double _Complex      __muldc3(double a, double b, double c, double d);
long double _Complex __mulxc3(long double a, long double b, long double c, long double d);
float _Complex       __divsc3(float a, float b, float c, float d);
double _Complex      __divdc3(double a, double b, double c, double d);
long double _Complex __divxc3(long double a, long double b, long double c, long double d);

#endif // _COMPLEX_H
