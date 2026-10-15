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

// Complex arithmetic
// [C99:7.3.1p2]: complex, _Complex, and _Complex_I, the imaginary unit in float
// [C99:7.3.1p3]: imaginary and _Imaginary_I, left out with the imaginary types
// [C99:7.3.1p4]: I, _Complex_I where _Imaginary_I is not defined
// [C99:7.3.1p5]: complex and I, a program's to undefine and redefine
#define _Complex_I (1.0iF)
#define complex    _Complex
#define I          _Complex_I

// The CX_LIMITED_RANGE pragma
// [C99:7.3.4p2]: CX_LIMITED_RANGE, on to allow the usual formulas, off by default
// Taken and ignored, * and / keeping G.5.1's infinities in either state.

// Exponential and logarithmic functions
// [C99:7.3.7.1]: cexp, the complex base-e exponential
// [C99:7.3.7.2]: clog, in [-ipi, +ipi], a branch cut along the negative real axis
// [C99:G.6.3.1]: cexp of the infinities and NaNs
// [C99:G.6.3.2]: clog of the zeros, infinities and NaNs
double complex      cexp(double complex z);
float complex       cexpf(float complex z);
long double complex cexpl(long double complex z);
double complex      clog(double complex z);
float complex       clogf(float complex z);
long double complex clogl(long double complex z);

// Power and absolute-value functions
// [C99:7.3.8.1]: cabs, the complex absolute value
// [C99:7.3.8.2]: cpow, a branch cut for x along the negative real axis
// [C99:7.3.8.3]: csqrt, in the right half-plane, a branch cut along the negative real axis
// [C99:G.6p6]:   cabs(x + iy) as hypot(x, y)
// [C99:G.6.4.1]: cpow(x, y) as cexp(y clog(x)), spurious exceptions allowed
// [C99:G.6.4.2]: csqrt of the zeros, infinities and NaNs
double              cabs(double complex z);
float               cabsf(float complex z);
long double         cabsl(long double complex z);
double complex      cpow(double complex x, double complex y);
float complex       cpowf(float complex x, float complex y);
long double complex cpowl(long double complex x, long double complex y);
double complex      csqrt(double complex z);
float complex       csqrtf(float complex z);
long double complex csqrtl(long double complex z);

// Manipulation functions
// [C99:7.3.9.1]: carg, in [-pi, +pi], a branch cut along the negative real axis
// [C99:7.3.9.2]: cimag, the imaginary part as a real
// [C99:7.3.9.3]: conj, the imaginary part's sign reversed
// [C99:7.3.9.4]: cproj, every infinity to +inf + i0, the zero of the imaginary part's sign
// [C99:7.3.9.5]: creal, the real part
// [C99:G.6p5]:   cimag, conj, cproj and creal, raising no exception
// [C99:G.6p6]:   carg(x + iy) as atan2(y, x)
double              carg(double complex z);
float               cargf(float complex z);
long double         cargl(long double complex z);
double              cimag(double complex z);
float               cimagf(float complex z);
long double         cimagl(long double complex z);
double complex      conj(double complex z);
float complex       conjf(float complex z);
long double complex conjl(long double complex z);
double complex      cproj(double complex z);
float complex       cprojf(float complex z);
long double complex cprojl(long double complex z);
double              creal(double complex z);
float               crealf(float complex z);
long double         creall(long double complex z);

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
