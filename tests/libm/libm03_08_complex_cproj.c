// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cproj.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// cproj should give a value with no infinite part back unchanged, a NaN
// too, and every infinity, a NaN beside it or not, as +inf and a zero of
// the imaginary part's sign, raising nothing, in each type.
// [C99:G.3p1]:     an infinity, a value with an infinite part
// [C99:7.3.9.4p2]: cproj, every infinity to +inf + i0, the zero of the imaginary part's sign
// [C99:7.3.9.4p3]: cproj, the projection onto the Riemann sphere
// [C99:G.6p5]:     cimag, conj, cproj and creal, raising no exception
static void Test_ComplexCproj(void)
{
    double complex d[4];
    float complex f[2];
    long double complex l[2];

    feclearexcept(FE_ALL_EXCEPT);
    d[0] = cproj(make_double(-1.5, DBL_MAX));
    d[1] = cproj(make_double(INFINITY, NAN));
    d[2] = cproj(make_double(NAN, -INFINITY));
    d[3] = cproj(make_double(NAN, -0.0));
    f[0] = cprojf(make_float(-INFINITY, -3));
    f[1] = cprojf(make_float(-0.0f, 0));
    l[0] = cprojl(make_ldouble(5, INFINITY));
    l[1] = cprojl(make_ldouble(-INFINITY, -INFINITY));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT), 0);

    _TEST_FLOAT(REAL(d[0], double), -1.5);
    _TEST_FLOAT(IMAG(d[0], double), DBL_MAX);
    _TEST_FLOAT(REAL(d[1], double), INFINITY);
    _TEST_TRUE(IMAG(d[1], double) == 0 && ! signbit(IMAG(d[1], double)));
    _TEST_FLOAT(REAL(d[2], double), INFINITY);
    _TEST_TRUE(IMAG(d[2], double) == 0 && signbit(IMAG(d[2], double)));
    _TEST_TRUE(isnan(REAL(d[3], double)));
    _TEST_TRUE(IMAG(d[3], double) == 0 && signbit(IMAG(d[3], double)));
    _TEST_FLOAT(REAL(f[0], float), INFINITY);
    _TEST_TRUE(IMAG(f[0], float) == 0 && signbit(IMAG(f[0], float)));
    _TEST_TRUE(REAL(f[1], float) == 0 && signbit(REAL(f[1], float)));
    _TEST_TRUE(IMAG(f[1], float) == 0 && ! signbit(IMAG(f[1], float)));
    _TEST_FLOAT(REAL(l[0], long double), INFINITY);
    _TEST_TRUE(IMAG(l[0], long double) == 0 && ! signbit(IMAG(l[0], long double)));
    _TEST_FLOAT(REAL(l[1], long double), INFINITY);
    _TEST_TRUE(IMAG(l[1], long double) == 0 && signbit(IMAG(l[1], long double)));
}

int main(void)
{
    Test_ComplexCproj();
    return _Test_Status();
}
