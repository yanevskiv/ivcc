// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cexp.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// cexp should give e to x times the cosine and the sine of y within a few
// ulps in each type, a real x's e to x with its zero imaginary part kept,
// and 1 + i0 of a zero, exactly and raising nothing but perhaps inexact.
// [C99:7.3.7.1p2]: cexp, the complex base-e exponential
// [C99:G.6.3.1p1]: cexp(conj(z)) as conj(cexp(z)), cexp(+-0 + i0) as 1 + i0
// [C99:F.9p8]:     inexact, unspecified
static void Test_ComplexCexpValues(void)
{
    double complex d = cexp(make_double(1, 2));
    double complex e = cexp(make_double(-0.5, -10));
    double complex c = cexp(make_double(1, -2));
    float complex f = cexpf(make_float(1, 2));
    long double complex l = cexpl(make_ldouble(1, 2));

    _TEST_TRUE(within_ulps(REAL(d, double), -0x1.21969c4953cd1p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1.3c618a2274afdp+1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), -0x1.0491810bc51f6p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.51e278be13c98p-2, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(d, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(d, double));
    _TEST_TRUE(within_ulps(REAL(f, float), -0x1.21969cp+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), 0x1.3c618ap+1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), -0x9.0cb4e24a9e68baep-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x9.e30c5113a57ead7p-2L, LDBL_MANT_DIG, ULPS));

    d = cexp(make_double(2, -0.0));
    _TEST_TRUE(within_ulps(REAL(d, double), exp(2), DBL_MANT_DIG, ULPS));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));

    feclearexcept(FE_ALL_EXCEPT);
    d = cexp(make_double(0, 0));
    f = cexpf(make_float(-0.0f, -0.0f));
    l = cexpl(make_ldouble(-0.0L, 0));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), 0);
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    _TEST_FLOAT(REAL(f, float), 1);
    _TEST_TRUE(IMAG(f, float) == 0 && signbit(IMAG(f, float)));
    _TEST_FLOAT(REAL(l, long double), 1);
    _TEST_TRUE(IMAG(l, long double) == 0 && ! signbit(IMAG(l, long double)));
}

// A part past the type's range should overflow alone, though e to x does,
// and a tiny result should underflow.
// [C99:G.6p4]:    the complex functions' exceptions, as F.9's
// [C99:F.9p6]:    overflow, an infinity returned for a value too large
// [C99:F.9p7]:    underflow, a tiny result that loses accuracy
static void Test_ComplexCexpRange(void)
{
    double complex d;
    float complex f;
    long double complex l;

    feclearexcept(FE_ALL_EXCEPT);
    d = cexp(make_double(710, 1.2));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.cd1c0ad37f5bcp+1022, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    _TEST_TRUE(fetestexcept(FE_OVERFLOW) != 0);
    f = cexpf(make_float(89, 1.2f));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.e98fa4p+126f, FLT_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(f, float), INFINITY);
    l = cexpl(make_ldouble(11357, 1.2L));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x9.567300b5e095f28p+16380L, LDBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(l, long double), INFINITY);

    feclearexcept(FE_ALL_EXCEPT);
    d = cexp(make_double(-740, 1));
    _TEST_TRUE(REAL(d, double) > 0 && REAL(d, double) < DBL_MIN);
    _TEST_TRUE(IMAG(d, double) > 0 && IMAG(d, double) < DBL_MIN);
    _TEST_TRUE(fetestexcept(FE_UNDERFLOW) != 0);
}

// cexp should give G.6.3.1's values of the infinities and NaNs, raising
// invalid where it says, a sign it leaves unspecified unchecked, and an
// invalid it makes optional untested.
// [C99:G.6.3.1p1]: cexp of the infinities and NaNs
static void Test_ComplexCexpSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_double(cexp(make_double(1, INFINITY))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(is_nan_float(cexpf(make_float(-0.0f, -INFINITY))));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    _TEST_TRUE(is_nan_double(cexp(make_double(2, NAN))));
    _TEST_TRUE(is_nan_ldouble(cexpl(make_ldouble(0, NAN))));

    feclearexcept(FE_ALL_EXCEPT);
    d = cexp(make_double(INFINITY, 0));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = cexp(make_double(INFINITY, -0.0));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = cexp(make_double(-INFINITY, 2));
    _TEST_TRUE(REAL(d, double) == 0 && signbit(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = cexp(make_double(INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), -INFINITY);
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = cexp(make_double(INFINITY, -1));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    _TEST_TRUE(is_zero_double(cexp(make_double(-INFINITY, INFINITY))));
    _TEST_TRUE(is_zero_ldouble(cexpl(make_ldouble(-INFINITY, NAN))));
    d = cexp(make_double(NAN, 0));
    _TEST_TRUE(isnan(REAL(d, double)));
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = cexp(make_double(NAN, -0.0));
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(cexp(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_INVALID), 0);

    d = cexp(make_double(INFINITY, INFINITY));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    _TEST_TRUE(fetestexcept(FE_INVALID) != 0);
    d = cexp(make_double(INFINITY, NAN));
    _TEST_TRUE(isinf(REAL(d, double)) && isnan(IMAG(d, double)));
    _TEST_TRUE(is_nan_float(cexpf(make_float(NAN, 1))));
}

int main(void)
{
    Test_ComplexCexpValues();
    Test_ComplexCexpRange();
    Test_ComplexCexpSpecial();
    return _Test_Status();
}
