// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> casinh.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// casinh should give the complex arc hyperbolic sine within a few ulps in
// each type, odd and conjugate symmetric.
// [C99:7.3.6.2p2]: casinh, branch cuts outside [-i, +i] along the imaginary axis
// [C99:7.3.6.2p3]: casinh, in [-ipi/2, +ipi/2] along the imaginary axis
// [C99:G.6.2.2p1]: casinh(conj(z)) as conj(casinh(z)), casinh odd
static void Test_ComplexCasinhValues(void)
{
    double complex d = casinh(make_double(0.5, 2));
    double complex e = casinh(make_double(-1.5, 0.25));
    double complex c = casinh(make_double(-0.5, 2));
    float complex f = casinhf(make_float(1, 2));
    long double complex l = casinhl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.5c9efbdcd9088p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.4b04ce1c05557p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.33e721e9b867p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.1b0611e3dc247p-3, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.78277p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.103d9ap+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xb.c13b7cc30e25beep-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x8.81ecd7d430f9d2p-3L, LDBL_MANT_DIG, ULPS));
}

// casinh should take each side of its cuts by the sign of the zero real
// part.
// [C99:G.6p3]: the functions continuous onto both sides of their branch cuts
static void Test_ComplexCasinhCut(void)
{
    double complex d = casinh(make_double(0, 2));
    double complex e = casinh(make_double(-0.0, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
}

// casinh should give G.6.2.2's values of the zeros, infinities and NaNs,
// raising nothing, a sign it leaves unspecified unchecked.
// [C99:G.6.2.2p1]: casinh of the zeros, infinities and NaNs
static void Test_ComplexCasinhSpecial(void)
{
    double complex d;
    long double complex l;

    feclearexcept(FE_ALL_EXCEPT);
    d = casinh(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = casinh(make_double(-0.0, -0.0));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = casinh(make_double(2, INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    d = casinh(make_double(INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    l = casinhl(make_ldouble(INFINITY, INFINITY));
    _TEST_FLOAT(REAL(l, long double), INFINITY);
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0xc.90fdaa22168c235p-4L, LDBL_MANT_DIG, ULPS));
    d = casinh(make_double(INFINITY, NAN));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(isnan(IMAG(d, double)));
    d = casinh(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = casinh(make_double(NAN, INFINITY));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(casinh(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);
    _TEST_TRUE(is_nan_float(casinhf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(casinhl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCasinhValues();
    Test_ComplexCasinhCut();
    Test_ComplexCasinhSpecial();
    return _Test_Status();
}
