// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> csin.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// csin should give the complex sine within a few ulps in each type, odd and
// conjugate symmetric.
// [C99:7.3.5.5p2]: csin, the complex sine
// [C99:G.6p7]:     csin(z) as -i csinh(iz)
static void Test_ComplexCsinValues(void)
{
    double complex d = csin(make_double(0.5, 2));
    double complex e = csin(make_double(-1.5, 0.25));
    double complex c = csin(make_double(-0.5, 2));
    float complex f = csinf(make_float(1, 2));
    long double complex l = csinl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.cdbecdf358453p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.9768441e05d6cp+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.07615d020c057p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.24c46391c9354p-6, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), -REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.95383ap+1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.f5a86ap+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xc.a9c1d7b292606d9p-2L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0xf.ad434f90e81e1b9p-3L, LDBL_MANT_DIG, ULPS));
}

// csin should give csinh's values of G.6.2.5 through G.6p7's formula, an
// infinite real part raising invalid where csinh's does, a sign it leaves
// unspecified unchecked.
// [C99:G.6.2.5p1]: csinh of the zeros, infinities and NaNs
static void Test_ComplexCsinSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = csin(make_double(0, 0));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = csin(make_double(-0.0, -0.0));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = csin(make_double(0, INFINITY));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = csin(make_double(0, NAN));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_TRUE(isnan(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(csin(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    d = csin(make_double(INFINITY, 0));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_double(csin(make_double(INFINITY, 2))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(csinf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(csinl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCsinValues();
    Test_ComplexCsinSpecial();
    return _Test_Status();
}
