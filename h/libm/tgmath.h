/*
 * C header file for type-generic math.
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


#ifndef _TGMATH_H
#define _TGMATH_H

// Type-generic math
// [C99:7.22p1]: <tgmath.h>, including <math.h> and <complex.h>
#include <math.h>
#include <complex.h>

// The zero of the type a generic argument counts as, an integer's double's.
// [C99:7.22p2]: generic parameters, those whose real type is double
// [C99:7.22p3]: long double if any is, else double if any is or is an integer, else float
#define _TGMATH_INTEGERS(value)  \
    _Bool:              (value), \
    char:               (value), \
    signed char:        (value), \
    unsigned char:      (value), \
    short:              (value), \
    unsigned short:     (value), \
    int:                (value), \
    unsigned int:       (value), \
    long:               (value), \
    unsigned long:      (value), \
    long long:          (value), \
    unsigned long long: (value)
#define _TGMATH_REAL(x) _Generic((x), float: 0.0f, double: 0.0, long double: 0.0L, _TGMATH_INTEGERS(0.0))
#define _TGMATH_ANY(x)  _Generic((x), float: 0.0f, double: 0.0, long double: 0.0L, float _Complex: (float _Complex) 0, double _Complex: (double _Complex) 0, long double _Complex: (long double _Complex) 0, _TGMATH_INTEGERS(0.0))

// The function of the type the zeros of a macro's generic arguments sum to.
#define _TGMATH_PICK_REAL(t, f, d, l)            _Generic((t), float: f, double: d, long double: l)
#define _TGMATH_PICK_ANY(t, f, d, l, cf, cd, cl) _Generic((t), float: f, double: d, long double: l, float _Complex: cf, double _Complex: cd, long double _Complex: cl)
#define _TGMATH_PICK_COMPLEX(t, cf, cd, cl)      _Generic((t), float: cf, double: cd, long double: cl, float _Complex: cf, double _Complex: cd, long double _Complex: cl)

// The macros of a real and a complex function each
// [C99:7.22p4]: one macro for f and cf, named f, fabs for fabs and cabs
#define acos(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), acosf, acos, acosl, cacosf, cacos, cacosl)(x)
#define asin(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), asinf, asin, asinl, casinf, casin, casinl)(x)
#define atan(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), atanf, atan, atanl, catanf, catan, catanl)(x)
#define acosh(x)  _TGMATH_PICK_ANY(_TGMATH_ANY(x), acoshf, acosh, acoshl, cacoshf, cacosh, cacoshl)(x)
#define asinh(x)  _TGMATH_PICK_ANY(_TGMATH_ANY(x), asinhf, asinh, asinhl, casinhf, casinh, casinhl)(x)
#define atanh(x)  _TGMATH_PICK_ANY(_TGMATH_ANY(x), atanhf, atanh, atanhl, catanhf, catanh, catanhl)(x)
#define cos(x)    _TGMATH_PICK_ANY(_TGMATH_ANY(x), cosf, cos, cosl, ccosf, ccos, ccosl)(x)
#define sin(x)    _TGMATH_PICK_ANY(_TGMATH_ANY(x), sinf, sin, sinl, csinf, csin, csinl)(x)
#define tan(x)    _TGMATH_PICK_ANY(_TGMATH_ANY(x), tanf, tan, tanl, ctanf, ctan, ctanl)(x)
#define cosh(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), coshf, cosh, coshl, ccoshf, ccosh, ccoshl)(x)
#define sinh(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), sinhf, sinh, sinhl, csinhf, csinh, csinhl)(x)
#define tanh(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), tanhf, tanh, tanhl, ctanhf, ctanh, ctanhl)(x)
#define exp(x)    _TGMATH_PICK_ANY(_TGMATH_ANY(x), expf, exp, expl, cexpf, cexp, cexpl)(x)
#define log(x)    _TGMATH_PICK_ANY(_TGMATH_ANY(x), logf, log, logl, clogf, clog, clogl)(x)
#define pow(x, y) _TGMATH_PICK_ANY(_TGMATH_ANY(x) + _TGMATH_ANY(y), powf, pow, powl, cpowf, cpow, cpowl)(x, y)
#define sqrt(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), sqrtf, sqrt, sqrtl, csqrtf, csqrt, csqrtl)(x)
#define fabs(x)   _TGMATH_PICK_ANY(_TGMATH_ANY(x), fabsf, fabs, fabsl, cabsf, cabs, cabsl)(x)

// The macros of a real function alone
// [C99:7.22p5]: one macro for each real function with no complex one, but modf
#define atan2(y, x)       _TGMATH_PICK_REAL(_TGMATH_REAL(y) + _TGMATH_REAL(x), atan2f, atan2, atan2l)(y, x)
#define cbrt(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), cbrtf, cbrt, cbrtl)(x)
#define ceil(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), ceilf, ceil, ceill)(x)
#define copysign(x, y)    _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), copysignf, copysign, copysignl)(x, y)
#define erf(x)            _TGMATH_PICK_REAL(_TGMATH_REAL(x), erff, erf, erfl)(x)
#define erfc(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), erfcf, erfc, erfcl)(x)
#define exp2(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), exp2f, exp2, exp2l)(x)
#define expm1(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), expm1f, expm1, expm1l)(x)
#define fdim(x, y)        _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), fdimf, fdim, fdiml)(x, y)
#define floor(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), floorf, floor, floorl)(x)
#define fma(x, y, z)      _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y) + _TGMATH_REAL(z), fmaf, fma, fmal)(x, y, z)
#define fmax(x, y)        _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), fmaxf, fmax, fmaxl)(x, y)
#define fmin(x, y)        _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), fminf, fmin, fminl)(x, y)
#define fmod(x, y)        _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), fmodf, fmod, fmodl)(x, y)
#define frexp(x, exp)     _TGMATH_PICK_REAL(_TGMATH_REAL(x), frexpf, frexp, frexpl)(x, exp)
#define hypot(x, y)       _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), hypotf, hypot, hypotl)(x, y)
#define ilogb(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), ilogbf, ilogb, ilogbl)(x)
#define ldexp(x, exp)     _TGMATH_PICK_REAL(_TGMATH_REAL(x), ldexpf, ldexp, ldexpl)(x, exp)
#define lgamma(x)         _TGMATH_PICK_REAL(_TGMATH_REAL(x), lgammaf, lgamma, lgammal)(x)
#define llrint(x)         _TGMATH_PICK_REAL(_TGMATH_REAL(x), llrintf, llrint, llrintl)(x)
#define llround(x)        _TGMATH_PICK_REAL(_TGMATH_REAL(x), llroundf, llround, llroundl)(x)
#define log10(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), log10f, log10, log10l)(x)
#define log1p(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), log1pf, log1p, log1pl)(x)
#define log2(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), log2f, log2, log2l)(x)
#define logb(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), logbf, logb, logbl)(x)
#define lrint(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), lrintf, lrint, lrintl)(x)
#define lround(x)         _TGMATH_PICK_REAL(_TGMATH_REAL(x), lroundf, lround, lroundl)(x)
#define nearbyint(x)      _TGMATH_PICK_REAL(_TGMATH_REAL(x), nearbyintf, nearbyint, nearbyintl)(x)
#define nextafter(x, y)   _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), nextafterf, nextafter, nextafterl)(x, y)
#define nexttoward(x, y)  _TGMATH_PICK_REAL(_TGMATH_REAL(x), nexttowardf, nexttoward, nexttowardl)(x, y)
#define remainder(x, y)   _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), remainderf, remainder, remainderl)(x, y)
#define remquo(x, y, quo) _TGMATH_PICK_REAL(_TGMATH_REAL(x) + _TGMATH_REAL(y), remquof, remquo, remquol)(x, y, quo)
#define rint(x)           _TGMATH_PICK_REAL(_TGMATH_REAL(x), rintf, rint, rintl)(x)
#define round(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), roundf, round, roundl)(x)
#define scalbn(x, n)      _TGMATH_PICK_REAL(_TGMATH_REAL(x), scalbnf, scalbn, scalbnl)(x, n)
#define scalbln(x, n)     _TGMATH_PICK_REAL(_TGMATH_REAL(x), scalblnf, scalbln, scalblnl)(x, n)
#define tgamma(x)         _TGMATH_PICK_REAL(_TGMATH_REAL(x), tgammaf, tgamma, tgammal)(x)
#define trunc(x)          _TGMATH_PICK_REAL(_TGMATH_REAL(x), truncf, trunc, truncl)(x)

// The macros of a complex function alone
// [C99:7.22p6]: carg, cimag, conj, cproj and creal, a complex function for any argument
#define carg(x)  _TGMATH_PICK_COMPLEX(_TGMATH_ANY(x), cargf, carg, cargl)(x)
#define cimag(x) _TGMATH_PICK_COMPLEX(_TGMATH_ANY(x), cimagf, cimag, cimagl)(x)
#define conj(x)  _TGMATH_PICK_COMPLEX(_TGMATH_ANY(x), conjf, conj, conjl)(x)
#define cproj(x) _TGMATH_PICK_COMPLEX(_TGMATH_ANY(x), cprojf, cproj, cprojl)(x)
#define creal(x) _TGMATH_PICK_COMPLEX(_TGMATH_ANY(x), crealf, creal, creall)(x)

#endif // _TGMATH_H
