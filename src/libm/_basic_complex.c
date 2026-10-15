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
#include <_fpu.h>

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

// Raise underflow for a nonzero finite x below least, a tiny result.
void _Basic_Complex_CheckTiny(long double x, long double least)
{
    if (_BASIC_MATH_IS_FINITE(x) && x != 0 && __basic_math_fabsl(x) < least) {
        _Fpu_RaiseFlags(_FPU_UNDERFLOW | _FPU_INEXACT);
    }
}

// Round long double parts to a float complex value.
float _Complex _Basic_Complex_RoundFloat(long double x, long double y)
{
    float re = (float) x;
    float im = (float) y;

    _Basic_Complex_CheckTiny(re, _BASIC_MATH_FLT_MIN);
    _Basic_Complex_CheckTiny(im, _BASIC_MATH_FLT_MIN);
    return _Basic_Complex_JoinFloat(re, im);
}

// Round long double parts to a double complex value.
double _Complex _Basic_Complex_RoundDouble(long double x, long double y)
{
    double re = (double) x;
    double im = (double) y;

    _Basic_Complex_CheckTiny(re, _BASIC_MATH_DBL_MIN);
    _Basic_Complex_CheckTiny(im, _BASIC_MATH_DBL_MIN);
    return _Basic_Complex_JoinDouble(re, im);
}

// Join long double parts into a long double complex value.
long double _Complex _Basic_Complex_RoundLDouble(long double x, long double y)
{
    _Basic_Complex_CheckTiny(x, _BASIC_MATH_LDBL_MIN);
    _Basic_Complex_CheckTiny(y, _BASIC_MATH_LDBL_MIN);
    return _Basic_Complex_JoinLDouble(x, y);
}

// Make a quiet NaN of no payload and a clear sign.
long double _Basic_Complex_MakeNan(void)
{
    return _Exact_MakeLDouble(_EXACT_LDOUBLE_EXP_MAX, _BASIC_MATH_LDOUBLE_QUIET);
}

// Square x into a high and a low part, or zero where x is below least.
long double _Basic_Complex_SquareParts(long double x, long double least, long double *low)
{
    if (__basic_math_fabsl(x) < least) {
        *low = 0;
        return 0;
    }
    return _Basic_Math_MultiplyParts(x, x, low);
}

// Sum a^2 + b^2 - 1 for a >= b >= 0, b's square dropped below least.
long double _Basic_Complex_SumUnitGap(long double a, long double b, long double least)
{
    _Exact_Value sum;
    _Exact_Value part;
    long double p;
    long double p_low;
    long double q;
    long double q_low;
    long double high;
    long double error;
    long double rest;
    long double t;

    p = _Basic_Math_MultiplyParts(a, a, &p_low);
    q = _Basic_Complex_SquareParts(b, least, &q_low);
    high = _Basic_Math_AddParts(p, -1, &error);
    high = _Basic_Math_AddParts(high, q, &rest);
    t = high + (error + rest + p_low + q_low);
    if (__basic_math_fabsl(t) < _BASIC_COMPLEX_LOG_EXACT && a != 1) {
        _Exact_MakeValue(&sum, a);
        _Exact_MultiplyValues(&sum, &sum, &sum);
        _Exact_MakeValue(&part, -1);
        _Exact_AddValues(&sum, &sum, &part);
        if (b != 0) {
            _Exact_MakeValue(&part, b);
            _Exact_MultiplyValues(&part, &part, &part);
            _Exact_AddValues(&sum, &sum, &part);
        }
        t = _Exact_RoundValue(&sum, _EXACT_TYPE_LDOUBLE);
    }
    return t;
}

// Take |x + iy| of parts within 2^-8000 to 2^8000, a the larger magnitude.
long double _Basic_Complex_TakeAbs(long double x, long double y, long double a)
{
    long double p;
    long double p_low;
    long double q;
    long double q_low;
    long double error;
    long double h;

    p = _Basic_Complex_SquareParts(x, a * _BASIC_COMPLEX_RATIO_TINY, &p_low);
    q = _Basic_Complex_SquareParts(y, a * _BASIC_COMPLEX_RATIO_TINY, &q_low);
    p = _Basic_Math_AddParts(p, q, &error);
    h = _Basic_Math_IterateRoot(p);
    return h + (error + p_low + q_low) / (2 * h);
}

// Take the sine and the cosine of a finite y.
void _Basic_Complex_TakeSinCos(long double y, long double *s, long double *c)
{
    long double r;
    long double low;
    long double sine;
    long double cosine;
    long double swap;
    unsigned int quadrant;

    if (__basic_math_fabsl(y) < _BASIC_COMPLEX_TRIG_TINY) {
        *s = y;
        *c = 1;
        return;
    }
    quadrant = _Basic_Math_ReduceTrig(__basic_math_fabsl(y), &r, &low);
    sine = _Basic_Math_SumSin(r, low);
    cosine = _Basic_Math_SumCos(r, low);
    if ((quadrant & _BASIC_MATH_QUADRANT_ODD) != 0) {
        swap = sine;
        sine = cosine;
        cosine = -swap;
    }
    if ((quadrant & _BASIC_MATH_QUADRANT_HALF) != 0) {
        sine = -sine;
        cosine = -cosine;
    }
    *s = y < 0 ? -sine : sine;
    *c = cosine;
}

