// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cpow.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// cpow should give x to y within a few ulps in each type, the principal
// value by the cut of x along the negative real axis, and 1 of any finite
// nonzero x to a zero y.
// [C99:7.3.8.2p2]: cpow, a branch cut for x along the negative real axis
// [C99:G.6.4.1p1]: cpow, exceptions as its parts' calculation raises, footnote 327
static void Test_ComplexCpowValues(void)
{
    double complex d = cpow(make_double(1, 1), make_double(1, 1));
    double complex e = cpow(make_double(-8, 0), make_double(1.0 / 3, 0));
    double complex c = cpow(make_double(-8, -0.0), make_double(1.0 / 3, 0));
    float complex f = cpowf(make_float(1, 1), make_float(1, 1));
    long double complex l = cpowl(make_ldouble(1, 1), make_ldouble(1, 1));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.18884016cf327p-2, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.2adad36b098a9p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.bb67ae8584caap+0, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(e, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(e, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.18884p-2f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.2adad4p-1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x8.c44200b6799349cp-5L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x9.56d69b584c549dap-4L, LDBL_MANT_DIG, ULPS));

    d = cpow(make_double(2, 0), make_double(10, 0));
    _TEST_TRUE(within_ulps(REAL(d, double), 1024, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0);
    d = cpow(make_double(0, 1), make_double(2, 0));
    _TEST_TRUE(within_ulps(REAL(d, double), -1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(fabs(IMAG(d, double)) < 0x1p-50);

    d = cpow(make_double(3, -4), make_double(0, 0));
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_TRUE(IMAG(d, double) == 0);
    f = cpowf(make_float(-0.5f, 2), make_float(0, 0));
    _TEST_FLOAT(REAL(f, float), 1);
    _TEST_TRUE(IMAG(f, float) == 0);
}

// cpow of a zero to a positive real power should be a zero, and of an
// infinity or a NaN an infinity or a NaN, as cexp(y clog(x)) gives them.
// [C99:G.6.4.1p1]: cpow as cexp(y clog(x)), spurious exceptions allowed, footnote 327
static void Test_ComplexCpowSpecial(void)
{
    _TEST_TRUE(is_zero_double(cpow(make_double(0, 0), make_double(2, 0))));
    _TEST_TRUE(is_zero_ldouble(cpowl(make_ldouble(-0.0L, 0), make_ldouble(0.5L, 0))));
    _TEST_TRUE(is_inf_double(cpow(make_double(INFINITY, 0), make_double(2, 0))));
    _TEST_TRUE(is_inf_float(cpowf(make_float(1, -INFINITY), make_float(1, 0))));
    _TEST_TRUE(isnan(creal(cpow(make_double(NAN, 0), make_double(2, 0)))));
    _TEST_TRUE(isnan(creal(cpow(make_double(2, 0), make_double(NAN, 1)))));
}

int main(void)
{
    Test_ComplexCpowValues();
    Test_ComplexCpowSpecial();
    return _Test_Status();
}
