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

// Compute the arc cosine of z.
double complex cacos(double complex z)
{
    return __basic_complex_cacos(z);
}

// Compute the arc cosine of z.
float complex cacosf(float complex z)
{
    return __basic_complex_cacosf(z);
}

// Compute the arc cosine of z.
long double complex cacosl(long double complex z)
{
    return __basic_complex_cacosl(z);
}

// Compute the arc sine of z.
double complex casin(double complex z)
{
    return __basic_complex_casin(z);
}

// Compute the arc sine of z.
float complex casinf(float complex z)
{
    return __basic_complex_casinf(z);
}

// Compute the arc sine of z.
long double complex casinl(long double complex z)
{
    return __basic_complex_casinl(z);
}

// Compute the arc tangent of z.
double complex catan(double complex z)
{
    return __basic_complex_catan(z);
}

// Compute the arc tangent of z.
float complex catanf(float complex z)
{
    return __basic_complex_catanf(z);
}

// Compute the arc tangent of z.
long double complex catanl(long double complex z)
{
    return __basic_complex_catanl(z);
}

// Compute the cosine of z.
double complex ccos(double complex z)
{
    return __basic_complex_ccos(z);
}

// Compute the cosine of z.
float complex ccosf(float complex z)
{
    return __basic_complex_ccosf(z);
}

// Compute the cosine of z.
long double complex ccosl(long double complex z)
{
    return __basic_complex_ccosl(z);
}

// Compute the sine of z.
double complex csin(double complex z)
{
    return __basic_complex_csin(z);
}

// Compute the sine of z.
float complex csinf(float complex z)
{
    return __basic_complex_csinf(z);
}

// Compute the sine of z.
long double complex csinl(long double complex z)
{
    return __basic_complex_csinl(z);
}

// Compute the tangent of z.
double complex ctan(double complex z)
{
    return __basic_complex_ctan(z);
}

// Compute the tangent of z.
float complex ctanf(float complex z)
{
    return __basic_complex_ctanf(z);
}

// Compute the tangent of z.
long double complex ctanl(long double complex z)
{
    return __basic_complex_ctanl(z);
}

// Compute the inverse hyperbolic cosine of z.
double complex cacosh(double complex z)
{
    return __basic_complex_cacosh(z);
}

// Compute the inverse hyperbolic cosine of z.
float complex cacoshf(float complex z)
{
    return __basic_complex_cacoshf(z);
}

// Compute the inverse hyperbolic cosine of z.
long double complex cacoshl(long double complex z)
{
    return __basic_complex_cacoshl(z);
}

// Compute the inverse hyperbolic sine of z.
double complex casinh(double complex z)
{
    return __basic_complex_casinh(z);
}

// Compute the inverse hyperbolic sine of z.
float complex casinhf(float complex z)
{
    return __basic_complex_casinhf(z);
}

// Compute the inverse hyperbolic sine of z.
long double complex casinhl(long double complex z)
{
    return __basic_complex_casinhl(z);
}

// Compute the inverse hyperbolic tangent of z.
double complex catanh(double complex z)
{
    return __basic_complex_catanh(z);
}

// Compute the inverse hyperbolic tangent of z.
float complex catanhf(float complex z)
{
    return __basic_complex_catanhf(z);
}

// Compute the inverse hyperbolic tangent of z.
long double complex catanhl(long double complex z)
{
    return __basic_complex_catanhl(z);
}

// Compute the hyperbolic cosine of z.
double complex ccosh(double complex z)
{
    return __basic_complex_ccosh(z);
}

// Compute the hyperbolic cosine of z.
float complex ccoshf(float complex z)
{
    return __basic_complex_ccoshf(z);
}

// Compute the hyperbolic cosine of z.
long double complex ccoshl(long double complex z)
{
    return __basic_complex_ccoshl(z);
}

// Compute the hyperbolic sine of z.
double complex csinh(double complex z)
{
    return __basic_complex_csinh(z);
}

// Compute the hyperbolic sine of z.
float complex csinhf(float complex z)
{
    return __basic_complex_csinhf(z);
}

// Compute the hyperbolic sine of z.
long double complex csinhl(long double complex z)
{
    return __basic_complex_csinhl(z);
}

// Compute the hyperbolic tangent of z.
double complex ctanh(double complex z)
{
    return __basic_complex_ctanh(z);
}

// Compute the hyperbolic tangent of z.
float complex ctanhf(float complex z)
{
    return __basic_complex_ctanhf(z);
}

// Compute the hyperbolic tangent of z.
long double complex ctanhl(long double complex z)
{
    return __basic_complex_ctanhl(z);
}

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