// Take e to x + iy, as e to x times the cosine and the sine of y.
void _Basic_Complex_TakeExp(long double x, long double y, long double *re, long double *im)
{
    long double r;
    long double s;
    long double c;
    long double m;
    int n;

    if (_BASIC_MATH_IS_FINITE(x) && _BASIC_MATH_IS_FINITE(y)) {
        _Basic_Complex_TakeSinCos(y, &s, &c);
        if (__basic_math_fabsl(x) > _BASIC_MATH_EXP_CLAMP) {
            x = __basic_math_copysignl(_BASIC_MATH_EXP_CLAMP, x);
        }
        n = _Basic_Math_ReduceExp(x, _BASIC_MATH_BASE_E, &r);
        m = 1 + _Basic_Math_SumExp(r);
        *re = _Basic_Math_ScaleLDouble(m * c, n);
        *im = _Basic_Math_ScaleLDouble(m * s, n);
    } else if (_BASIC_MATH_IS_FINITE(x)) {
        *re = _Basic_Complex_MakeNan();
        *im = *re;
        _Fpu_RaiseFlags(_FPU_INVALID);
    } else if (_BASIC_MATH_IS_INF(x) && _BASIC_MATH_IS_FINITE(y)) {
        m = x < 0 ? 0 : _EXACT_INFINITY;
        if (y == 0) {
            *re = m;
            *im = y;
        } else {
            _Basic_Complex_TakeSinCos(y, &s, &c);
            *re = __basic_math_copysignl(m, c);
            *im = __basic_math_copysignl(m, s);
        }
    } else if (_BASIC_MATH_IS_INF(x)) {
        *re = x < 0 ? 0 : x;
        *im = x < 0 ? __basic_math_copysignl(0, y) : y - y;
    } else {
        *re = _Basic_Complex_MakeNan();
        *im = y == 0 ? y : *re;
        if (y != 0 && ! _BASIC_MATH_IS_NAN(y)) {
            _Fpu_RaiseFlags(_FPU_INVALID);
        }
    }
}

// Take ln |x + iy| of finite parts not both zero.
long double _Basic_Complex_TakeLogAbs(long double x, long double y)
{
    long double a = __basic_math_fabsl(x);
    long double b = __basic_math_fabsl(y);
    long double t;

    if (a < b) {
        t = a;
        a = b;
        b = t;
    }
    if (a < _BASIC_COMPLEX_LOG_NEAR_LOW || a > _BASIC_COMPLEX_LOG_NEAR_HIGH) {
        if ((a >= _BASIC_COMPLEX_LOG_SQUARE && b < a * _BASIC_COMPLEX_RATIO_TINY) || b / a < _BASIC_COMPLEX_RATIO_TINY) {
            return _Basic_Math_TakeLog(a, _BASIC_MATH_BASE_E);
        }
        t = b / a;
        return _Basic_Math_TakeLog(a, _BASIC_MATH_BASE_E) + _BASIC_MATH_HALF * _Basic_Math_TakeLog1p(t * t);
    }
    t = _Basic_Complex_SumUnitGap(a, b, a == 1 ? 0 : _BASIC_COMPLEX_LOG_SQUARE);
    return _BASIC_MATH_HALF * _Basic_Math_TakeLog1p(t);
}

// Take the natural logarithm of x + iy, its imaginary part in [-pi, pi].
void _Basic_Complex_TakeLog(long double x, long double y, long double *re, long double *im)
{
    if (_BASIC_MATH_IS_NAN(x) || _BASIC_MATH_IS_NAN(y)) {
        *re = _BASIC_MATH_IS_INF(x) || _BASIC_MATH_IS_INF(y) ? _EXACT_INFINITY : _Basic_Complex_MakeNan();
        *im = _Basic_Complex_MakeNan();
        return;
    }
    *im = _Basic_Math_TakeAtan2(y, x);
    if (x == 0 && y == 0) {
        *re = -1 / __basic_math_fabsl(x);
    } else if (_BASIC_MATH_IS_INF(x) || _BASIC_MATH_IS_INF(y)) {
        *re = _EXACT_INFINITY;
    } else {
        *re = _Basic_Complex_TakeLogAbs(x, y);
    }
}

