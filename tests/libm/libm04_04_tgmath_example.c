// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <tgmath.h>, C99's own example.

// Include helpers.
#include "libm04_00_tgmath_helpers.inc"

// Each use in C99's example should invoke the function its table names, each
// a result of that function's type and value; the rows of undefined
// behaviour are left out.
// [C99:7.22p7]: the functions a use of each type-generic macro invokes
static void Test_TgmathExample(void)
{
    int                  n = 2;
    float                f = 1.5f;
    double               d = 0.25;
    long double          ld = 0.75L;
    float _Complex       fc = make_float(0.5f, 2);
    double _Complex      dc = make_double(-3, 4);
    long double _Complex ldc = make_ldouble(0.25L, -1);

    _TEST_INT(KIND(exp(n)), KIND_DOUBLE);
    _TEST_TRUE(SAME(exp(n), (exp)(n), double));
    _TEST_INT(KIND(acosh(f)), KIND_FLOAT);
    _TEST_TRUE(SAME(acosh(f), acoshf(f), float));
    _TEST_INT(KIND(sin(d)), KIND_DOUBLE);
    _TEST_TRUE(SAME(sin(d), (sin)(d), double));
    _TEST_INT(KIND(atan(ld)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(atan(ld), atanl(ld), ldouble));
    _TEST_INT(KIND(log(fc)), KIND_FLOAT_COMPLEX);
    _TEST_TRUE(SAME(log(fc), clogf(fc), cfloat));
    _TEST_INT(KIND(sqrt(dc)), KIND_DOUBLE_COMPLEX);
    _TEST_TRUE(SAME(sqrt(dc), csqrt(dc), cdouble));
    _TEST_INT(KIND(pow(ldc, f)), KIND_LDOUBLE_COMPLEX);
    _TEST_TRUE(SAME(pow(ldc, f), cpowl(ldc, f), cldouble));
    _TEST_INT(KIND(remainder(n, n)), KIND_DOUBLE);
    _TEST_TRUE(SAME(remainder(n, n), (remainder)(n, n), double));
    _TEST_INT(KIND(nextafter(d, f)), KIND_DOUBLE);
    _TEST_TRUE(SAME(nextafter(d, f), (nextafter)(d, f), double));
    _TEST_INT(KIND(nexttoward(f, ld)), KIND_FLOAT);
    _TEST_TRUE(SAME(nexttoward(f, ld), nexttowardf(f, ld), float));
    _TEST_INT(KIND(copysign(n, ld)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(copysign(n, ld), copysignl(n, ld), ldouble));
    _TEST_INT(KIND(carg(n)), KIND_DOUBLE);
    _TEST_TRUE(SAME(carg(n), (carg)(n), double));
    _TEST_INT(KIND(cproj(f)), KIND_FLOAT_COMPLEX);
    _TEST_TRUE(SAME(cproj(f), cprojf(f), cfloat));
    _TEST_INT(KIND(creal(d)), KIND_DOUBLE);
    _TEST_TRUE(SAME(creal(d), (creal)(d), double));
    _TEST_INT(KIND(cimag(ld)), KIND_LDOUBLE);
    _TEST_TRUE(SAME(cimag(ld), cimagl(ld), ldouble));
    _TEST_INT(KIND(fabs(fc)), KIND_FLOAT);
    _TEST_TRUE(SAME(fabs(fc), cabsf(fc), float));
    _TEST_INT(KIND(carg(dc)), KIND_DOUBLE);
    _TEST_TRUE(SAME(carg(dc), (carg)(dc), double));
    _TEST_INT(KIND(cproj(ldc)), KIND_LDOUBLE_COMPLEX);
    _TEST_TRUE(SAME(cproj(ldc), cprojl(ldc), cldouble));
}

int main(void)
{
    Test_TgmathExample();
    return _Test_Status();
}
