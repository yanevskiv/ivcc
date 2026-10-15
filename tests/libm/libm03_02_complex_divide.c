// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> division by complex values.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

// A quotient should follow the usual formula where it is exact, in each
// type, a real dividend taken as a complex one.
// [C99:G.5.1p3]: / by a complex operand, complex division
// [C99:G.5.1p5]: / by a complex operand, exceptions as its parts' calculation raises
static void Test_ComplexDivideExact(void)
{
    float _Complex f = make_float(-4.25f, -4.25f) / make_float(-2, 0.5f);
    double _Complex d = make_double(-5, 10) / make_double(3, 4);
    long double _Complex l = make_ldouble(-7.4375L, 7.5L) / make_ldouble(2, 0);

    _TEST_FLOAT(REAL(f, float), 1.5f);
    _TEST_FLOAT(IMAG(f, float), 2.5f);
    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_FLOAT(IMAG(d, double), 2);
    _TEST_FLOAT(REAL(l, long double), -3.71875L);
    _TEST_FLOAT(IMAG(l, long double), 3.75L);
    d = 10 / make_double(1, 2);
    _TEST_FLOAT(REAL(d, double), 2);
    _TEST_FLOAT(IMAG(d, double), -4);
    d = make_double(1, 2) / make_double(0, 1);
    _TEST_FLOAT(REAL(d, double), 2);
    _TEST_FLOAT(IMAG(d, double), -1);
}

// An infinity over a finite number, and a nonzero finite number or an
// infinity over a zero, should be an infinity.
// [C99:G.3p1]:   an infinity, a value with an infinite part
// [C99:G.5.1p4]: / of an infinity by a finite number, or of a nonzero by a zero, an infinity
static void Test_ComplexDivideInfinity(void)
{
    _TEST_TRUE(is_inf_double(make_double(INFINITY, NAN) / make_double(1, 1)));
    _TEST_TRUE(is_inf_double(make_double(NAN, -INFINITY) / make_double(0, 3)));
    _TEST_TRUE(is_inf_double(make_double(1, 0) / make_double(0, 0)));
    _TEST_TRUE(is_inf_double(make_double(INFINITY, 1) / make_double(0, 0)));
    _TEST_TRUE(is_inf_double(make_double(NAN, 1) / make_double(0, 0)));
    _TEST_TRUE(is_inf_float(make_float(INFINITY, NAN) / make_float(2, 0)));
    _TEST_TRUE(is_inf_float(make_float(0, -1) / make_float(0, 0)));
    _TEST_TRUE(is_inf_ldouble(make_ldouble(NAN, INFINITY) / make_ldouble(1, -1)));
    _TEST_TRUE(is_inf_ldouble(make_ldouble(3, 0) / make_ldouble(-0.0L, 0)));
}

// A finite number over an infinity should be a zero.
// [C99:G.5.1p4]: / of a finite number by an infinity, a zero
static void Test_ComplexDivideZero(void)
{
    _TEST_TRUE(is_zero_double(make_double(1, 1) / make_double(INFINITY, NAN)));
    _TEST_TRUE(is_zero_double(make_double(-2, 0) / make_double(NAN, -INFINITY)));
    _TEST_TRUE(is_zero_double(make_double(0, 0) / make_double(INFINITY, INFINITY)));
    _TEST_TRUE(is_zero_float(make_float(1, 2) / make_float(INFINITY, 0)));
    _TEST_TRUE(is_zero_ldouble(make_ldouble(LDBL_MAX, 1) / make_ldouble(1, INFINITY)));
}

int main(void)
{
    Test_ComplexDivideExact();
    Test_ComplexDivideInfinity();
    Test_ComplexDivideZero();
    return _Test_Status();
}
