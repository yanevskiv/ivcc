// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> multiplication of complex values.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

// A product should follow the usual formula where it is exact, in each type.
// [C99:G.5.1p5]: * of complex operands, exceptions as its parts' calculation raises
static void Test_ComplexMultiplyExact(void)
{
    float _Complex f = make_float(1.5f, 2.5f) * make_float(-2, 0.5f);
    double _Complex d = make_double(1, 2) * make_double(3, 4);
    long double _Complex l = make_ldouble(1.25L, 3) * make_ldouble(1.25L, 3);

    _TEST_FLOAT(REAL(f, float), -4.25f);
    _TEST_FLOAT(IMAG(f, float), -4.25f);
    _TEST_FLOAT(REAL(d, double), -5);
    _TEST_FLOAT(IMAG(d, double), 10);
    _TEST_FLOAT(REAL(l, long double), -7.4375L);
    _TEST_FLOAT(IMAG(l, long double), 7.5L);
    d = make_double(0, 1) * make_double(0, 1);
    _TEST_FLOAT(REAL(d, double), -1);
    _TEST_FLOAT(IMAG(d, double), 0);
}

// An infinity times a nonzero finite number or an infinity should be an
// infinity, even where the formula gives NaN + iNaN, a NaN part beside it.
// [C99:G.3p1]:   an infinity, a value with an infinite part
// [C99:G.5.1p4]: * of an infinity, an infinity
static void Test_ComplexMultiplyInfinity(void)
{
    _TEST_TRUE(is_inf_double(make_double(INFINITY, NAN) * make_double(1, 1)));
    _TEST_TRUE(is_inf_double(make_double(1, 1) * make_double(NAN, -INFINITY)));
    _TEST_TRUE(is_inf_double(make_double(INFINITY, INFINITY) * make_double(INFINITY, -INFINITY)));
    _TEST_TRUE(is_inf_double(make_double(0, INFINITY) * make_double(2, 0)));
    _TEST_TRUE(is_inf_double(make_double(DBL_MAX, DBL_MAX) * make_double(DBL_MAX, NAN)));
    _TEST_TRUE(is_inf_float(make_float(INFINITY, NAN) * make_float(0, 1)));
    _TEST_TRUE(is_inf_float(make_float(FLT_MAX, FLT_MAX) * make_float(FLT_MAX, NAN)));
    _TEST_TRUE(is_inf_ldouble(make_ldouble(NAN, INFINITY) * make_ldouble(-1, 0)));
    _TEST_TRUE(is_inf_ldouble(make_ldouble(LDBL_MAX, LDBL_MAX) * make_ldouble(LDBL_MAX, NAN)));
}

// A product with a NaN and no infinity should stay a NaN.
// [C99:G.5.1p4]: * of an infinity, an infinity
static void Test_ComplexMultiplyNan(void)
{
    double _Complex d = make_double(NAN, 1) * make_double(1, 1);
    long double _Complex l = make_ldouble(NAN, NAN) * make_ldouble(2, 3);

    _TEST_TRUE(! is_inf_double(d) && (isnan(REAL(d, double)) || isnan(IMAG(d, double))));
    _TEST_TRUE(isnan(REAL(l, long double)) && isnan(IMAG(l, long double)));
}

int main(void)
{
    Test_ComplexMultiplyExact();
    Test_ComplexMultiplyInfinity();
    Test_ComplexMultiplyNan();
    return _Test_Status();
}
