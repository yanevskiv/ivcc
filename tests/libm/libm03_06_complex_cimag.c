// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cimag.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

#pragma STDC FENV_ACCESS ON

// cimag should give the imaginary part, the second element, as a real, its
// sign, infinity and NaN kept, raising nothing, in each type.
// [C99:6.2.5p13]:  a complex type, an array of its real and imaginary parts
// [C99:7.3.9.2p2]: cimag, the imaginary part, footnote 170
// [C99:7.3.9.2p3]: cimag, the imaginary part as a real
// [C99:G.6p5]:     cimag, conj, cproj and creal, raising no exception
static void Test_ComplexCimag(void)
{
    double complex z = make_double(1.5, -2.25);

    feclearexcept(FE_ALL_EXCEPT);
    _TEST_FLOAT(cimag(z), -2.25);
    _TEST_FLOAT(cimagf(make_float(NAN, 0x1p-149f)), 0x1p-149f);
    _TEST_FLOAT(cimagl(make_ldouble(1, LDBL_MAX)), LDBL_MAX);
    _TEST_TRUE(cimag(make_double(1, -0.0)) == 0 && signbit(cimag(make_double(1, -0.0))));
    _TEST_FLOAT(cimag(make_double(NAN, -INFINITY)), -INFINITY);
    _TEST_TRUE(isnan(cimagf(make_float(1, NAN))));
    _TEST_TRUE(isnan(cimagl(make_ldouble(1, -NAN))) && signbit(cimagl(make_ldouble(1, -NAN))));
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT), 0);
    _TEST_TRUE(z == creal(z) + cimag(z) * I);
}

int main(void)
{
    Test_ComplexCimag();
    return _Test_Status();
}
