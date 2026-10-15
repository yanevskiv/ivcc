// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> catan.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// catan should give the complex arc tangent within a few ulps in each type,
// its real part in [-pi/2, +pi/2], odd and conjugate symmetric.
// [C99:7.3.5.3p2]: catan, branch cuts outside [-i, +i] along the imaginary axis
// [C99:7.3.5.3p3]: catan, in [-pi/2, +pi/2] along the real axis
// [C99:G.6p7]:     catan(z) as -i catanh(iz)
static void Test_ComplexCatanValues(void)
{
    double complex d = catan(make_double(0.5, 2));
    double complex e = catan(make_double(-1.5, 0.25));
    double complex c = catan(make_double(-0.5, 2));
    float complex f = catanf(make_float(1, 2));
    long double complex l = catanl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.6bea7ebdbbf5cp+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.00307f2440124p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.fbb3705373617p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.37832fc0873acp-4, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.56c6e8p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.9c042p-2f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xa.b63739cbfad72ccp-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0xc.e020fbf6c699b58p-5L, LDBL_MANT_DIG, ULPS));
}

// catan should take each side of its cuts by the sign of the zero real part,
// and i to an infinity with divide-by-zero.
// [C99:G.6p3]:     the functions continuous onto both sides of their branch cuts
// [C99:G.6.2.3p1]: catanh(+1 + i0) as +inf + i0, raising divide-by-zero
static void Test_ComplexCatanCut(void)
{
    double complex d = catan(make_double(0, 2));
    double complex e = catan(make_double(-0.0, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.193ea7aad030bp-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.193ea7aad030bp-1, DBL_MANT_DIG, ULPS));

    feclearexcept(FE_ALL_EXCEPT);
    d = catan(make_double(0, 1));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    _TEST_TRUE(fetestexcept(FE_DIVBYZERO) != 0);
}

// catan should give catanh's values of G.6.2.3 through G.6p7's formula,
// raising nothing.
// [C99:G.6.2.3p1]: catanh of the zeros, infinities and NaNs
static void Test_ComplexCatanSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = catan(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = catan(make_double(2, INFINITY));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = catan(make_double(INFINITY, 2));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = catan(make_double(-INFINITY, -INFINITY));
    _TEST_TRUE(within_ulps(REAL(d, double), -0x1.921fb54442d18p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = catan(make_double(NAN, INFINITY));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    d = catan(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(catan(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);
    _TEST_TRUE(is_nan_float(catanf(make_float(NAN, 2))));
    _TEST_TRUE(is_nan_ldouble(catanl(make_ldouble(2, NAN))));
}

int main(void)
{
    Test_ComplexCatanValues();
    Test_ComplexCatanCut();
    Test_ComplexCatanSpecial();
    return _Test_Status();
}
