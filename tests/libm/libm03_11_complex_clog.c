// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> clog.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// Defines.
#define ULPS 4

// clog should give ln |z| and the argument of z within a few ulps in each
// type, the argument in [-pi, +pi], the sign of a zero imaginary part
// choosing the side of the cut along the negative real axis, and ln |z|
// near the unit circle to its own precision.
// [C99:7.3.3p1]:   a branch cut's sides, by the sign of zero
// [C99:7.3.7.2p2]: clog, a branch cut along the negative real axis
// [C99:7.3.7.2p3]: clog, in [-ipi, +ipi] along the imaginary axis
// [C99:G.6.3.2p1]: clog(conj(z)) as conj(clog(z))
static void Test_ComplexClogValues(void)
{
    double pi = atan2(0, -1);
    double complex d = clog(make_double(3, -4));
    double complex e = clog(make_double(-2, 0.5));
    double complex c = clog(make_double(-2, -0.5));
    float complex f = clogf(make_float(3, -4));
    long double complex l = clogl(make_ldouble(3, -4));

    _TEST_TRUE(within_ulps(REAL(d, double), 0x1.9c041f7ed8d33p+0, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), -0x1.dac670561bb4fp-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(e, double), 0x1.7269484fac504p-1, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(e, double), 0x1.72c43f4b1650ap+1, DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(REAL(c, double), REAL(e, double));
    _TEST_FLOAT(IMAG(c, double), -IMAG(e, double));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1.9c042p+0f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(f, float), -0x1.dac67p-1f, FLT_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0xc.e020fbf6c699b58p-3L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), -0xe.d63382b0dda7b45p-4L, LDBL_MANT_DIG, ULPS));

    d = clog(make_double(-2, 0));
    _TEST_TRUE(within_ulps(REAL(d, double), log(2), DBL_MANT_DIG, ULPS));
    _TEST_FLOAT(IMAG(d, double), pi);
    d = clog(make_double(-2, -0.0));
    _TEST_FLOAT(IMAG(d, double), -pi);
    d = clog(make_double(1, 0));
    _TEST_TRUE(is_zero_double(d) && ! signbit(REAL(d, double)) && ! signbit(IMAG(d, double)));

    d = clog(make_double(1, 0x1p-30));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1p-61, DBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(d, double), 0x1p-30, DBL_MANT_DIG, ULPS));
    d = clog(make_double(0x1.fffffffffffffp-1, 0x1p-26));
    _TEST_TRUE(within_ulps(REAL(d, double), 0x1p-107, DBL_MANT_DIG, ULPS));
    f = clogf(make_float(1, 0x1p-30f));
    _TEST_TRUE(within_ulps(REAL(f, float), 0x1p-61f, FLT_MANT_DIG, ULPS));
    l = clogl(make_ldouble(0x1.fffffffffffffp-1, 0x1p-26));
    _TEST_TRUE(within_ulps(REAL(l, long double), 0x8p-110L, LDBL_MANT_DIG, ULPS));
    _TEST_TRUE(within_ulps(IMAG(l, long double), 0x8.000000000000155p-29L, LDBL_MANT_DIG, ULPS));
}

// clog should give G.6.3.2's values of the zeros, infinities and NaNs,
// raising divide-by-zero where it says, and an invalid it makes optional
// untested.
// [C99:G.6.3.2p1]: clog of the zeros, infinities and NaNs
static void Test_ComplexClogSpecial(void)
{
    double pi = atan2(0, -1);
    double complex d;
    float complex f;
    long double complex l;

    feclearexcept(FE_ALL_EXCEPT);
    d = clog(make_double(-0.0, 0));
    _TEST_FLOAT(REAL(d, double), -INFINITY);
    _TEST_FLOAT(IMAG(d, double), pi);
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_DIVBYZERO);
    feclearexcept(FE_ALL_EXCEPT);
    d = clog(make_double(0, -0.0));
    _TEST_FLOAT(REAL(d, double), -INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && signbit(IMAG(d, double)));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_DIVBYZERO);
    feclearexcept(FE_ALL_EXCEPT);
    f = clogf(make_float(0, 0));
    _TEST_FLOAT(REAL(f, float), -INFINITY);
    _TEST_TRUE(IMAG(f, float) == 0 && ! signbit(IMAG(f, float)));
    _TEST_INT(fetestexcept(FE_DIVBYZERO), FE_DIVBYZERO);

    feclearexcept(FE_ALL_EXCEPT);
    d = clog(make_double(-3, INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), pi / 2);
    d = clog(make_double(-INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), pi);
    d = clog(make_double(INFINITY, 2));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(IMAG(d, double) == 0 && ! signbit(IMAG(d, double)));
    d = clog(make_double(-INFINITY, INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), atan2(1, -1));
    d = clog(make_double(INFINITY, -INFINITY));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_FLOAT(IMAG(d, double), atan2(-1, 1));
    d = clog(make_double(-INFINITY, NAN));
    _TEST_FLOAT(REAL(d, double), INFINITY);
    _TEST_TRUE(isnan(IMAG(d, double)));
    l = clogl(make_ldouble(NAN, -INFINITY));
    _TEST_FLOAT(REAL(l, long double), INFINITY);
    _TEST_TRUE(isnan(IMAG(l, long double)));
    _TEST_TRUE(is_nan_double(clog(make_double(NAN, NAN))));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), 0);

    _TEST_TRUE(is_nan_double(clog(make_double(1, NAN))));
    _TEST_TRUE(is_nan_ldouble(clogl(make_ldouble(NAN, 0))));
}

int main(void)
{
    Test_ComplexClogValues();
    Test_ComplexClogSpecial();
    return _Test_Status();
}
