// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> creal.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// creal should give the real part, the first element, its sign, infinity
// and NaN kept, raising nothing, in each type.
// [C99:6.2.5p13]:  a complex type, an array of its real and imaginary parts
// [C99:7.3.9.5p2]: creal, the real part, footnote 171
// [C99:7.3.9.5p3]: creal, the real part's value
// [C99:G.6p5]:     cimag, conj, cproj and creal, raising no exception
static void Test_ComplexCreal(void)
{
    float complex z = make_float(-0.75f, 8);

    feclearexcept(FE_ALL_EXCEPT);
    _TEST_FLOAT(crealf(z), -0.75f);
    _TEST_FLOAT(creal(make_double(DBL_MIN, NAN)), DBL_MIN);
    _TEST_FLOAT(creall(make_ldouble(-LDBL_MAX, 1)), -LDBL_MAX);
    _TEST_TRUE(creal(make_double(-0.0, 1)) == 0 && signbit(creal(make_double(-0.0, 1))));
    _TEST_FLOAT(creall(make_ldouble(INFINITY, NAN)), INFINITY);
    _TEST_TRUE(isnan(creal(make_double(-NAN, 1))) && signbit(creal(make_double(-NAN, 1))));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT), 0);
    _TEST_TRUE(z == crealf(z) + cimagf(z) * I);
}

int main(void)
{
    Test_ComplexCreal();
    return _Test_Status();
}
