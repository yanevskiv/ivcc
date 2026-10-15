// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <tgmath.h>'s macros of a complex function alone.

// Include helpers.
#include "libm04_00_tgmath_helpers.inc"

// Defines.
#define CHECK_PART(m, mf, md, ml)                                              \
    _TEST_INT(KIND(m(arg_f)), KIND_FLOAT);                                     \
    _TEST_INT(KIND(m(arg_d)), KIND_DOUBLE);                                    \
    _TEST_INT(KIND(m(arg_l)), KIND_LDOUBLE);                                   \
    _TEST_INT(KIND(m(arg_n)), KIND_DOUBLE);                                    \
    _TEST_INT(KIND(m(arg_cf)), KIND_FLOAT);                                    \
    _TEST_INT(KIND(m(arg_cd)), KIND_DOUBLE);                                   \
    _TEST_INT(KIND(m(arg_cl)), KIND_LDOUBLE);                                  \
    _TEST_TRUE(SAME(m(arg_f), (mf)(arg_f), float));                            \
    _TEST_TRUE(SAME(m(arg_n), (md)(arg_n), double));                           \
    _TEST_TRUE(SAME(m(arg_cf), (mf)(arg_cf), float));                          \
    _TEST_TRUE(SAME(m(arg_cd), (md)(arg_cd), double));                         \
    _TEST_TRUE(SAME(m(arg_cl), (ml)(arg_cl), ldouble))
#define CHECK_WHOLE(m, mf, md, ml)                                             \
    _TEST_INT(KIND(m(arg_f)), KIND_FLOAT_COMPLEX);                             \
    _TEST_INT(KIND(m(arg_d)), KIND_DOUBLE_COMPLEX);                            \
    _TEST_INT(KIND(m(arg_l)), KIND_LDOUBLE_COMPLEX);                           \
    _TEST_INT(KIND(m(arg_n)), KIND_DOUBLE_COMPLEX);                            \
    _TEST_INT(KIND(m(arg_cf)), KIND_FLOAT_COMPLEX);                            \
    _TEST_INT(KIND(m(arg_cd)), KIND_DOUBLE_COMPLEX);                           \
    _TEST_INT(KIND(m(arg_cl)), KIND_LDOUBLE_COMPLEX);                          \
    _TEST_TRUE(SAME(m(arg_f), (mf)(arg_f), cfloat));                           \
    _TEST_TRUE(SAME(m(arg_n), (md)(arg_n), cdouble));                          \
    _TEST_TRUE(SAME(m(arg_cf), (mf)(arg_cf), cfloat));                         \
    _TEST_TRUE(SAME(m(arg_cd), (md)(arg_cd), cdouble));                        \
    _TEST_TRUE(SAME(m(arg_cl), (ml)(arg_cl), cldouble))

// Each macro of a complex function alone should invoke it in the type its
// argument has, a real argument's being of its complex type, an integer's
// double complex; carg, cimag and creal give a real result.
// [C99:7.22p3]: long double if any is, else double if any is or is an integer, else float
// [C99:7.22p6]: carg, cimag, conj, cproj and creal, a complex function for any argument
static void Test_TgmathComplexOnly(void)
{
    float                arg_f = -2.5f;
    double               arg_d = 0.75;
    long double          arg_l = -1.25L;
    int                  arg_n = -3;
    float _Complex       arg_cf = make_float(0.5f, -0.25f);
    double _Complex      arg_cd = make_double(-0.25, 1.5);
    long double _Complex arg_cl = make_ldouble(1.25L, -0.5L);

    CHECK_PART(carg, cargf, carg, cargl);
    CHECK_PART(cimag, cimagf, cimag, cimagl);
    CHECK_PART(creal, crealf, creal, creall);
    CHECK_WHOLE(conj, conjf, conj, conjl);
    CHECK_WHOLE(cproj, cprojf, cproj, cprojl);

    _TEST_TRUE(SAME(carg(arg_l), 0xc.90fdaa22168c235p-2L, ldouble));
    _TEST_TRUE(SAME(creal(arg_l), arg_l, ldouble));
    _TEST_TRUE(SAME(cimag(arg_cl), -0.5L, ldouble));
}

int main(void)
{
    Test_TgmathComplexOnly();
    return _Test_Status();
}