// Take the square root of x + iy by the root of half of |x| + |z|.
void _Basic_Complex_TakeSqrt(long double x, long double y, long double *re, long double *im)
{
    int class_x = _BASIC_MATH_CLASSIFY(x);
    int class_y = _BASIC_MATH_CLASSIFY(y);
    long double a;
    long double h;
    long double t;
    int k = 0;

    if (class_y == _BASIC_MATH_FP_INFINITE) {
        *re = _EXACT_INFINITY;
        *im = y;
        return;
    }
    if (class_x == _BASIC_MATH_FP_INFINITE) {
        *re = x > 0 ? x : class_y == _BASIC_MATH_FP_NAN ? _Basic_Complex_MakeNan() : 0;
        *im = x < 0 ? __basic_math_copysignl(_EXACT_INFINITY, y) : class_y == _BASIC_MATH_FP_NAN ? _Basic_Complex_MakeNan() : __basic_math_copysignl(0, y);
        return;
    }
    if (class_x == _BASIC_MATH_FP_NAN || class_y == _BASIC_MATH_FP_NAN) {
        *re = _Basic_Complex_MakeNan();
        *im = *re;
        return;
    }
    if (class_x == _BASIC_MATH_FP_ZERO && class_y == _BASIC_MATH_FP_ZERO) {
        *re = 0;
        *im = y;
        return;
    }
    a = __basic_math_fabsl(x) > __basic_math_fabsl(y) ? __basic_math_fabsl(x) : __basic_math_fabsl(y);
    if (a > _BASIC_COMPLEX_ROOT_HUGE || a < _BASIC_COMPLEX_ROOT_TINY) {
        k = __basic_math_ilogbl(a) / 2;
        a = _Basic_Math_ScaleLDouble(a, -2 * k);
        x = _Basic_Math_ScaleLDouble(x, -2 * k);
        y = _Basic_Math_ScaleLDouble(y, -2 * k);
    }
    h = _Basic_Complex_TakeAbs(x, y, a);
    t = _Basic_Math_IterateRoot(_BASIC_MATH_HALF * (__basic_math_fabsl(x) + h));
    if (x == 0) {
        *re = t;
        *im = __basic_math_copysignl(t, y);
    } else if (x > 0) {
        *re = t;
        *im = y / (2 * t);
    } else {
        *re = __basic_math_fabsl(y) / (2 * t);
        *im = __basic_math_copysignl(t, y);
    }
    if (k != 0) {
        *re = _Basic_Math_ScaleLDouble(*re, k);
        *im = _Basic_Math_ScaleLDouble(*im, k);
    }
}

// Take x + iy to c + id, as e to (c + id) ln(x + iy).
void _Basic_Complex_TakePow(long double x, long double y, long double c, long double d, long double *re, long double *im)
{
    long double u;
    long double v;
    long double _Complex w;

    _Basic_Complex_TakeLog(x, y, &u, &v);
    w = __basic_complex_mulxc3(c, d, u, v);
    _Basic_Complex_TakeExp(__basic_complex_creall(w), __basic_complex_cimagl(w), re, im);
}

// Take sinh and cosh of a finite a >= 0, each scaled by 2 to minus the result.
int _Basic_Complex_TakeSinhCosh(long double a, long double *sh, long double *ch)
{
    long double r;
    int n;

    if (a < _BASIC_COMPLEX_TRIG_TINY) {
        *sh = a;
        *ch = 1;
        return 0;
    }
    if (a <= _BASIC_MATH_HYPERBOLIC_WIDE) {
        *sh = _Basic_Math_TakeHyperbolic(a, _BASIC_MATH_TRIG_SIN);
        *ch = _Basic_Math_TakeHyperbolic(a, _BASIC_MATH_TRIG_COS);
        return 0;
    }
    if (a > _BASIC_MATH_EXP_CLAMP) {
        a = _BASIC_MATH_EXP_CLAMP;
    }
    n = _Basic_Math_ReduceExp(a, _BASIC_MATH_BASE_E, &r);
    *sh = 1 + _Basic_Math_SumExp(r);
    *ch = *sh;
    return n - 1;
}

// Take the hyperbolic sine of x + iy, as sinh x cos y + i cosh x sin y.
void _Basic_Complex_TakeSinh(long double x, long double y, long double *re, long double *im)
{
    long double sh;
    long double ch;
    long double s;
    long double c;
    int n;

    if (_BASIC_MATH_IS_FINITE(x) && _BASIC_MATH_IS_FINITE(y)) {
        n = _Basic_Complex_TakeSinhCosh(__basic_math_fabsl(x), &sh, &ch);
        _Basic_Complex_TakeSinCos(y, &s, &c);
        *re = __basic_math_copysignl(sh, x) * c;
        *im = ch * s;
        if (n != 0) {
            *re = _Basic_Math_ScaleLDouble(*re, n);
            *im = _Basic_Math_ScaleLDouble(*im, n);
        }
    } else if (_BASIC_MATH_IS_FINITE(x)) {
        if (x == 0) {
            *re = x;
            *im = y - y;
        } else {
            *re = _Basic_Complex_MakeNan();
            *im = *re;
            _Fpu_RaiseFlags(_FPU_INVALID);
        }
    } else if (_BASIC_MATH_IS_INF(x) && _BASIC_MATH_IS_FINITE(y)) {
        if (y == 0) {
            *re = x;
            *im = y;
        } else {
            _Basic_Complex_TakeSinCos(y, &s, &c);
            *re = __basic_math_copysignl(_EXACT_INFINITY, c);
            *re = x < 0 ? -*re : *re;
            *im = __basic_math_copysignl(_EXACT_INFINITY, s);
        }
    } else if (_BASIC_MATH_IS_INF(x)) {
        *re = _EXACT_INFINITY;
        *im = y - y;
    } else {
        *re = _Basic_Complex_MakeNan();
        *im = y == 0 ? y : *re;
    }
}

