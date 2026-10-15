// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> csinh.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// csinh should give the complex hyperbolic sine within a few ulps in each
// type, odd and conjugate symmetric.
// [C99:7.3.6.5p2]: csinh, the complex hyperbolic sine
// [C99:G.6.2.5p1]: csinh(conj(z)) as conj(csinh(z)), csinh odd
static void Test_ComplexCsinhValues(void)
{
    double complex d = csinh(make_double(0.5, 2));
    double complex e = csinh(make_double(-1.5, 0.25));
    double complex c = csinh(make_double(-0.5, 2));
    float complex f = csinhf(make_float(1, 2));
    long double complex l = csinhl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), -0x1.bc1cfc9e7e455p-3, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.067d2a9d01d9ep+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.08132df6d0aa6p+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.29fb4ed6ac01ap-1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), -0x1.f4cb2ap-2f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.6732d2p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), -0xf.a6594fcf9115e85p-5L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0xb.399695ee7a3fca4p-3L, LDBL_MANT_DIG, ULPS));
}

// csinh should give G.6.2.5's values of the zeros, infinities and NaNs, an
// infinite imaginary part raising invalid, a sign it leaves unspecified
// unchecked.
// [C99:G.6.2.5p1]: csinh of the zeros, infinities and NaNs
static void Test_ComplexCsinhSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = csinh(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = csinh(make_double(-0.0, -0.0));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = csinh(make_double(0, NAN));
    _TEST_TRUE(REAL(d, double) == 0 && isnan(IMAG(d, double)));
    d = csinh(make_double(INFINITY, 0));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = csinh(make_double(INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), -INFINITY);
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = csinh(make_double(INFINITY, NAN));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    d = csinh(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(csinh(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    d = csinh(make_double(0, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && isnan(IMAG(d, double)));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_double(csinh(make_double(2, INFINITY))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    d = csinh(make_double(INFINITY, INFINITY));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(csinhf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(csinhl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCsinhValues();
    Test_ComplexCsinhSpecial();
    return _Test_Status();
}
