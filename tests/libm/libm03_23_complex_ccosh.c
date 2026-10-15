// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> ccosh.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// ccosh should give the complex hyperbolic cosine within a few ulps in each
// type, even and conjugate symmetric.
// [C99:7.3.6.4p2]: ccosh, the complex hyperbolic cosine
// [C99:G.6.2.4p1]: ccosh(conj(z)) as conj(ccosh(z)), ccosh even
static void Test_ComplexCcoshValues(void)
{
    double complex d = ccosh(make_double(0.5, 2));
    double complex e = ccosh(make_double(-1.5, 0.25));
    double complex c = ccosh(make_double(-0.5, 2));
    float complex f = ccoshf(make_float(1, 2));
    long double complex l = ccoshl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), -0x1.e08529d786015p-2, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.e533daaa209f6p-2, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.23bf6930e258ap+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), -0x1.0db7b3f6d4979p-1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), -0x1.48c7a4p-1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.119042p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), -0xa.463d1cad744681ap-4L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x8.8c820c38d0bd909p-3L, LDBL_MANT_DIG, ULPS));
}

// ccosh should keep a part that fits where e^x alone would overflow.
// [C99:7.3.6.4p3]: ccosh, the complex hyperbolic cosine value
static void Test_ComplexCcoshLarge(void)
{
    double complex d = ccosh(make_double(711, 1.2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.395b3e684442ap+1023, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
}

// ccosh should give G.6.2.4's values of the zeros, infinities and NaNs, an
// infinite imaginary part raising invalid, a sign it leaves unspecified
// unchecked.
// [C99:G.6.2.4p1]: ccosh of the zeros, infinities and NaNs
static void Test_ComplexCcoshSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = ccosh(make_double(0, 0));
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = ccosh(make_double(0, NAN));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    d = ccosh(make_double(INFINITY, 0));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = ccosh(make_double(INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), -INFINITY);
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = ccosh(make_double(INFINITY, NAN));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(isnan(IMAG(d, double)));
    d = ccosh(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    _TEST_TRUE(is_nan_double(ccosh(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    d = ccosh(make_double(0, INFINITY));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_double(ccosh(make_double(2, INFINITY))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    d = ccosh(make_double(INFINITY, INFINITY));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(ccoshf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(ccoshl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCcoshValues();
    Test_ComplexCcoshLarge();
    Test_ComplexCcoshSpecial();
    return _Test_Status();
}