// Take the hyperbolic cosine of x + iy, as cosh x cos y + i sinh x sin y.
void _Basic_Complex_TakeCosh(long double x, long double y, long double *re, long double *im)
{
    long double sh;
    long double ch;
    long double s;
    long double c;
    int n;

    if (_BASIC_MATH_IS_FINITE(x) && _BASIC_MATH_IS_FINITE(y)) {
        n = _Basic_Complex_TakeSinhCosh(__basic_math_fabsl(x), &sh, &ch);
        _Basic_Complex_TakeSinCos(y, &s, &c);
        *re = ch * c;
        *im = __basic_math_copysignl(sh, x) * s;
        if (n != 0) {
            *re = _Basic_Math_ScaleLDouble(*re, n);
            *im = _Basic_Math_ScaleLDouble(*im, n);
        }
    } else if (_BASIC_MATH_IS_FINITE(x)) {
        *re = y - y;
        *im = x == 0 ? 0 : _Basic_Complex_MakeNan();
    } else if (_BASIC_MATH_IS_INF(x) && _BASIC_MATH_IS_FINITE(y)) {
        *re = _EXACT_INFINITY;
        if (y == 0) {
            *im = x < 0 ? -y : y;
        } else {
            _Basic_Complex_TakeSinCos(y, &s, &c);
            *re = __basic_math_copysignl(_EXACT_INFINITY, c);
            *im = __basic_math_copysignl(_EXACT_INFINITY, s);
            *im = x < 0 ? -*im : *im;
        }
    } else if (_BASIC_MATH_IS_INF(x)) {
        *re = _EXACT_INFINITY;
        *im = y - y;
    } else {
        *re = _Basic_Complex_MakeNan();
        *im = y == 0 ? y : *re;
    }
}

// Take the hyperbolic tangent of x + iy, by sinh x, cosh x, sin y and cos y.
void _Basic_Complex_TakeTanh(long double x, long double y, long double *re, long double *im)
{
    long double a = __basic_math_fabsl(x);
    long double sh;
    long double ch;
    long double s;
    long double c;
    long double r;
    long double den;
    int n;

    if (_BASIC_MATH_IS_FINITE(x) && _BASIC_MATH_IS_FINITE(y)) {
        _Basic_Complex_TakeSinCos(y, &s, &c);
        if (a > _BASIC_MATH_HYPERBOLIC_WIDE) {
            if (a > _BASIC_MATH_HALF * _BASIC_MATH_EXP_CLAMP) {
                a = _BASIC_MATH_HALF * _BASIC_MATH_EXP_CLAMP;
            }
            n = _Basic_Math_ReduceExp(-2 * a, _BASIC_MATH_BASE_E, &r);
            *re = __basic_math_copysignl(1, x);
            *im = _Basic_Math_ScaleLDouble(4 * s * c * (1 + _Basic_Math_SumExp(r)), n);
            return;
        }
        _Basic_Complex_TakeSinhCosh(a, &sh, &ch);
        den = c * c;
        if (sh >= __basic_math_fabsl(c) * _BASIC_COMPLEX_RATIO_TINY) {
            den += sh * sh;
        }
        *re = __basic_math_copysignl(sh * ch / den, x);
        *im = s * c / den;
    } else if (_BASIC_MATH_IS_INF(x)) {
        *re = __basic_math_copysignl(1, x);
        if (_BASIC_MATH_IS_FINITE(y) && __basic_math_fabsl(y) > 1) {
            _Basic_Complex_TakeSinCos(y, &s, &c);
            *im = __basic_math_copysignl(0, s * c);
        } else {
            *im = __basic_math_copysignl(0, y);
        }
    } else if (y == 0) {
        *re = x;
        *im = y;
    } else {
        *re = x == 0 ? x : _Basic_Complex_MakeNan();
        *im = _Basic_Complex_MakeNan();
        if (_BASIC_MATH_IS_INF(y)) {
            _Fpu_RaiseFlags(_FPU_INVALID);
        }
    }
}

// Take half of h less b, h the hypotenuse of a and b, without cancellation.
long double _Basic_Complex_TakeHalfExcess(long double a, long double b, long double h)
{
    if (b < 0) {
        return _BASIC_MATH_HALF * (h - b);
    }
    if (b == 0) {
        return _BASIC_MATH_HALF * a;
    }
    return _BASIC_MATH_HALF * (a * a / (h + b));
}

