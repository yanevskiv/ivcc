// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> catanh.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// catanh should give the complex arc hyperbolic tangent within a few ulps in
// each type, odd and conjugate symmetric.
// [C99:7.3.6.3p2]: catanh, branch cuts outside [-1, +1] along the real axis
// [C99:7.3.6.3p3]: catanh, in [-ipi/2, +ipi/2] along the imaginary axis
// [C99:G.6.2.3p1]: catanh(conj(z)) as conj(catanh(z)), catanh odd
static void Test_ComplexCatanhValues(void)
{
    double complex d = catanh(make_double(0.5, 2));
    double complex e = catanh(make_double(-1.5, 0.25));
    double complex c = catanh(make_double(-0.5, 2));
    float complex f = catanhf(make_float(1, 2));
    long double complex l = catanhl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.8aeb1af986dcdp-4, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.206600be7bd52p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.80ba35240adc8p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.6388d87af0c11p+0, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.62e43p-3f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.2d97c8p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xb.17217f7d1cf79acp-6L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x9.6cbe3f9990e91a8p-3L, LDBL_MANT_DIG, ULPS));
}

// catanh should take each side of its cuts by the sign of the zero imaginary
// part, and 1 to an infinity with divide-by-zero.
// [C99:G.6p3]:     the functions continuous onto both sides of their branch cuts
// [C99:G.6.2.3p1]: catanh(+1 + i0) as +inf + i0, raising divide-by-zero
static void Test_ComplexCatanhCut(void)
{
    double complex d = catanh(make_double(2, 0));
    double complex e = catanh(make_double(2, -0.0));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.193ea7aad030bp-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.193ea7aad030bp-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), -0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));

    feclearexcept(FE_ALL_EXCEPT);
    d = catanh(make_double(1, 0));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    _TEST_TRUE(fetestexcept(FE_DIVBYZERO) != 0);
}

// catanh should give G.6.2.3's values of the zeros, infinities and NaNs,
// raising nothing, a sign it leaves unspecified unchecked.
// [C99:G.6.2.3p1]: catanh of the zeros, infinities and NaNs
static void Test_ComplexCatanhSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = catanh(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = catanh(make_double(0, NAN));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(isnan(IMAG(d, double)));
    d = catanh(make_double(2, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    d = catanh(make_double(INFINITY, 2));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    d = catanh(make_double(-INFINITY, -INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    d = catanh(make_double(INFINITY, NAN));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(isnan(IMAG(d, double)));
    d = catanh(make_double(NAN, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0);
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(is_nan_double(catanh(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);
    _TEST_TRUE(is_nan_float(catanhf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(catanhl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCatanhValues();
    Test_ComplexCatanhCut();
    Test_ComplexCatanhSpecial();
    return _Test_Status();
}
