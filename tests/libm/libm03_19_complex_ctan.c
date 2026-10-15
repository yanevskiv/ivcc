// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> ctan.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// ctan should give the complex tangent within a few ulps in each type, odd
// and conjugate symmetric.
// [C99:7.3.5.6p2]: ctan, the complex tangent
// [C99:G.6p7]:     ctan(z) as -i ctanh(iz)
static void Test_ComplexCtanValues(void)
{
    double complex d = ctan(make_double(0.5, 2));
    double complex e = ctan(make_double(-1.5, 0.25));
    double complex c = ctan(make_double(-0.5, 2));
    float complex f = ctanf(make_float(1, 2));
    long double complex l = ctanl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.ef0f09578f1c5p-6, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.f5bace9d33415p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.067c297685313p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.e49f37b75b3c8p+1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.14fea2p-5f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.03c984p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x8.a7f51632d061f95p-8L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x8.1e4c1d8c50a08b9p-3L, LDBL_MANT_DIG, ULPS));
}

// ctan should keep its value where the imaginary part is large, the tiny
// real part with it.
// [C99:7.3.5.6p3]: ctan, the complex tangent value
static void Test_ComplexCtanLarge(void)
{
    double complex d = ctan(make_double(1, 20));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.1d0a56d651beap-57, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 1, DBL_MANT_DIG, ULPS));
}

// ctan should give ctanh's values of G.6.2.6 through G.6p7's formula, an
// infinite real part raising invalid where ctanh's does, a sign it leaves
// unspecified unchecked.
// [C99:G.6.2.6p1]: ctanh of the zeros, infinities and NaNs
static void Test_ComplexCtanSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = ctan(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = ctan(make_double(1, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), 1);
    d = ctan(make_double(2, -INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), -1);
    d = ctan(make_double(0, NAN));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(isnan(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(ctan(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    _TEST_TRUE(is_nan_double(ctan(make_double(INFINITY, 2))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(ctanf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(ctanl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCtanValues();
    Test_ComplexCtanLarge();
    Test_ComplexCtanSpecial();
    return _Test_Status();
}
