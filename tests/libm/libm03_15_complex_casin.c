// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> casin.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// casin should give the complex arc sine within a few ulps in each type,
// its real part in [-pi/2, +pi/2], odd and conjugate symmetric.
// [C99:7.3.5.2p2]: casin, branch cuts outside [-1, +1] along the real axis
// [C99:7.3.5.2p3]: casin, in [-pi/2, +pi/2] along the real axis
// [C99:G.6p7]:     casin(z) as -i casinh(iz)
static void Test_ComplexCasinValues(void)
{
    double complex d = casin(make_double(0.5, 2));
    double complex e = casin(make_double(-1.5, 0.25));
    double complex c = casin(make_double(-0.5, -2));
    float complex f = casinf(make_float(1, 2));
    long double complex l = casinl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.c4a56b1e74619p-3, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.77391f0ddbd69p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.5ac8be779ee27p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.fcca3d59566c8p-1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.b55416p-2f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.87506cp+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xd.aaa0b62c1543531p-5L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0xc.3a8363e64cdfe1dp-3L, LDBL_MANT_DIG, ULPS));
}

// casin should take each side of its cuts by the sign of the zero imaginary
// part.
// [C99:G.6p3]: the functions continuous onto both sides of their branch cuts
static void Test_ComplexCasinCut(void)
{
    double complex d = casin(make_double(2, 0));
    double complex e = casin(make_double(2, -0.0));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), -0x1.5124271980435p+0, DBL_MANT_DIG, ULPS));
}

// casin should give casinh's values of G.6.2.2 through G.6p7's formula,
// raising nothing.
// [C99:G.6.2.2p1]: casinh of the zeros, infinities and NaNs
static void Test_ComplexCasinSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = casin(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = casin(make_double(-0.0, -0.0));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = casin(make_double(2, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = casin(make_double(INFINITY, 2));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = casin(make_double(NAN, INFINITY));
    _TEST_TRUE(isnan(REAL(d, double)) && isinf(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(casin(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);
    _TEST_TRUE(is_nan_float(casinf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(casinl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCasinValues();
    Test_ComplexCasinCut();
    Test_ComplexCasinSpecial();
    return _Test_Status();
}
