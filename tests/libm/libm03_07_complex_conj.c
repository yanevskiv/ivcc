// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> conj.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// conj should reverse the sign of the imaginary part alone, a zero's, an
// infinity's and a NaN's too, raising nothing, in each type.
// [C99:7.3.9.3p2]: conj, the imaginary part's sign reversed
// [C99:7.3.9.3p3]: conj, the complex conjugate
// [C99:G.6p5]:     cimag, conj, cproj and creal, raising no exception
static void Test_ComplexConj(void)
{
    double complex d;
    float complex f;
    long double complex l;

    feclearexcept(FE_ALL_EXCEPT);
    d = conj(make_double(1, 2));
    f = conjf(make_float(-3, -0.0f));
    l = conjl(make_ldouble(NAN, INFINITY));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT), 0);
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_FLOAT(IMAG(d, double), -2);
    _TEST_FLOAT(REAL(f, float), -3);
    _TEST_TRUE(IMAG(f, float) == 0 && ! signbit(IMAG(f, float)));
    _TEST_TRUE(isnan(REAL(l, long double)) && ! signbit(REAL(l, long double)));
    _TEST_FLOAT(IMAG(l, long double), -INFINITY);
    d = conj(make_double(-NAN, NAN));
    _TEST_TRUE(signbit(REAL(d, double)) && isnan(IMAG(d, double)) && signbit(IMAG(d, double)));
    _TEST_TRUE(conj(conj(make_double(5, -6))) == make_double(5, -6));
}

int main(void)
{
    Test_ComplexConj();
    return _Test_Status();
}
