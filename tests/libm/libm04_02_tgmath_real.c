// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <tgmath.h>'s macros of a real function alone.

// Include helpers.
#include "libm04_00_tgmath_helpers.inc"

// Defines.
#define CHECK_ONE(m, mf, md, ml)                                               \
    _TEST_INT(KIND(m(arg_f)), KIND_FLOAT);                                     \
    _TEST_INT(KIND(m(arg_d)), KIND_DOUBLE);                                    \
    _TEST_INT(KIND(m(arg_l)), KIND_LDOUBLE);                                   \
    _TEST_INT(KIND(m(arg_n)), KIND_DOUBLE);                                    \
    _TEST_TRUE(SAME(m(arg_f), (mf)(arg_f), float));                            \
    _TEST_TRUE(SAME(m(arg_d), (md)(arg_d), double));                           \
    _TEST_TRUE(SAME(m(arg_l), (ml)(arg_l), ldouble));                          \
    _TEST_TRUE(SAME(m(arg_n), (md)(arg_n), double))
#define CHECK_TWO(m, mf, md, ml)                                               \
    _TEST_INT(KIND(m(arg_f, arg_f)), KIND_FLOAT);                              \
    _TEST_INT(KIND(m(arg_f, arg_d)), KIND_DOUBLE);                             \
    _TEST_INT(KIND(m(arg_n, arg_f)), KIND_DOUBLE);                             \
    _TEST_INT(KIND(m(arg_d, arg_l)), KIND_LDOUBLE);                            \
    _TEST_INT(KIND(m(arg_l, arg_n)), KIND_LDOUBLE);                            \
    _TEST_TRUE(SAME(m(arg_f, arg_f), (mf)(arg_f, arg_f), float));              \
    _TEST_TRUE(SAME(m(arg_f, arg_d), (md)(arg_f, arg_d), double));             \
    _TEST_TRUE(SAME(m(arg_n, arg_f), (md)(arg_n, arg_f), double));             \
    _TEST_TRUE(SAME(m(arg_d, arg_l), (ml)(arg_d, arg_l), ldouble));            \
    _TEST_TRUE(SAME(m(arg_l, arg_n), (ml)(arg_l, arg_n), ldouble))
#define CHECK_INTEGER(m, mf, md, ml)                                           \
    _TEST_TRUE(m(arg_f) == (mf)(arg_f));                                       \
    _TEST_TRUE(m(arg_d) == (md)(arg_d));                                       \
    _TEST_TRUE(m(arg_l) == (ml)(arg_l));                                       \
    _TEST_TRUE(m(arg_n) == (md)(arg_n))