// Take casinh's real part of x + iy, x, y >= 0, and its angle's two sides.
long double _Basic_Complex_TakeArcParts(long double x, long double y, long double *top, long double *side)
{
    long double gap = __basic_math_fabsl(y - 1);
    long double r = _Basic_Complex_TakeAbs(x, y + 1, x > y + 1 ? x : y + 1);
    long double b = x > gap ? x : gap;
    long double s = b < _BASIC_COMPLEX_ROOT_TINY ? b : _Basic_Complex_TakeAbs(x, y - 1, b);
    long double a = _BASIC_MATH_HALF * (r + s);
    long double am1;
    long double re;

    if (a < 1) {
        a = 1;
    }
    if (a >= _BASIC_COMPLEX_ARC_CROSS_A) {
        re = _Basic_Math_TakeLog(a + _Basic_Math_IterateRoot(a * a - 1), _BASIC_MATH_BASE_E);
    } else if (y == 1 && x < _BASIC_COMPLEX_ARC_NEAR) {
        re = _Basic_Math_IterateRoot(x);
    } else if (x >= _BASIC_COMPLEX_LDBL_EPS * gap) {
        am1 = _Basic_Complex_TakeHalfExcess(x, 1 + y, r) + _Basic_Complex_TakeHalfExcess(x, 1 - y, s);
        re = _Basic_Math_TakeLog1p(am1 + _Basic_Math_IterateRoot(am1 * (a + 1)));
    } else if (y < 1) {
        re = x / _Basic_Math_IterateRoot((1 - y) * (1 + y));
    } else {
        re = _Basic_Math_TakeLog1p((y - 1) + _Basic_Math_IterateRoot((y - 1) * (y + 1)));
    }
    *top = y;
    if (y < _BASIC_COMPLEX_ARC_FLOOR) {
        *top = y * _BASIC_COMPLEX_ARC_LIFT;
        *side = a * _BASIC_COMPLEX_ARC_LIFT;
    } else if (y / a <= _BASIC_COMPLEX_ARC_CROSS_B) {
        *top = y / a;
        *side = _Basic_Math_IterateRoot((1 - *top) * (1 + *top));
    } else if (y == 1 && x < _BASIC_COMPLEX_ARC_NEAR_SIDE) {
        *side = _Basic_Math_IterateRoot(x) * _Basic_Math_IterateRoot(_BASIC_MATH_HALF * (a + y));
    } else if (x >= _BASIC_COMPLEX_LDBL_EPS * gap) {
        am1 = _Basic_Complex_TakeHalfExcess(x, y + 1, r) + _Basic_Complex_TakeHalfExcess(x, y - 1, s);
        *side = _Basic_Math_IterateRoot(am1 * (a + y));
    } else if (y > 1) {
        *side = x * _BASIC_COMPLEX_ARC_LIFT_TWICE * y / _Basic_Math_IterateRoot((y + 1) * (y - 1));
        *top = y * _BASIC_COMPLEX_ARC_LIFT_TWICE;
    } else {
        *side = _Basic_Math_IterateRoot((1 - y) * (1 + y));
    }
    return re;
}

// Take the inverse hyperbolic sine of x + iy, by Hull's A and B.
void _Basic_Complex_TakeAsinh(long double x, long double y, long double *re, long double *im)
{
    long double a = __basic_math_fabsl(x);
    long double b = __basic_math_fabsl(y);
    long double top;
    long double side;
    long double u;
    long double v;

    if (_BASIC_MATH_IS_INF(y)) {
        *re = __basic_math_copysignl(_EXACT_INFINITY, x);
        if (_BASIC_MATH_IS_NAN(x)) {
            *im = _Basic_Complex_MakeNan();
        } else {
            *im = __basic_math_copysignl(_BASIC_MATH_IS_INF(x) ? _BASIC_COMPLEX_QUARTER_PI : _BASIC_MATH_HALF_PI_HIGH + _BASIC_MATH_HALF_PI_LOW, y);
        }
    } else if (! _BASIC_MATH_IS_FINITE(x)) {
        *re = x;
        if ((_BASIC_MATH_IS_INF(x) && _BASIC_MATH_IS_FINITE(y)) || y == 0) {
            *im = __basic_math_copysignl(0, y);
        } else {
            *im = _Basic_Complex_MakeNan();
        }
    } else if (_BASIC_MATH_IS_NAN(y)) {
        *re = _Basic_Complex_MakeNan();
        *im = *re;
    } else if (a > _BASIC_COMPLEX_ARC_HUGE || b > _BASIC_COMPLEX_ARC_HUGE) {
        _Basic_Complex_TakeLog(a, b, &u, &v);
        *re = __basic_math_copysignl(u + _BASIC_MATH_LN2, x);
        *im = __basic_math_copysignl(v, y);
    } else if (a < _BASIC_COMPLEX_ARC_TINY && b < _BASIC_COMPLEX_ARC_TINY) {
        *re = x;
        *im = y;
    } else {
        u = _Basic_Complex_TakeArcParts(a, b, &top, &side);
        *re = __basic_math_copysignl(u, x);
        *im = __basic_math_copysignl(_Basic_Math_TakeAtan2(top, side), y);
    }
}

