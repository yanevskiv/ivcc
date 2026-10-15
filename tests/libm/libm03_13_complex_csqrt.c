// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> csqrt.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// csqrt should give the square root in the right half-plane within a few
// ulps in each type, exactly where it is exact, the sign of a zero
// imaginary part choosing the side of the cut along the negative real axis,
// and a part far smaller than the other kept to its own precision.
// [C99:7.3.3p1]:   a branch cut's sides, by the sign of zero
// [C99:7.3.8.3p2]: csqrt, a branch cut along the negative real axis
// [C99:7.3.8.3p3]: csqrt, in the right half-plane
// [C99:G.6p3]:     csqrt(-2 +- i0) as +-i sqrt(2)
// [C99:G.6.4.2p1]: csqrt(conj(z)) as conj(csqrt(z))
static void Test_ComplexCsqrtValues(void)
{
    double complex d = csqrt(make_double(0, 1));
    double complex e = csqrt(make_double(-1, 1e-10));
    float complex f = csqrtf(make_float(0, 1));
    long double complex l = csqrtl(make_ldouble(0, 1));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.6a09e667f3bcdp-1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), REAL(d, double));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.b7cdfd9d7bdbbp-35, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(e, double), 1);
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.6a09e6p-1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xb.504f333f9de6484p-4L, LDBL_MANT_DIG, ULPS));

    d = csqrt(make_double(3, 4));
    _TEST_FLOAT(REAL(d, double), 2);
    _TEST_FLOAT(IMAG(d, double), 1);
    d = csqrt(make_double(-3, -4));
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_FLOAT(IMAG(d, double), -2);
    f = csqrtf(make_float(-4, 0));
    _TEST_TRUE(REAL(f, float) == 0 && ! signbit(REAL(f, float)));
    _TEST_FLOAT(IMAG(f, float), 2);
    l = csqrtl(make_ldouble(-2, -0.0L));
    _TEST_TRUE(REAL(l, long double) == 0 && ! signbit(REAL(l, long double)));
    _TEST_TRUE(within_ulps(IMAG(l, long double), -sqrtl(2), LDBL_MANT_DIG, ULPS));
    d = csqrt(make_double(9, -0.0));
    _TEST_FLOAT(REAL(d, double), 3);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));

    l = csqrtl(make_ldouble(LDBL_MAX, LDBL_MAX));
    _TEST_TRUE(isfinite(REAL(l, long double)) && isfinite(IMAG(l, long double)));
    _TEST_TRUE(within_ulps(REAL(l, long double) / IMAG(l, long double), 1 + sqrtl(2), LDBL_MANT_DIG, ULPS));
    feclearexcept(FE_ALL_EXCEPT);
    l = csqrtl(make_ldouble(1, 0x1p-16000L));
    _TEST_FLOAT(REAL(l, long double), 1);
    _TEST_FLOAT(IMAG(l, long double), 0x1p-16001L);
    _TEST_INT(fetestexcept(FE_UNDERFLOW), 0);
}

// csqrt should give G.6.4.2's values of the zeros, infinities and NaNs,
// raising nothing, a sign it leaves unspecified unchecked.
// [C99:G.6.4.2p1]: csqrt of the zeros, infinities and NaNs
static void Test_ComplexCsqrtSpecial(void)
{
    double complex d;

    feclearexcept(FE_ALL_EXCEPT);
    d = csqrt(make_double(-0.0, 0));
    _TEST_TRUE(is_zero_double(d) && ! signbit(REAL(d, double)) && ! signbit(IMAG(d, double)));
    d = csqrt(make_double(0, -0.0));
    _TEST_TRUE(is_zero_double(d) && ! signbit(REAL(d, double)) && signbit(IMAG(d, double)));
    d = csqrt(make_double(NAN, INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = csqrt(make_double(-5, -INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), -INFINITY);
    d = csqrt(make_double(-INFINITY, 2));
    _TEST_TRUE(REAL(d, double) == 0 && ! signbit(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), INFINITY);
    d = csqrt(make_double(INFINITY, -2));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    d = csqrt(make_double(-INFINITY, NAN));
    _TEST_TRUE(isnan(REAL(d, double)) && isinf(IMAG(d, double)));
    d = csqrt(make_double(INFINITY, NAN));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(isnan(IMAG(d, double)));
    _TEST_TRUE(is_nan_double(csqrt(make_double(NAN, NAN))));
    _TEST_TRUE(is_nan_float(csqrtf(make_float(NAN, 1))));
    _TEST_TRUE(is_nan_ldouble(csqrtl(make_ldouble(1, NAN))));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT & ~FE_INVALID), 0);
}

int main(void)
{
    Test_ComplexCsqrtValues();
    Test_ComplexCsqrtSpecial();
    return _Test_Status();
}
