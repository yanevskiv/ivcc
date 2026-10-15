// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> ctanh.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// ctanh should give the complex hyperbolic tangent within a few ulps in each
// type, odd and conjugate symmetric.
// [C99:7.3.6.6p2]: ctanh, the complex hyperbolic tangent
// [C99:G.6.2.6p1]: ctanh(conj(z)) as conj(ctanh(z)), ctanh odd
static void Test_ComplexCtanhValues(void)
{
    double complex d = ctanh(make_double(0.5, 2));
    double complex e = ctanh(make_double(-1.5, 0.25));
    double complex c = ctanh(make_double(-0.5, 2));
    float complex f = ctanhf(make_float(1, 2));
    long double complex l = ctanhl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.523fd669f0da7p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.b3a64c0e661c2p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.d49e852ccf33ep-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.66d3d2ac63eeep-5, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.2aaf3ap+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), -0x1.f29a36p-3f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x9.5579d19f41eef9p-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), -0xf.94d1b502488dfb6p-6L, LDBL_MANT_DIG, ULPS));
}

// ctanh should keep its value where the real part is large, the tiny
// imaginary part with it.
// [C99:7.3.6.6p3]: ctanh, the complex hyperbolic tangent value
static void Test_ComplexCtanhLarge(void)
{
    double complex d = ctanh(make_double(20, 1));

    _TEST_TRUE(within_ulps(REAL(d, double), 1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.1d0a56d651beap-57, DBL_MANT_DIG, ULPS));
}

// ctanh should give G.6.2.6's values of the zeros, infinities and NaNs, an
// infinite imaginary part raising invalid, a sign it leaves unspecified
// unchecked.
// [C99:G.6.2.6p1]: ctanh of the zeros, infinities and NaNs
static void Test_ComplexCtanhSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = ctanh(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = ctanh(make_double(INFINITY, 1));
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = ctanh(make_double(-INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), -1);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = ctanh(make_double(INFINITY, INFINITY));
    _TEST_TRUE(REAL(d, double) == 1 && IMAG(d, double) == 0);
    d = ctanh(make_double(INFINITY, NAN));
    _TEST_TRUE(REAL(d, double) == 1 && IMAG(d, double) == 0);
    d = ctanh(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(ctanh(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    _TEST_TRUE(is_nan_double(ctanh(make_double(2, INFINITY))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(ctanhf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(ctanhl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCtanhValues();
    Test_ComplexCtanhLarge();
    Test_ComplexCtanhSpecial();
    return _Test_Status();
}