// Each macro of a real function alone should invoke the one of the type its
// generic arguments determine: long double if any is, else double if any is
// or is an integer, else float. A parameter that is not generic keeps its type.
// [C99:7.22p2]: generic parameters, those whose real type is double
// [C99:7.22p3]: long double if any is, else double if any is or is an integer, else float
// [C99:7.22p5]: one macro for each real function with no complex one, but modf
static void Test_TgmathReal(void)
{
    float       arg_f = 2.5f;
    double      arg_d = 0.75;
    long double arg_l = 1.25L;
    int         arg_n = 3;
    long double tie = 0.5L + 0x1p-60L;
    long double below = 0.5L - 0x1p-64L;
    long double tiny = 0x1p-16000L;
    int         exp_f = 0;
    int         exp_l = 0;
    int         quo_f = 0;
    int         quo_l = 0;

    CHECK_ONE(cbrt, cbrtf, cbrt, cbrtl);
    CHECK_ONE(ceil, ceilf, ceil, ceill);
    CHECK_ONE(erf, erff, erf, erfl);
    CHECK_ONE(erfc, erfcf, erfc, erfcl);
    CHECK_ONE(exp2, exp2f, exp2, exp2l);
    CHECK_ONE(expm1, expm1f, expm1, expm1l);
    CHECK_ONE(floor, floorf, floor, floorl);
    CHECK_ONE(lgamma, lgammaf, lgamma, lgammal);
    CHECK_ONE(log10, log10f, log10, log10l);
    CHECK_ONE(log1p, log1pf, log1p, log1pl);
    CHECK_ONE(log2, log2f, log2, log2l);
    CHECK_ONE(logb, logbf, logb, logbl);
    CHECK_ONE(nearbyint, nearbyintf, nearbyint, nearbyintl);
    CHECK_ONE(rint, rintf, rint, rintl);
    CHECK_ONE(round, roundf, round, roundl);
    CHECK_ONE(tgamma, tgammaf, tgamma, tgammal);
    CHECK_ONE(trunc, truncf, trunc, truncl);

    CHECK_TWO(atan2, atan2f, atan2, atan2l);
    CHECK_TWO(copysign, copysignf, copysign, copysignl);
    CHECK_TWO(fdim, fdimf, fdim, fdiml);
    CHECK_TWO(fmax, fmaxf, fmax, fmaxl);
    CHECK_TWO(fmin, fminf, fmin, fminl);
    CHECK_TWO(fmod, fmodf, fmod, fmodl);
    CHECK_TWO(hypot, hypotf, hypot, hypotl);
    CHECK_TWO(nextafter, nextafterf, nextafter, nextafterl);
    CHECK_TWO(remainder, remainderf, remainder, remainderl);

    _TEST_INT(KIND(fma(arg_f, arg_f, arg_f)), KIND_FLOAT);
    _TEST_INT(KIND(fma(arg_f, arg_f, arg_n)), KIND_DOUBLE);
    _TEST_INT(KIND(fma(arg_f, arg_l, arg_d)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(fma(arg_f, arg_f, arg_f), fmaf(arg_f, arg_f, arg_f), float));
    _TEST_TRUE(SAME(fma(arg_f, arg_f, arg_n), (fma)(arg_f, arg_f, arg_n), double));
    _TEST_TRUE(SAME(fma(arg_f, arg_l, arg_d), fmal(arg_f, arg_l, arg_d), ldouble));

    _TEST_INT(KIND(frexp(arg_f, &exp_f)), KIND_FLOAT);
    _TEST_INT(KIND(frexp(arg_l, &exp_l)), KIND_LDOUBLE);
    _TEST_TRUE(frexp(arg_f, &exp_f) == 0.625f && exp_f == 2);
    _TEST_TRUE(frexp(tiny, &exp_l) == 0.5L && exp_l == -15999);
    _TEST_INT(KIND(ldexp(arg_f, 2)), KIND_FLOAT);
    _TEST_INT(KIND(ldexp(arg_n, 2)), KIND_DOUBLE);
    _TEST_TRUE(SAME(ldexp(tiny, 100), 0x1p-15900L, ldouble));
    _TEST_INT(KIND(scalbn(arg_f, 2)), KIND_FLOAT);
    _TEST_INT(KIND(scalbn(arg_l, 2)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(scalbn(arg_d, 2), 3.0, double));
    _TEST_INT(KIND(scalbln(arg_f, 2L)), KIND_FLOAT);
    _TEST_INT(KIND(scalbln(arg_d, 2L)), KIND_DOUBLE);
    _TEST_TRUE(SAME(scalbln(arg_l, -2L), 0.3125L, ldouble));
    _TEST_INT(KIND(nexttoward(arg_f, arg_l)), KIND_FLOAT);
    _TEST_INT(KIND(nexttoward(arg_d, arg_l)), KIND_DOUBLE);
    _TEST_INT(KIND(nexttoward(arg_l, arg_d)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(nexttoward(arg_f, arg_l), nexttowardf(arg_f, arg_l), float));
    _TEST_INT(KIND(remquo(arg_f, arg_f, &quo_f)), KIND_FLOAT);
    _TEST_INT(KIND(remquo(arg_l, arg_f, &quo_l)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(remquo(arg_l, arg_d, &quo_l), remquol(arg_l, arg_d, &quo_f), ldouble));
    _TEST_INT(quo_l, quo_f);

    CHECK_INTEGER(ilogb, ilogbf, ilogb, ilogbl);
    CHECK_INTEGER(llrint, llrintf, llrint, llrintl);
    CHECK_INTEGER(llround, llroundf, llround, llroundl);
    CHECK_INTEGER(lrint, lrintf, lrint, lrintl);
    CHECK_INTEGER(lround, lroundf, lround, lroundl);
    _TEST_INT(ilogb(tiny), -16000);
    _TEST_TRUE(llrint(tie) == 1 && lrint(tie) == 1);
    _TEST_TRUE(llround(below) == 0 && lround(below) == 0);
}

int main(void)
{
    Test_TgmathReal();
    return _Test_Status();
}
