// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <tgmath.h>'s macros of a real and a complex function.

// Include helpers.
#include "libm04_00_tgmath_helpers.inc"

// Defines.
#define CHECK_REAL(m, mf, md, ml)                                              \
    _TEST_INT(KIND(m(arg_f)), KIND_FLOAT);                                     \
    _TEST_INT(KIND(m(arg_d)), KIND_DOUBLE);                                    \
    _TEST_INT(KIND(m(arg_l)), KIND_LDOUBLE);                                   \
    _TEST_INT(KIND(m(arg_n)), KIND_DOUBLE);                                    \
    _TEST_TRUE(SAME(m(arg_f), (mf)(arg_f), float));                            \
    _TEST_TRUE(SAME(m(arg_d), (md)(arg_d), double));                           \
    _TEST_TRUE(SAME(m(arg_l), (ml)(arg_l), ldouble));                          \
    _TEST_TRUE(SAME(m(arg_n), (md)(arg_n), double))
#define CHECK_COMPLEX(m, mf, md, ml)                                           \
    _TEST_INT(KIND(m(arg_cf)), KIND_FLOAT_COMPLEX);                            \
    _TEST_INT(KIND(m(arg_cd)), KIND_DOUBLE_COMPLEX);                           \
    _TEST_INT(KIND(m(arg_cl)), KIND_LDOUBLE_COMPLEX);                          \
    _TEST_TRUE(SAME(m(arg_cf), (mf)(arg_cf), cfloat));                         \
    _TEST_TRUE(SAME(m(arg_cd), (md)(arg_cd), cdouble));                        \
    _TEST_TRUE(SAME(m(arg_cl), (ml)(arg_cl), cldouble))
#define CHECK_PAIR(m, mf, ml, cmf, cm, cml)                                    \
    CHECK_REAL(m, mf, m, ml);                                                  \
    CHECK_COMPLEX(m, cmf, cm, cml)

// Each macro of a real and a complex function should invoke the real one of
// the type its argument has, an integer's being double, and the complex one
// of a complex argument's type; fabs's complex one is cabs.
// [C99:7.22p2]: generic parameters, those whose real type is double
// [C99:7.22p3]: long double if any is, else double if any is or is an integer, else float
// [C99:7.22p4]: one macro for f and cf, named f, fabs for fabs and cabs
static void Test_TgmathComplexPairs(void)
{
    float                arg_f = 0.5f;
    double               arg_d = 0.25;
    long double          arg_l = 0.75L;
    int                  arg_n = 2;
    float _Complex       arg_cf = make_float(0.5f, 0.25f);
    double _Complex      arg_cd = make_double(-0.25, 1.5);
    long double _Complex arg_cl = make_ldouble(1.25L, -0.5L);

    CHECK_PAIR(acos, acosf, acosl, cacosf, cacos, cacosl);
    CHECK_PAIR(asin, asinf, asinl, casinf, casin, casinl);
    CHECK_PAIR(atan, atanf, atanl, catanf, catan, catanl);
    CHECK_PAIR(acosh, acoshf, acoshl, cacoshf, cacosh, cacoshl);
    CHECK_PAIR(asinh, asinhf, asinhl, casinhf, casinh, casinhl);
    CHECK_PAIR(atanh, atanhf, atanhl, catanhf, catanh, catanhl);
    CHECK_PAIR(cos, cosf, cosl, ccosf, ccos, ccosl);
    CHECK_PAIR(sin, sinf, sinl, csinf, csin, csinl);
    CHECK_PAIR(tan, tanf, tanl, ctanf, ctan, ctanl);
    CHECK_PAIR(cosh, coshf, coshl, ccoshf, ccosh, ccoshl);
    CHECK_PAIR(sinh, sinhf, sinhl, csinhf, csinh, csinhl);
    CHECK_PAIR(tanh, tanhf, tanhl, ctanhf, ctanh, ctanhl);
    CHECK_PAIR(exp, expf, expl, cexpf, cexp, cexpl);
    CHECK_PAIR(log, logf, logl, clogf, clog, clogl);
    CHECK_PAIR(sqrt, sqrtf, sqrtl, csqrtf, csqrt, csqrtl);

    CHECK_REAL(fabs, fabsf, fabs, fabsl);
    _TEST_INT(KIND(fabs(arg_cf)), KIND_FLOAT);
    _TEST_INT(KIND(fabs(arg_cd)), KIND_DOUBLE);
    _TEST_INT(KIND(fabs(arg_cl)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(fabs(arg_cf), cabsf(arg_cf), float));
    _TEST_TRUE(SAME(fabs(arg_cd), cabs(arg_cd), double));
    _TEST_TRUE(SAME(fabs(arg_cl), cabsl(arg_cl), ldouble));

    _TEST_INT(KIND(pow(arg_f, arg_f)), KIND_FLOAT);
    _TEST_INT(KIND(pow(arg_f, arg_n)), KIND_DOUBLE);
    _TEST_INT(KIND(pow(arg_d, arg_l)), KIND_LDOUBLE);
    _TEST_INT(KIND(pow(arg_cf, arg_f)), KIND_FLOAT_COMPLEX);
    _TEST_INT(KIND(pow(arg_f, arg_cd)), KIND_DOUBLE_COMPLEX);
    _TEST_INT(KIND(pow(arg_cf, arg_l)), KIND_LDOUBLE_COMPLEX);
    _TEST_TRUE(SAME(pow(arg_f, arg_f), powf(arg_f, arg_f), float));
    _TEST_TRUE(SAME(pow(arg_f, arg_n), (pow)(arg_f, arg_n), double));
    _TEST_TRUE(SAME(pow(arg_d, arg_l), powl(arg_d, arg_l), ldouble));
    _TEST_TRUE(SAME(pow(arg_cf, arg_f), cpowf(arg_cf, arg_f), cfloat));
    _TEST_TRUE(SAME(pow(arg_f, arg_cd), cpow(arg_f, arg_cd), cdouble));
    _TEST_TRUE(SAME(pow(arg_cf, arg_l), cpowl(arg_cf, arg_l), cldouble));
}

int main(void)
{
    Test_TgmathComplexPairs();
    return _Test_Status();
}
