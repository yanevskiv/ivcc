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

// The bounds a double's division scales its operands by, as libgcc's.
#define _BASIC_COMPLEX_DBL_BIG     0x1.fffffffffffffp+1022
#define _BASIC_COMPLEX_DBL_MIN     0x1p-1022
#define _BASIC_COMPLEX_DBL_EPS     0x1p-52
#define _BASIC_COMPLEX_DBL_SCALE   0x1p52
#define _BASIC_COMPLEX_DBL_BIG_EPS 0x1.fffffffffffffp+970

// The bounds a long double's division scales its operands by, as libgcc's.
#define _BASIC_COMPLEX_LDBL_BIG     (_LDOUBLE_MAX / 2)
#define _BASIC_COMPLEX_LDBL_MIN     _LDOUBLE_MIN
#define _BASIC_COMPLEX_LDBL_EPS     _LDOUBLE_EPSILON
#define _BASIC_COMPLEX_LDBL_SCALE   (1 / _LDOUBLE_EPSILON)
#define _BASIC_COMPLEX_LDBL_BIG_EPS (_LDOUBLE_MAX / 2 * _LDOUBLE_EPSILON)

// The factor that halves the operands of a division near the largest value.
#define _BASIC_COMPLEX_HALF 0.5

// The magnitude below which the sine of y is y and its cosine 1.
#define _BASIC_COMPLEX_TRIG_TINY 0x1p-33L

// The ratio of the parts below which the smaller one's square is lost in |z|.
#define _BASIC_COMPLEX_RATIO_TINY 0x1p-40L

// The band of the larger part in which ln |z| is half log1p of x^2 + y^2 - 1.
#define _BASIC_COMPLEX_LOG_NEAR_LOW  0.5L
#define _BASIC_COMPLEX_LOG_NEAR_HIGH 2.0L

// The magnitude of x^2 + y^2 - 1 below which it is summed exactly.
#define _BASIC_COMPLEX_LOG_EXACT 0x1p-40L

// The smaller part below which its square is lost but where the larger is 1.
#define _BASIC_COMPLEX_LOG_SQUARE 0x1p-8000L

// The magnitudes between which a square root's parts are squared unscaled.
#define _BASIC_COMPLEX_ROOT_HUGE 0x1p8000L
#define _BASIC_COMPLEX_ROOT_TINY 0x1p-8000L

// A quarter and three quarters of pi, the angles of an infinity's diagonals.
#define _BASIC_COMPLEX_QUARTER_PI       0xc.90fdaa22168c235p-4L
#define _BASIC_COMPLEX_THREE_QUARTER_PI 0x9.6cbe3f9990e91a8p-2L

// The magnitudes above which casinh(z) is ln 2z and below which it is z.
#define _BASIC_COMPLEX_ARC_HUGE 0x1p63L
#define _BASIC_COMPLEX_ARC_TINY 0x1p-33L

// Hull's crossovers for A - 1 summed of its parts and the angle from its sides.
#define _BASIC_COMPLEX_ARC_CROSS_A 10.0L
#define _BASIC_COMPLEX_ARC_CROSS_B 0.6417L

// Hull's y below which y / A would underflow.
#define _BASIC_COMPLEX_ARC_FLOOR 0x1p-8189L

// The factors that lift an angle's sides from Hull's floor.
#define _BASIC_COMPLEX_ARC_LIFT       0x1p64L
#define _BASIC_COMPLEX_ARC_LIFT_TWICE 0x1p128L

// Hull's x below which A - 1 and A - y at y = 1 are of the order of root x.
#define _BASIC_COMPLEX_ARC_NEAR      0x1p-133L
#define _BASIC_COMPLEX_ARC_NEAR_SIDE 0x1p-70L

// A complex value of each type made of its two parts.
float _Complex       _Basic_Complex_JoinFloat(float x, float y);
double _Complex      _Basic_Complex_JoinDouble(double x, double y);
long double _Complex _Basic_Complex_JoinLDouble(long double x, long double y);

