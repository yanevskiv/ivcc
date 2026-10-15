/*
 * C header file for the basic complex functions.
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


#ifndef _BASIC_COMPLEX_H
#define _BASIC_COMPLEX_H

// The parts of a complex value, its real and its imaginary one.
#define _BASIC_COMPLEX_PARTS 2

// The bounds a double's and a long double's division scales its operands
// by, as libgcc's: half the largest value, the least normal one, the
// epsilon and its inverse, and half the largest value times the epsilon.
#define _BASIC_COMPLEX_DBL_BIG      0x1.fffffffffffffp+1022
#define _BASIC_COMPLEX_DBL_MIN      0x1p-1022
#define _BASIC_COMPLEX_DBL_EPS      0x1p-52
#define _BASIC_COMPLEX_DBL_SCALE    0x1p52
#define _BASIC_COMPLEX_DBL_BIG_EPS  0x1.fffffffffffffp+970
#define _BASIC_COMPLEX_LDBL_BIG     0xf.fffffffffffffffp+16379L
#define _BASIC_COMPLEX_LDBL_MIN     0x1p-16382L
#define _BASIC_COMPLEX_LDBL_EPS     0x1p-63L
#define _BASIC_COMPLEX_LDBL_SCALE   0x1p63L
#define _BASIC_COMPLEX_LDBL_BIG_EPS 0xf.fffffffffffffffp+16316L

// The factor that halves the operands of a division near the largest value.
#define _BASIC_COMPLEX_HALF 0.5

// A complex value of each type made of its two parts.
float _Complex       _Basic_Complex_JoinFloat(float x, float y);
double _Complex      _Basic_Complex_JoinDouble(double x, double y);
long double _Complex _Basic_Complex_JoinLDouble(long double x, long double y);

// The parts of a product's or quotient's operands, an infinity boxed to 1
// and a NaN cleared to 0, each keeping its sign.
long double _Basic_Complex_BoxInfinity(long double x);
long double _Basic_Complex_ClearNan(long double x);

// The operands of a division scaled by a power of 2.
void _Basic_Complex_ScaleDouble(double *a, double *b, double *c, double *d, double by);
void _Basic_Complex_ScaleLDouble(long double *a, long double *b, long double *c, long double *d, long double by);

// The quotient of a + ib by c + id, x + iy, both NaN, made the infinity or
// zero G.5.1 asks for where the operands give one.
void _Basic_Complex_RecoverFloat(float a, float b, float c, float d, float *x, float *y);
void _Basic_Complex_RecoverDouble(double a, double b, double c, double d, double *x, double *y);
void _Basic_Complex_RecoverLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y);

// The quotient of a + ib by c + id, x + iy, by Smith's ratio of c and d,
// the operands scaled first where its terms would overflow or underflow.
void _Basic_Complex_DivideDouble(double a, double b, double c, double d, double *x, double *y);
void _Basic_Complex_DivideLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y);

// The compiler's helpers for * and / of two complex values, as libgcc's.
float _Complex       __basic_complex_mulsc3(float a, float b, float c, float d);
double _Complex      __basic_complex_muldc3(double a, double b, double c, double d);
long double _Complex __basic_complex_mulxc3(long double a, long double b, long double c, long double d);
float _Complex       __basic_complex_divsc3(float a, float b, float c, float d);
double _Complex      __basic_complex_divdc3(double a, double b, double c, double d);
long double _Complex __basic_complex_divxc3(long double a, long double b, long double c, long double d);

#endif // _BASIC_COMPLEX_H
