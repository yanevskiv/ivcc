/*
 * C source file for complex arithmetic.
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
#include <complex.h>

// Includes.
#include <_basic_complex.h>

// Compute e to z.
double complex cexp(double complex z)
{
    return __basic_complex_cexp(z);
}

// Compute e to z.
float complex cexpf(float complex z)
{
    return __basic_complex_cexpf(z);
}

// Compute e to z.
long double complex cexpl(long double complex z)
{
    return __basic_complex_cexpl(z);
}

// Compute the natural logarithm of z.
double complex clog(double complex z)
{
    return __basic_complex_clog(z);
}

// Compute the natural logarithm of z.
float complex clogf(float complex z)
{
    return __basic_complex_clogf(z);
}

// Compute the natural logarithm of z.
long double complex clogl(long double complex z)
{
    return __basic_complex_clogl(z);
}

// Compute the absolute value of z.
double cabs(double complex z)
{
    return __basic_complex_cabs(z);
}

// Compute the absolute value of z.
float cabsf(float complex z)
{
    return __basic_complex_cabsf(z);
}

// Compute the absolute value of z.
long double cabsl(long double complex z)
{
    return __basic_complex_cabsl(z);
}

// Raise x to the power y.
double complex cpow(double complex x, double complex y)
{
    return __basic_complex_cpow(x, y);
}

// Raise x to the power y.
float complex cpowf(float complex x, float complex y)
{
    return __basic_complex_cpowf(x, y);
}

// Raise x to the power y.
long double complex cpowl(long double complex x, long double complex y)
{
    return __basic_complex_cpowl(x, y);
}

// Compute the square root of z.
double complex csqrt(double complex z)
{
    return __basic_complex_csqrt(z);
}

// Compute the square root of z.
float complex csqrtf(float complex z)
{
    return __basic_complex_csqrtf(z);
}

// Compute the square root of z.
long double complex csqrtl(long double complex z)
{
    return __basic_complex_csqrtl(z);
}

// Compute the argument of z.
double carg(double complex z)
{
    return __basic_complex_carg(z);
}

// Compute the argument of z.
float cargf(float complex z)
{
    return __basic_complex_cargf(z);
}

// Compute the argument of z.
long double cargl(long double complex z)
{
    return __basic_complex_cargl(z);
}

// Read the imaginary part of z.
double cimag(double complex z)
{
    return __basic_complex_cimag(z);
}

// Read the imaginary part of z.
float cimagf(float complex z)
{
    return __basic_complex_cimagf(z);
}

// Read the imaginary part of z.
long double cimagl(long double complex z)
{
    return __basic_complex_cimagl(z);
}

// Compute the conjugate of z.
double complex conj(double complex z)
{
    return __basic_complex_conj(z);
}

// Compute the conjugate of z.
float complex conjf(float complex z)
{
    return __basic_complex_conjf(z);
}

// Compute the conjugate of z.
long double complex conjl(long double complex z)
{
    return __basic_complex_conjl(z);
}

// Project z onto the Riemann sphere.
double complex cproj(double complex z)
{
    return __basic_complex_cproj(z);
}

// Project z onto the Riemann sphere.
float complex cprojf(float complex z)
{
    return __basic_complex_cprojf(z);
}

// Project z onto the Riemann sphere.
long double complex cprojl(long double complex z)
{
    return __basic_complex_cprojl(z);
}

// Read the real part of z.
double creal(double complex z)
{
    return __basic_complex_creal(z);
}

// Read the real part of z.
float crealf(float complex z)
{
    return __basic_complex_crealf(z);
}

// Read the real part of z.
long double creall(long double complex z)
{
    return __basic_complex_creall(z);
}

// Multiply a + ib by c + id, the compiler's helper for float.
float _Complex __mulsc3(float a, float b, float c, float d)
{
    return __basic_complex_mulsc3(a, b, c, d);
}

// Multiply a + ib by c + id, the compiler's helper for double.
double _Complex __muldc3(double a, double b, double c, double d)
{
    return __basic_complex_muldc3(a, b, c, d);
}

// Multiply a + ib by c + id, the compiler's helper for long double.
long double _Complex __mulxc3(long double a, long double b, long double c, long double d)
{
    return __basic_complex_mulxc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for float.
float _Complex __divsc3(float a, float b, float c, float d)
{
    return __basic_complex_divsc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for double.
double _Complex __divdc3(double a, double b, double c, double d)
{
    return __basic_complex_divdc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for long double.
long double _Complex __divxc3(long double a, long double b, long double c, long double d)
{
    return __basic_complex_divxc3(a, b, c, d);
}