// Take the arc sine of x + iy, as -i casinh(iz).
void _Basic_Complex_TakeAsin(long double x, long double y, long double *re, long double *im)
{
    long double u;
    long double v;

    if (_BASIC_MATH_IS_NAN(x)) {
        *re = _BASIC_MATH_IS_INF(y) ? x : _Basic_Complex_MakeNan();
        *im = _BASIC_MATH_IS_INF(y) ? y : *re;
        return;
    }
    _Basic_Complex_TakeAsinh(-y, x, &u, &v);
    *re = v;
    *im = -u;
}

// Take the arc cosine of x + iy, by Hull's A and B.
void _Basic_Complex_TakeAcos(long double x, long double y, long double *re, long double *im)
{
    long double a = __basic_math_fabsl(x);
    long double b = __basic_math_fabsl(y);
    long double top;
    long double side;
    long double u;
    long double v;

    if (! _BASIC_MATH_IS_FINITE(x) || ! _BASIC_MATH_IS_FINITE(y) || (x == 0 && y == 0)) {
        _Basic_Complex_TakeAsin(x, y, &u, &v);
        *re = (_BASIC_MATH_HALF_PI_HIGH + _BASIC_MATH_HALF_PI_LOW) - u;
        *im = -v;
    } else if (a > _BASIC_COMPLEX_ARC_HUGE || b > _BASIC_COMPLEX_ARC_HUGE) {
        _Basic_Complex_TakeLog(x, y, &u, &v);
        *re = __basic_math_fabsl(v);
        *im = _BASIC_MATH_SIGNBIT(y) != 0 ? u + _BASIC_MATH_LN2 : -(u + _BASIC_MATH_LN2);
    } else if (x == 1 && y == 0) {
        *re = 0;
        *im = -y;
    } else if (a < _BASIC_COMPLEX_ARC_TINY && b < _BASIC_COMPLEX_ARC_TINY) {
        *re = _BASIC_MATH_HALF_PI_HIGH - (x - _BASIC_MATH_HALF_PI_LOW);
        *im = -y;
    } else {
        u = _Basic_Complex_TakeArcParts(b, a, &top, &side);
        *re = _Basic_Math_TakeAtan2(side, x < 0 ? -top : top);
        *im = _BASIC_MATH_SIGNBIT(y) != 0 ? u : -u;
    }
}

// Take the inverse hyperbolic cosine of x + iy, by its arc cosine.
void _Basic_Complex_TakeAcosh(long double x, long double y, long double *re, long double *im)
{
    long double half_pi = _BASIC_MATH_HALF_PI_HIGH + _BASIC_MATH_HALF_PI_LOW;
    long double u;
    long double v;

    if (_BASIC_MATH_IS_INF(y)) {
        *re = _EXACT_INFINITY;
        if (_BASIC_MATH_IS_NAN(x)) {
            *im = _Basic_Complex_MakeNan();
        } else if (_BASIC_MATH_IS_INF(x)) {
            *im = __basic_math_copysignl(x < 0 ? _BASIC_COMPLEX_THREE_QUARTER_PI : _BASIC_COMPLEX_QUARTER_PI, y);
        } else {
            *im = __basic_math_copysignl(half_pi, y);
        }
    } else if (_BASIC_MATH_IS_INF(x)) {
        *re = _EXACT_INFINITY;
        if (_BASIC_MATH_IS_FINITE(y)) {
            *im = __basic_math_copysignl(x < 0 ? _BASIC_MATH_PI_HIGH + _BASIC_MATH_PI_LOW : 0, y);
        } else {
            *im = _Basic_Complex_MakeNan();
        }
    } else if (_BASIC_MATH_IS_NAN(x) || _BASIC_MATH_IS_NAN(y)) {
        *re = _Basic_Complex_MakeNan();
        *im = x == 0 ? half_pi : *re;
    } else if (x == 0 && y == 0) {
        *re = 0;
        *im = __basic_math_copysignl(half_pi, y);
    } else {
        _Basic_Complex_TakeAcos(x, y, &u, &v);
        *re = __basic_math_fabsl(v);
        *im = __basic_math_copysignl(u, y);
    }
}

// Take the real part of 1 / (x + iy), past 2^63 in magnitude.
long double _Basic_Complex_TakeInverseReal(long double x, long double y)
{
    long double a = __basic_math_fabsl(x);
    long double b = __basic_math_fabsl(y);
    int k;

    if (b < a * _BASIC_COMPLEX_RATIO_TINY) {
        return 1 / x;
    }
    if (a < b * _BASIC_COMPLEX_RATIO_TINY) {
        return x / y / y;
    }
    k = __basic_math_ilogbl(a > b ? a : b);
    x = _Basic_Math_ScaleLDouble(x, -k);
    y = _Basic_Math_ScaleLDouble(y, -k);
    return _Basic_Math_ScaleLDouble(x / (x * x + y * y), -k);
}

