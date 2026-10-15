// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cacos.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// cacos should give the complex arc cosine within a few ulps in each type,
// its real part in [0, pi], and cacos(conj(z)) as conj(cacos(z)).
// [C99:7.3.5.1p2]: cacos, branch cuts outside [-1, +1] along the real axis
// [C99:7.3.5.1p3]: cacos, in [0, pi] along the real axis
// [C99:G.6.1.1p1]: cacos(conj(z)) as conj(cacos(z))
static void Test_ComplexCacosValues(void)
{
    double complex d = cacos(make_double(0.5, 2));
    double complex e = cacos(make_double(-1.5, 0.25));
    double complex c = cacos(make_double(0.5, -2));
    float complex f = cacosf(make_float(1, 2));
    long double complex l = cacosl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.598b07e074455p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.77391f0ddbd69p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.767439ddf0d9fp+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), -0x1.fcca3d59566c8p-1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.24cabp+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), -0x1.87506cp+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x9.26557c97113b4e8p-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), -0xc.3a8363e64cdfe1dp-3L, LDBL_MANT_DIG, ULPS));
}

// cacos should take each side of its cuts by the sign of the zero imaginary
// part, and 1 to 0 exactly.
// [C99:G.6p3]: the functions continuous onto both sides of their branch cuts
static void Test_ComplexCacosCut(void)
{
    double complex d = cacos(make_double(2, 0));
    double complex e = cacos(make_double(2, -0.0));
    double complex g = cacos(make_double(-2, 0));

    _TEST_FLOAT(REAL(d, double), 0);
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(g, double), 0x1.921fb54442d18p+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(g, double), -0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));

    d = cacos(make_double(1, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
}

// cacos should give G.6.1.1's values of the zeros, infinities and NaNs,
// raising nothing, a sign it leaves unspecified unchecked.
// [C99:G.6.1.1p1]: cacos of the zeros, infinities and NaNs
static void Test_ComplexCacosSpecial(void)
{
    double complex d;
    long double complex l;

    feclearexcept(FE_ALL_EXCEPT);
    d = cacos(make_double(-0.0, 0));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = cacos(make_double(0, NAN));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(isnan(IMAG(d, double)));
    d = cacos(make_double(5, INFINITY));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    d = cacos(make_double(-INFINITY, 2));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    d = cacos(make_double(INFINITY, 2));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    d = cacos(make_double(-INFINITY, INFINITY));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.2d97c7f3321d2p+1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    l = cacosl(make_ldouble(INFINITY, INFINITY));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xc.90fdaa22168c235p-4L, LDBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(l, long double), -INFINITY);
    d = cacos(make_double(INFINITY, NAN));
    _TEST_TRUE(isnan(REAL(d, double)) && isinf(IMAG(d, double)));
    d = cacos(make_double(NAN, INFINITY));
    _TEST_TRUE(isnan(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    _TEST_TRUE(is_nan_double(cacos(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);
    _TEST_TRUE(is_nan_float(cacosf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(cacosl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCacosValues();
    Test_ComplexCacosCut();
    Test_ComplexCacosSpecial();
    return _Test_Status();
}
