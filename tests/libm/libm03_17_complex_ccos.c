// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> ccos.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// ccos should give the complex cosine within a few ulps in each type, even
// and conjugate symmetric.
// [C99:7.3.5.4p2]: ccos, the complex cosine
// [C99:G.6p7]:     ccos(z) as ccosh(iz)
static void Test_ComplexCcosValues(void)
{
    double complex d = ccos(make_double(0.5, 2));
    double complex e = ccos(make_double(-1.5, 0.25));
    double complex c = ccos(make_double(-0.5, 2));
    float complex f = ccosf(make_float(1, 2));
    long double complex l = ccosl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.a69c0d580f319p+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.bd229ea3b0ef8p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.2ad758a49ae2ep-4, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.0206eb4f45109p-2, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.043044p+1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), -0x1.86a496p+1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x8.218223d3e7abf37p-2L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), -0xc.3524b2585d8ce54p-2L, LDBL_MANT_DIG, ULPS));
}

// ccos should give ccosh's values of G.6.2.4 through G.6p7's formula, an
// infinite imaginary part raising invalid where ccosh's does, a sign it
// leaves unspecified unchecked.
// [C99:G.6.2.4p1]: ccosh of the zeros, infinities and NaNs
static void Test_ComplexCcosSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = ccos(make_double(0, 0));
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = ccos(make_double(0, INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = ccos(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    _TEST_TRUE(is_nan_double(ccos(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID | FE_DIVBYZERO), 0);

    d = ccos(make_double(INFINITY, 0));
    _TEST_TRUE(isnan(REAL(d, double)) && IMAG(d, double) == 0);
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_double(ccos(make_double(INFINITY, 2))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_float(ccosf(make_float(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(ccosl(make_ldouble(NAN, 2))));
}

int main(void)
{
    Test_ComplexCcosValues();
    Test_ComplexCcosSpecial();
    return _Test_Status();
}