// Take the inverse hyperbolic tangent of x + iy, by log1p and atan2.
void _Basic_Complex_TakeAtanh(long double x, long double y, long double *re, long double *im)
{
    long double half_pi = _BASIC_MATH_HALF_PI_HIGH + _BASIC_MATH_HALF_PI_LOW;
    long double a = __basic_math_fabsl(x);
    long double b = __basic_math_fabsl(y);
    long double t;
    long double p;
    long double q;
    long double low;

    if (_BASIC_MATH_IS_INF(y)) {
        *re = __basic_math_copysignl(0, x);
        *im = __basic_math_copysignl(half_pi, y);
    } else if (! _BASIC_MATH_IS_FINITE(x) || _BASIC_MATH_IS_NAN(y)) {
        if (_BASIC_MATH_IS_INF(x) || x == 0) {
            *re = __basic_math_copysignl(0, x);
            *im = _BASIC_MATH_IS_FINITE(y) ? __basic_math_copysignl(half_pi, y) : _Basic_Complex_MakeNan();
        } else {
            *re = _Basic_Complex_MakeNan();
            *im = *re;
        }
    } else if (y == 0 && a <= 1) {
        if (a == 1) {
            *re = __basic_math_copysignl(_EXACT_INFINITY, x);
            _Fpu_RaiseFlags(_FPU_DIVBYZERO);
        } else {
            *re = x == 0 ? x : _Basic_Math_TakeArcHyperbolic(x, _BASIC_MATH_TRIG_TAN);
        }
        *im = y;
    } else if (x == 0) {
        *re = x;
        *im = _Basic_Math_TakeAtan2(y, 1);
    } else if (a > _BASIC_COMPLEX_ARC_HUGE || b > _BASIC_COMPLEX_ARC_HUGE) {
        *re = _Basic_Complex_TakeInverseReal(x, y);
        *im = __basic_math_copysignl(half_pi, y);
    } else if (a < _BASIC_COMPLEX_ARC_TINY && b < _BASIC_COMPLEX_ARC_TINY) {
        *re = x;
        *im = y;
    } else {
        if (a == 1 && b < _BASIC_COMPLEX_LDBL_EPS) {
            *re = _BASIC_MATH_HALF * (_BASIC_MATH_LN2 - _Basic_Math_TakeLog(b, _BASIC_MATH_BASE_E));
        } else {
            t = a - 1;
            p = t * t;
            q = _Basic_Complex_SquareParts(b, __basic_math_fabsl(t) * _BASIC_COMPLEX_RATIO_TINY, &low);
            *re = _BASIC_MATH_HALF * _BASIC_MATH_HALF * _Basic_Math_TakeLog1p(4 * a / (p + q));
        }
        t = a > b ? _Basic_Complex_SumUnitGap(a, b, _BASIC_COMPLEX_LOG_SQUARE) : _Basic_Complex_SumUnitGap(b, a, _BASIC_COMPLEX_LOG_SQUARE);
        *re = __basic_math_copysignl(*re, x);
        *im = __basic_math_copysignl(_BASIC_MATH_HALF * _Basic_Math_TakeAtan2(2 * b, -t), y);
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

// Compute the arc cosine of z, in long double.
double _Complex __basic_complex_cacos(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcos(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the arc cosine of z, in long double.
float _Complex __basic_complex_cacosf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcos(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the arc cosine of z.
long double _Complex __basic_complex_cacosl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcos(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the inverse hyperbolic cosine of z, in long double.
double _Complex __basic_complex_cacosh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcosh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the inverse hyperbolic cosine of z, in long double.
float _Complex __basic_complex_cacoshf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcosh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the inverse hyperbolic cosine of z.
long double _Complex __basic_complex_cacoshl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAcosh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
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

// Compute the arc sine of z, in long double.
double _Complex __basic_complex_casin(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsin(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the arc sine of z, in long double.
float _Complex __basic_complex_casinf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsin(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the arc sine of z.
long double _Complex __basic_complex_casinl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsin(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the inverse hyperbolic sine of z, in long double.
double _Complex __basic_complex_casinh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsinh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the inverse hyperbolic sine of z, in long double.
float _Complex __basic_complex_casinhf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsinh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the inverse hyperbolic sine of z.
long double _Complex __basic_complex_casinhl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAsinh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the arc tangent of z, as -i catanh(iz), in long double.
double _Complex __basic_complex_catan(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(-__basic_complex_cimag(z), __basic_complex_creal(z), &re, &im);
    return _Basic_Complex_RoundDouble(im, -re);
}

// Compute the arc tangent of z, as -i catanh(iz), in long double.
float _Complex __basic_complex_catanf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(-__basic_complex_cimagf(z), __basic_complex_crealf(z), &re, &im);
    return _Basic_Complex_RoundFloat(im, -re);
}

// Compute the arc tangent of z, as -i catanh(iz).
long double _Complex __basic_complex_catanl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(-__basic_complex_cimagl(z), __basic_complex_creall(z), &re, &im);
    return _Basic_Complex_RoundLDouble(im, -re);
}

// Compute the inverse hyperbolic tangent of z, in long double.
double _Complex __basic_complex_catanh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the inverse hyperbolic tangent of z, in long double.
float _Complex __basic_complex_catanhf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the inverse hyperbolic tangent of z.
long double _Complex __basic_complex_catanhl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeAtanh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the cosine of z, as ccosh(iz), in long double.
double _Complex __basic_complex_ccos(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(-__basic_complex_cimag(z), __basic_complex_creal(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the cosine of z, as ccosh(iz), in long double.
float _Complex __basic_complex_ccosf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(-__basic_complex_cimagf(z), __basic_complex_crealf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the cosine of z, as ccosh(iz).
long double _Complex __basic_complex_ccosl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(-__basic_complex_cimagl(z), __basic_complex_creall(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the hyperbolic cosine of z, in long double.
double _Complex __basic_complex_ccosh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the hyperbolic cosine of z, in long double.
float _Complex __basic_complex_ccoshf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the hyperbolic cosine of z.
long double _Complex __basic_complex_ccoshl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeCosh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute e to z, in long double.
double _Complex __basic_complex_cexp(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeExp(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute e to z, in long double.
float _Complex __basic_complex_cexpf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeExp(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute e to z.
long double _Complex __basic_complex_cexpl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeExp(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
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

// Compute the natural logarithm of z, in long double.
double _Complex __basic_complex_clog(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeLog(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the natural logarithm of z, in long double.
float _Complex __basic_complex_clogf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeLog(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the natural logarithm of z.
long double _Complex __basic_complex_clogl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeLog(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
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

// Raise x to the power y, in long double.
double _Complex __basic_complex_cpow(double _Complex x, double _Complex y)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakePow(__basic_complex_creal(x), __basic_complex_cimag(x), __basic_complex_creal(y), __basic_complex_cimag(y), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Raise x to the power y, in long double.
float _Complex __basic_complex_cpowf(float _Complex x, float _Complex y)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakePow(__basic_complex_crealf(x), __basic_complex_cimagf(x), __basic_complex_crealf(y), __basic_complex_cimagf(y), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Raise x to the power y.
long double _Complex __basic_complex_cpowl(long double _Complex x, long double _Complex y)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakePow(__basic_complex_creall(x), __basic_complex_cimagl(x), __basic_complex_creall(y), __basic_complex_cimagl(y), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
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

// Compute the sine of z, as -i csinh(iz), in long double.
double _Complex __basic_complex_csin(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(-__basic_complex_cimag(z), __basic_complex_creal(z), &re, &im);
    return _Basic_Complex_RoundDouble(im, -re);
}

// Compute the sine of z, as -i csinh(iz), in long double.
float _Complex __basic_complex_csinf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(-__basic_complex_cimagf(z), __basic_complex_crealf(z), &re, &im);
    return _Basic_Complex_RoundFloat(im, -re);
}

// Compute the sine of z, as -i csinh(iz).
long double _Complex __basic_complex_csinl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(-__basic_complex_cimagl(z), __basic_complex_creall(z), &re, &im);
    return _Basic_Complex_RoundLDouble(im, -re);
}

// Compute the hyperbolic sine of z, in long double.
double _Complex __basic_complex_csinh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the hyperbolic sine of z, in long double.
float _Complex __basic_complex_csinhf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the hyperbolic sine of z.
long double _Complex __basic_complex_csinhl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSinh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the square root of z, in the right half-plane, in long double.
double _Complex __basic_complex_csqrt(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSqrt(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the square root of z, in the right half-plane, in long double.
float _Complex __basic_complex_csqrtf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSqrt(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the square root of z, in the right half-plane.
long double _Complex __basic_complex_csqrtl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeSqrt(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
}

// Compute the tangent of z, as -i ctanh(iz), in long double.
double _Complex __basic_complex_ctan(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(-__basic_complex_cimag(z), __basic_complex_creal(z), &re, &im);
    return _Basic_Complex_RoundDouble(im, -re);
}

// Compute the tangent of z, as -i ctanh(iz), in long double.
float _Complex __basic_complex_ctanf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(-__basic_complex_cimagf(z), __basic_complex_crealf(z), &re, &im);
    return _Basic_Complex_RoundFloat(im, -re);
}

// Compute the tangent of z, as -i ctanh(iz).
long double _Complex __basic_complex_ctanl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(-__basic_complex_cimagl(z), __basic_complex_creall(z), &re, &im);
    return _Basic_Complex_RoundLDouble(im, -re);
}

// Compute the hyperbolic tangent of z, in long double.
double _Complex __basic_complex_ctanh(double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(__basic_complex_creal(z), __basic_complex_cimag(z), &re, &im);
    return _Basic_Complex_RoundDouble(re, im);
}

// Compute the hyperbolic tangent of z, in long double.
float _Complex __basic_complex_ctanhf(float _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(__basic_complex_crealf(z), __basic_complex_cimagf(z), &re, &im);
    return _Basic_Complex_RoundFloat(re, im);
}

// Compute the hyperbolic tangent of z.
long double _Complex __basic_complex_ctanhl(long double _Complex z)
{
    long double re = 0;
    long double im = 0;

    _Basic_Complex_TakeTanh(__basic_complex_creall(z), __basic_complex_cimagl(z), &re, &im);
    return _Basic_Complex_RoundLDouble(re, im);
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
