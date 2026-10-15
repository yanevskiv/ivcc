/*
 * C source file for the basic complex functions.
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
#include <_basic_complex.h>

// Includes.
#include <_basic_math.h>
#include <_exact.h>

// Make a float complex value of its two parts.
float _Complex _Basic_Complex_JoinFloat(float x, float y)
{
    float part[_BASIC_COMPLEX_PARTS] = { x, y };

    return *(float _Complex *) part;
}

// Make a double complex value of its two parts.
double _Complex _Basic_Complex_JoinDouble(double x, double y)
{
    double part[_BASIC_COMPLEX_PARTS] = { x, y };

    return *(double _Complex *) part;
}

// Make a long double complex value of its two parts.
long double _Complex _Basic_Complex_JoinLDouble(long double x, long double y)
{
    long double part[_BASIC_COMPLEX_PARTS] = { x, y };

    return *(long double _Complex *) part;
}

// Box a part to 1 if it is infinite and to 0 if not, keeping its sign.
long double _Basic_Complex_BoxInfinity(long double x)
{
    return __basic_math_copysignl(_BASIC_MATH_IS_INF(x) ? 1.0L : 0.0L, x);
}

// Clear a NaN part to a zero of its sign, leaving any other.
long double _Basic_Complex_ClearNan(long double x)
{
    return _BASIC_MATH_IS_NAN(x) ? __basic_math_copysignl(0.0L, x) : x;
}

// Scale the parts of a double division's operands by the same power of 2.
void _Basic_Complex_ScaleDouble(double *a, double *b, double *c, double *d, double by)
{
    *a *= by;
    *b *= by;
    *c *= by;
    *d *= by;
}

// Scale the parts of a long double division's operands by the same power of 2.
void _Basic_Complex_ScaleLDouble(long double *a, long double *b, long double *c, long double *d, long double by)
{
    *a *= by;
    *b *= by;
    *c *= by;
    *d *= by;
}

// Recover the infinity or zero a float quotient computed as NaN + iNaN.
void _Basic_Complex_RecoverFloat(float a, float b, float c, float d, float *x, float *y)
{
    if (c == 0 && d == 0 && (! _BASIC_MATH_IS_NAN(a) || ! _BASIC_MATH_IS_NAN(b))) {
        *x = __basic_math_copysignf((float) _EXACT_INFINITY, c) * a;
        *y = __basic_math_copysignf((float) _EXACT_INFINITY, c) * b;
    } else if ((_BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b)) && _BASIC_MATH_IS_FINITE(c) && _BASIC_MATH_IS_FINITE(d)) {
        a = (float) _Basic_Complex_BoxInfinity(a);
        b = (float) _Basic_Complex_BoxInfinity(b);
        *x = (float) _EXACT_INFINITY * (a * c + b * d);
        *y = (float) _EXACT_INFINITY * (b * c - a * d);
    } else if ((_BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d)) && _BASIC_MATH_IS_FINITE(a) && _BASIC_MATH_IS_FINITE(b)) {
        c = (float) _Basic_Complex_BoxInfinity(c);
        d = (float) _Basic_Complex_BoxInfinity(d);
        *x = 0.0f * (a * c + b * d);
        *y = 0.0f * (b * c - a * d);
    }
}

// Recover the infinity or zero a double quotient computed as NaN + iNaN.
void _Basic_Complex_RecoverDouble(double a, double b, double c, double d, double *x, double *y)
{
    if (c == 0 && d == 0 && (! _BASIC_MATH_IS_NAN(a) || ! _BASIC_MATH_IS_NAN(b))) {
        *x = __basic_math_copysign((double) _EXACT_INFINITY, c) * a;
        *y = __basic_math_copysign((double) _EXACT_INFINITY, c) * b;
    } else if ((_BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b)) && _BASIC_MATH_IS_FINITE(c) && _BASIC_MATH_IS_FINITE(d)) {
        a = (double) _Basic_Complex_BoxInfinity(a);
        b = (double) _Basic_Complex_BoxInfinity(b);
        *x = (double) _EXACT_INFINITY * (a * c + b * d);
        *y = (double) _EXACT_INFINITY * (b * c - a * d);
    } else if ((_BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d)) && _BASIC_MATH_IS_FINITE(a) && _BASIC_MATH_IS_FINITE(b)) {
        c = (double) _Basic_Complex_BoxInfinity(c);
        d = (double) _Basic_Complex_BoxInfinity(d);
        *x = 0.0 * (a * c + b * d);
        *y = 0.0 * (b * c - a * d);
    }
}

// Recover the infinity or zero a long double quotient computed as NaN + iNaN.
void _Basic_Complex_RecoverLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y)
{
    if (c == 0 && d == 0 && (! _BASIC_MATH_IS_NAN(a) || ! _BASIC_MATH_IS_NAN(b))) {
        *x = __basic_math_copysignl(_EXACT_INFINITY, c) * a;
        *y = __basic_math_copysignl(_EXACT_INFINITY, c) * b;
    } else if ((_BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b)) && _BASIC_MATH_IS_FINITE(c) && _BASIC_MATH_IS_FINITE(d)) {
        a = _Basic_Complex_BoxInfinity(a);
        b = _Basic_Complex_BoxInfinity(b);
        *x = _EXACT_INFINITY * (a * c + b * d);
        *y = _EXACT_INFINITY * (b * c - a * d);
    } else if ((_BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d)) && _BASIC_MATH_IS_FINITE(a) && _BASIC_MATH_IS_FINITE(b)) {
        c = _Basic_Complex_BoxInfinity(c);
        d = _Basic_Complex_BoxInfinity(d);
        *x = 0.0L * (a * c + b * d);
        *y = 0.0L * (b * c - a * d);
    }
}

// Divide a + ib by c + id in double into x + iy, as libgcc's division.
void _Basic_Complex_DivideDouble(double a, double b, double c, double d, double *x, double *y)
{
    if (__basic_math_fabs(c) < __basic_math_fabs(d)) {
        if (__basic_math_fabs(d) >= _BASIC_COMPLEX_DBL_BIG) {
            _Basic_Complex_ScaleDouble(&a, &b, &c, &d, _BASIC_COMPLEX_HALF);
        }

        double fa = __basic_math_fabs(a);
        double fb = __basic_math_fabs(b);
        double fd = __basic_math_fabs(d);
        _Bool tiny = (fa < _BASIC_COMPLEX_DBL_MIN && fb < _BASIC_COMPLEX_DBL_BIG_EPS && fd < _BASIC_COMPLEX_DBL_BIG_EPS)
            || (fb < _BASIC_COMPLEX_DBL_MIN && fa < _BASIC_COMPLEX_DBL_BIG_EPS && fd < _BASIC_COMPLEX_DBL_BIG_EPS);

        if (fd < _BASIC_COMPLEX_DBL_EPS || tiny) {
            _Basic_Complex_ScaleDouble(&a, &b, &c, &d, _BASIC_COMPLEX_DBL_SCALE);
        }

        double ratio = c / d;
        double denom = c * ratio + d;

        if (__basic_math_fabs(ratio) > _BASIC_COMPLEX_DBL_MIN) {
            *x = (a * ratio + b) / denom;
            *y = (b * ratio - a) / denom;
        } else {
            *x = (c * (a / d) + b) / denom;
            *y = (c * (b / d) - a) / denom;
        }
    } else {
        if (__basic_math_fabs(c) >= _BASIC_COMPLEX_DBL_BIG) {
            _Basic_Complex_ScaleDouble(&a, &b, &c, &d, _BASIC_COMPLEX_HALF);
        }

        double fa = __basic_math_fabs(a);
        double fb = __basic_math_fabs(b);
        double fc = __basic_math_fabs(c);
        _Bool tiny = (fa < _BASIC_COMPLEX_DBL_MIN && fb < _BASIC_COMPLEX_DBL_BIG_EPS && fc < _BASIC_COMPLEX_DBL_BIG_EPS)
            || (fb < _BASIC_COMPLEX_DBL_MIN && fa < _BASIC_COMPLEX_DBL_BIG_EPS && fc < _BASIC_COMPLEX_DBL_BIG_EPS);

        if (fc < _BASIC_COMPLEX_DBL_EPS || tiny) {
            _Basic_Complex_ScaleDouble(&a, &b, &c, &d, _BASIC_COMPLEX_DBL_SCALE);
        }

        double ratio = d / c;
        double denom = d * ratio + c;

        if (__basic_math_fabs(ratio) > _BASIC_COMPLEX_DBL_MIN) {
            *x = (b * ratio + a) / denom;
            *y = (b - a * ratio) / denom;
        } else {
            *x = (d * (b / c) + a) / denom;
            *y = (b - d * (a / c)) / denom;
        }
    }
    if (_BASIC_MATH_IS_NAN(*x) && _BASIC_MATH_IS_NAN(*y)) {
        _Basic_Complex_RecoverDouble(a, b, c, d, x, y);
    }
}

// Divide a + ib by c + id in long double into x + iy, as libgcc's division.
void _Basic_Complex_DivideLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y)
{
    if (__basic_math_fabsl(c) < __basic_math_fabsl(d)) {
        if (__basic_math_fabsl(d) >= _BASIC_COMPLEX_LDBL_BIG) {
            _Basic_Complex_ScaleLDouble(&a, &b, &c, &d, _BASIC_COMPLEX_HALF);
        }

        long double fa = __basic_math_fabsl(a);
        long double fb = __basic_math_fabsl(b);
        long double fd = __basic_math_fabsl(d);
        _Bool tiny = (fa < _BASIC_COMPLEX_LDBL_MIN && fb < _BASIC_COMPLEX_LDBL_BIG_EPS && fd < _BASIC_COMPLEX_LDBL_BIG_EPS)
            || (fb < _BASIC_COMPLEX_LDBL_MIN && fa < _BASIC_COMPLEX_LDBL_BIG_EPS && fd < _BASIC_COMPLEX_LDBL_BIG_EPS);

        if (fd < _BASIC_COMPLEX_LDBL_EPS || tiny) {
            _Basic_Complex_ScaleLDouble(&a, &b, &c, &d, _BASIC_COMPLEX_LDBL_SCALE);
        }

        long double ratio = c / d;
        long double denom = c * ratio + d;

        if (__basic_math_fabsl(ratio) > _BASIC_COMPLEX_LDBL_MIN) {
            *x = (a * ratio + b) / denom;
            *y = (b * ratio - a) / denom;
        } else {
            *x = (c * (a / d) + b) / denom;
            *y = (c * (b / d) - a) / denom;
        }
    } else {
        if (__basic_math_fabsl(c) >= _BASIC_COMPLEX_LDBL_BIG) {
            _Basic_Complex_ScaleLDouble(&a, &b, &c, &d, _BASIC_COMPLEX_HALF);
        }

        long double fa = __basic_math_fabsl(a);
        long double fb = __basic_math_fabsl(b);
        long double fc = __basic_math_fabsl(c);
        _Bool tiny = (fa < _BASIC_COMPLEX_LDBL_MIN && fb < _BASIC_COMPLEX_LDBL_BIG_EPS && fc < _BASIC_COMPLEX_LDBL_BIG_EPS)
            || (fb < _BASIC_COMPLEX_LDBL_MIN && fa < _BASIC_COMPLEX_LDBL_BIG_EPS && fc < _BASIC_COMPLEX_LDBL_BIG_EPS);

        if (fc < _BASIC_COMPLEX_LDBL_EPS || tiny) {
            _Basic_Complex_ScaleLDouble(&a, &b, &c, &d, _BASIC_COMPLEX_LDBL_SCALE);
        }

        long double ratio = d / c;
        long double denom = d * ratio + c;

        if (__basic_math_fabsl(ratio) > _BASIC_COMPLEX_LDBL_MIN) {
            *x = (b * ratio + a) / denom;
            *y = (b - a * ratio) / denom;
        } else {
            *x = (d * (b / c) + a) / denom;
            *y = (b - d * (a / c)) / denom;
        }
    }
    if (_BASIC_MATH_IS_NAN(*x) && _BASIC_MATH_IS_NAN(*y)) {
        _Basic_Complex_RecoverLDouble(a, b, c, d, x, y);
    }
}

// Compute the absolute value of z, the hypotenuse of its parts.
double __basic_complex_cabs(double _Complex z)
{
    return __basic_math_hypot(__basic_complex_creal(z), __basic_complex_cimag(z));
}

// Compute the absolute value of z, the hypotenuse of its parts.
float __basic_complex_cabsf(float _Complex z)
{
    return __basic_math_hypotf(__basic_complex_crealf(z), __basic_complex_cimagf(z));
}

// Compute the absolute value of z, the hypotenuse of its parts.
long double __basic_complex_cabsl(long double _Complex z)
{
    return __basic_math_hypotl(__basic_complex_creall(z), __basic_complex_cimagl(z));
}

// Compute the argument of z, the arc tangent of its parts.
double __basic_complex_carg(double _Complex z)
{
    return __basic_math_atan2(__basic_complex_cimag(z), __basic_complex_creal(z));
}

// Compute the argument of z, the arc tangent of its parts.
float __basic_complex_cargf(float _Complex z)
{
    return __basic_math_atan2f(__basic_complex_cimagf(z), __basic_complex_crealf(z));
}

// Compute the argument of z, the arc tangent of its parts.
long double __basic_complex_cargl(long double _Complex z)
{
    return __basic_math_atan2l(__basic_complex_cimagl(z), __basic_complex_creall(z));
}

// Read the imaginary part of z, its second element.
double __basic_complex_cimag(double _Complex z)
{
    return ((double *) &z)[1];
}

// Read the imaginary part of z, its second element.
float __basic_complex_cimagf(float _Complex z)
{
    return ((float *) &z)[1];
}

// Read the imaginary part of z, its second element.
long double __basic_complex_cimagl(long double _Complex z)
{
    return ((long double *) &z)[1];
}

// Compute the conjugate of z, its imaginary part's sign flipped.
double _Complex __basic_complex_conj(double _Complex z)
{
    return _Basic_Complex_JoinDouble(__basic_complex_creal(z), -__basic_complex_cimag(z));
}

// Compute the conjugate of z, its imaginary part's sign flipped.
float _Complex __basic_complex_conjf(float _Complex z)
{
    return _Basic_Complex_JoinFloat(__basic_complex_crealf(z), -__basic_complex_cimagf(z));
}

// Compute the conjugate of z, its imaginary part's sign flipped.
long double _Complex __basic_complex_conjl(long double _Complex z)
{
    return _Basic_Complex_JoinLDouble(__basic_complex_creall(z), -__basic_complex_cimagl(z));
}

// Project z onto the Riemann sphere, each infinity to +inf + i(+-0).
double _Complex __basic_complex_cproj(double _Complex z)
{
    double y = __basic_complex_cimag(z);

    if (_BASIC_MATH_IS_INF(__basic_complex_creal(z)) || _BASIC_MATH_IS_INF(y)) {
        return _Basic_Complex_JoinDouble((double) _EXACT_INFINITY, __basic_math_copysign(0.0, y));
    }
    return z;
}

// Project z onto the Riemann sphere, each infinity to +inf + i(+-0).
float _Complex __basic_complex_cprojf(float _Complex z)
{
    float y = __basic_complex_cimagf(z);

    if (_BASIC_MATH_IS_INF(__basic_complex_crealf(z)) || _BASIC_MATH_IS_INF(y)) {
        return _Basic_Complex_JoinFloat((float) _EXACT_INFINITY, __basic_math_copysignf(0.0f, y));
    }
    return z;
}

// Project z onto the Riemann sphere, each infinity to +inf + i(+-0).
long double _Complex __basic_complex_cprojl(long double _Complex z)
{
    long double y = __basic_complex_cimagl(z);

    if (_BASIC_MATH_IS_INF(__basic_complex_creall(z)) || _BASIC_MATH_IS_INF(y)) {
        return _Basic_Complex_JoinLDouble(_EXACT_INFINITY, __basic_math_copysignl(0.0L, y));
    }
    return z;
}

// Read the real part of z, its first element.
double __basic_complex_creal(double _Complex z)
{
    return ((double *) &z)[0];
}

// Read the real part of z, its first element.
float __basic_complex_crealf(float _Complex z)
{
    return ((float *) &z)[0];
}

// Read the real part of z, its first element.
long double __basic_complex_creall(long double _Complex z)
{
    return ((long double *) &z)[0];
}

// Multiply a + ib by c + id, float's helper, recovering lost infinities.
float _Complex __basic_complex_mulsc3(float a, float b, float c, float d)
{
    float ac = a * c;
    float bd = b * d;
    float ad = a * d;
    float bc = b * c;
    float x = ac - bd;
    float y = ad + bc;

    if (! _BASIC_MATH_IS_NAN(x) || ! _BASIC_MATH_IS_NAN(y)) {
        return _Basic_Complex_JoinFloat(x, y);
    }

    _Bool zinf = _BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b);
    _Bool winf = _BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d);
    _Bool over = _BASIC_MATH_IS_INF(ac) || _BASIC_MATH_IS_INF(bd) || _BASIC_MATH_IS_INF(ad) || _BASIC_MATH_IS_INF(bc);

    if (! zinf && ! winf && ! over) {
        return _Basic_Complex_JoinFloat(x, y);
    }
    if (zinf) {
        a = (float) _Basic_Complex_BoxInfinity(a);
        b = (float) _Basic_Complex_BoxInfinity(b);
    }
    if (winf) {
        c = (float) _Basic_Complex_BoxInfinity(c);
        d = (float) _Basic_Complex_BoxInfinity(d);
    }
    a = (float) _Basic_Complex_ClearNan(a);
    b = (float) _Basic_Complex_ClearNan(b);
    c = (float) _Basic_Complex_ClearNan(c);
    d = (float) _Basic_Complex_ClearNan(d);
    x = (float) _EXACT_INFINITY * (a * c - b * d);
    y = (float) _EXACT_INFINITY * (a * d + b * c);
    return _Basic_Complex_JoinFloat(x, y);
}

// Multiply a + ib by c + id, double's helper, recovering lost infinities.
double _Complex __basic_complex_muldc3(double a, double b, double c, double d)
{
    double ac = a * c;
    double bd = b * d;
    double ad = a * d;
    double bc = b * c;
    double x = ac - bd;
    double y = ad + bc;

    if (! _BASIC_MATH_IS_NAN(x) || ! _BASIC_MATH_IS_NAN(y)) {
        return _Basic_Complex_JoinDouble(x, y);
    }

    _Bool zinf = _BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b);
    _Bool winf = _BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d);
    _Bool over = _BASIC_MATH_IS_INF(ac) || _BASIC_MATH_IS_INF(bd) || _BASIC_MATH_IS_INF(ad) || _BASIC_MATH_IS_INF(bc);

    if (! zinf && ! winf && ! over) {
        return _Basic_Complex_JoinDouble(x, y);
    }
    if (zinf) {
        a = (double) _Basic_Complex_BoxInfinity(a);
        b = (double) _Basic_Complex_BoxInfinity(b);
    }
    if (winf) {
        c = (double) _Basic_Complex_BoxInfinity(c);
        d = (double) _Basic_Complex_BoxInfinity(d);
    }
    a = (double) _Basic_Complex_ClearNan(a);
    b = (double) _Basic_Complex_ClearNan(b);
    c = (double) _Basic_Complex_ClearNan(c);
    d = (double) _Basic_Complex_ClearNan(d);
    x = (double) _EXACT_INFINITY * (a * c - b * d);
    y = (double) _EXACT_INFINITY * (a * d + b * c);
    return _Basic_Complex_JoinDouble(x, y);
}

// Multiply a + ib by c + id, long double's helper, recovering lost infinities.
long double _Complex __basic_complex_mulxc3(long double a, long double b, long double c, long double d)
{
    long double ac = a * c;
    long double bd = b * d;
    long double ad = a * d;
    long double bc = b * c;
    long double x = ac - bd;
    long double y = ad + bc;

    if (! _BASIC_MATH_IS_NAN(x) || ! _BASIC_MATH_IS_NAN(y)) {
        return _Basic_Complex_JoinLDouble(x, y);
    }

    _Bool zinf = _BASIC_MATH_IS_INF(a) || _BASIC_MATH_IS_INF(b);
    _Bool winf = _BASIC_MATH_IS_INF(c) || _BASIC_MATH_IS_INF(d);
    _Bool over = _BASIC_MATH_IS_INF(ac) || _BASIC_MATH_IS_INF(bd) || _BASIC_MATH_IS_INF(ad) || _BASIC_MATH_IS_INF(bc);

    if (! zinf && ! winf && ! over) {
        return _Basic_Complex_JoinLDouble(x, y);
    }
    if (zinf) {
        a = _Basic_Complex_BoxInfinity(a);
        b = _Basic_Complex_BoxInfinity(b);
    }
    if (winf) {
        c = _Basic_Complex_BoxInfinity(c);
        d = _Basic_Complex_BoxInfinity(d);
    }
    a = _Basic_Complex_ClearNan(a);
    b = _Basic_Complex_ClearNan(b);
    c = _Basic_Complex_ClearNan(c);
    d = _Basic_Complex_ClearNan(d);
    x = _EXACT_INFINITY * (a * c - b * d);
    y = _EXACT_INFINITY * (a * d + b * c);
    return _Basic_Complex_JoinLDouble(x, y);
}

// Divide a + ib by c + id, float's helper, by the formula in double.
float _Complex __basic_complex_divsc3(float a, float b, float c, float d)
{
    double denom = (double) c * c + (double) d * d;
    float x = (float) (((double) a * c + (double) b * d) / denom);
    float y = (float) (((double) b * c - (double) a * d) / denom);

    if (_BASIC_MATH_IS_NAN(x) && _BASIC_MATH_IS_NAN(y)) {
        _Basic_Complex_RecoverFloat(a, b, c, d, &x, &y);
    }
    return _Basic_Complex_JoinFloat(x, y);
}

// Divide a + ib by c + id, double's helper.
double _Complex __basic_complex_divdc3(double a, double b, double c, double d)
{
    double x = 0;
    double y = 0;

    _Basic_Complex_DivideDouble(a, b, c, d, &x, &y);
    return _Basic_Complex_JoinDouble(x, y);
}

// Divide a + ib by c + id, long double's helper.
long double _Complex __basic_complex_divxc3(long double a, long double b, long double c, long double d)
{
    long double x = 0;
    long double y = 0;

    _Basic_Complex_DivideLDouble(a, b, c, d, &x, &y);
    return _Basic_Complex_JoinLDouble(x, y);
}