// An operand's part of * or /, an infinity boxed to 1 or a NaN cleared to 0.
long double _Basic_Complex_BoxInfinity(long double x);
long double _Basic_Complex_ClearNan(long double x);

// The operands of a division scaled by a power of 2.
void _Basic_Complex_ScaleDouble(double *a, double *b, double *c, double *d, double by);
void _Basic_Complex_ScaleLDouble(long double *a, long double *b, long double *c, long double *d, long double by);

// A NaN quotient x + iy made the infinity or zero G.5.1 asks for.
void _Basic_Complex_RecoverFloat(float a, float b, float c, float d, float *x, float *y);
void _Basic_Complex_RecoverDouble(double a, double b, double c, double d, double *x, double *y);
void _Basic_Complex_RecoverLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y);

// The quotient of a + ib by c + id by Smith's ratio, scaled where it must be.
void _Basic_Complex_DivideDouble(double a, double b, double c, double d, double *x, double *y);
void _Basic_Complex_DivideLDouble(long double a, long double b, long double c, long double d, long double *x, long double *y);

// A complex value of each type rounded from long double parts, tiny checked.
void                 _Basic_Complex_CheckTiny(long double x, long double least);
float _Complex       _Basic_Complex_RoundFloat(long double x, long double y);
double _Complex      _Basic_Complex_RoundDouble(long double x, long double y);
long double _Complex _Basic_Complex_RoundLDouble(long double x, long double y);

// The cores' shared steps: a NaN, a square's parts, x^2 + y^2 - 1, |z|, cis y.
long double _Basic_Complex_MakeNan(void);
long double _Basic_Complex_SquareParts(long double x, long double least, long double *low);
long double _Basic_Complex_SumUnitGap(long double a, long double b, long double least);
long double _Basic_Complex_TakeAbs(long double x, long double y, long double a);
void        _Basic_Complex_TakeSinCos(long double y, long double *s, long double *c);

// The exponential, logarithm, square root and power of x + iy in long double.
void        _Basic_Complex_TakeExp(long double x, long double y, long double *re, long double *im);
long double _Basic_Complex_TakeLogAbs(long double x, long double y);
void        _Basic_Complex_TakeLog(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeSqrt(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakePow(long double x, long double y, long double c, long double d, long double *re, long double *im);

// The hyperbolic functions of x + iy and their inverses in long double.
int         _Basic_Complex_TakeSinhCosh(long double a, long double *sh, long double *ch);
void        _Basic_Complex_TakeSinh(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeCosh(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeTanh(long double x, long double y, long double *re, long double *im);
long double _Basic_Complex_TakeHalfExcess(long double a, long double b, long double h);
long double _Basic_Complex_TakeArcParts(long double x, long double y, long double *top, long double *side);
void        _Basic_Complex_TakeAsinh(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeAsin(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeAcos(long double x, long double y, long double *re, long double *im);
void        _Basic_Complex_TakeAcosh(long double x, long double y, long double *re, long double *im);
long double _Basic_Complex_TakeInverseReal(long double x, long double y);
void        _Basic_Complex_TakeAtanh(long double x, long double y, long double *re, long double *im);

// The bodies of <complex.h>'s functions.
double               __basic_complex_cabs(double _Complex z);
float                __basic_complex_cabsf(float _Complex z);
long double          __basic_complex_cabsl(long double _Complex z);
double _Complex      __basic_complex_cacos(double _Complex z);
float _Complex       __basic_complex_cacosf(float _Complex z);
long double _Complex __basic_complex_cacosl(long double _Complex z);
double _Complex      __basic_complex_cacosh(double _Complex z);
float _Complex       __basic_complex_cacoshf(float _Complex z);
long double _Complex __basic_complex_cacoshl(long double _Complex z);
double               __basic_complex_carg(double _Complex z);
float                __basic_complex_cargf(float _Complex z);
long double          __basic_complex_cargl(long double _Complex z);
double _Complex      __basic_complex_casin(double _Complex z);
float _Complex       __basic_complex_casinf(float _Complex z);
long double _Complex __basic_complex_casinl(long double _Complex z);
double _Complex      __basic_complex_casinh(double _Complex z);
float _Complex       __basic_complex_casinhf(float _Complex z);
long double _Complex __basic_complex_casinhl(long double _Complex z);
double _Complex      __basic_complex_catan(double _Complex z);
float _Complex       __basic_complex_catanf(float _Complex z);
long double _Complex __basic_complex_catanl(long double _Complex z);
double _Complex      __basic_complex_catanh(double _Complex z);
float _Complex       __basic_complex_catanhf(float _Complex z);
long double _Complex __basic_complex_catanhl(long double _Complex z);
double _Complex      __basic_complex_ccos(double _Complex z);
float _Complex       __basic_complex_ccosf(float _Complex z);
long double _Complex __basic_complex_ccosl(long double _Complex z);
double _Complex      __basic_complex_ccosh(double _Complex z);
float _Complex       __basic_complex_ccoshf(float _Complex z);
long double _Complex __basic_complex_ccoshl(long double _Complex z);
double _Complex      __basic_complex_cexp(double _Complex z);
float _Complex       __basic_complex_cexpf(float _Complex z);
long double _Complex __basic_complex_cexpl(long double _Complex z);
double               __basic_complex_cimag(double _Complex z);
float                __basic_complex_cimagf(float _Complex z);
long double          __basic_complex_cimagl(long double _Complex z);
double _Complex      __basic_complex_clog(double _Complex z);
float _Complex       __basic_complex_clogf(float _Complex z);
long double _Complex __basic_complex_clogl(long double _Complex z);
double _Complex      __basic_complex_conj(double _Complex z);
float _Complex       __basic_complex_conjf(float _Complex z);
long double _Complex __basic_complex_conjl(long double _Complex z);
double _Complex      __basic_complex_cpow(double _Complex x, double _Complex y);
float _Complex       __basic_complex_cpowf(float _Complex x, float _Complex y);
long double _Complex __basic_complex_cpowl(long double _Complex x, long double _Complex y);
double _Complex      __basic_complex_cproj(double _Complex z);
float _Complex       __basic_complex_cprojf(float _Complex z);
long double _Complex __basic_complex_cprojl(long double _Complex z);
double               __basic_complex_creal(double _Complex z);
float                __basic_complex_crealf(float _Complex z);
long double          __basic_complex_creall(long double _Complex z);
double _Complex      __basic_complex_csin(double _Complex z);
float _Complex       __basic_complex_csinf(float _Complex z);
long double _Complex __basic_complex_csinl(long double _Complex z);
double _Complex      __basic_complex_csinh(double _Complex z);
float _Complex       __basic_complex_csinhf(float _Complex z);
long double _Complex __basic_complex_csinhl(long double _Complex z);
double _Complex      __basic_complex_csqrt(double _Complex z);
float _Complex       __basic_complex_csqrtf(float _Complex z);
long double _Complex __basic_complex_csqrtl(long double _Complex z);
double _Complex      __basic_complex_ctan(double _Complex z);
float _Complex       __basic_complex_ctanf(float _Complex z);
long double _Complex __basic_complex_ctanl(long double _Complex z);
double _Complex      __basic_complex_ctanh(double _Complex z);
float _Complex       __basic_complex_ctanhf(float _Complex z);
long double _Complex __basic_complex_ctanhl(long double _Complex z);

// The compiler's helpers for * and / of two complex values, as libgcc's.
float _Complex       __basic_complex_mulsc3(float a, float b, float c, float d);
double _Complex      __basic_complex_muldc3(double a, double b, double c, double d);
long double _Complex __basic_complex_mulxc3(long double a, long double b, long double c, long double d);
float _Complex       __basic_complex_divsc3(float a, float b, float c, float d);
double _Complex      __basic_complex_divdc3(double a, double b, double c, double d);
long double _Complex __basic_complex_divxc3(long double a, long double b, long double c, long double d);

#endif // _BASIC_COMPLEX_H
