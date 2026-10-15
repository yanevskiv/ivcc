// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> complex, _Complex_I, I and CX_LIMITED_RANGE.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

// The pragma, in either state, outside external declarations.
#pragma STDC CX_LIMITED_RANGE OFF

// complex should name the complex types, and _Complex_I and I the
// imaginary unit, a float complex value whose square is -1.
// [C99:7.3.1p2]: complex, _Complex, and _Complex_I, the imaginary unit in float
// [C99:7.3.1p4]: I, _Complex_I where _Imaginary_I is not defined
static void Test_ComplexMacros(void)
{
    double complex z = 3 + 4 * I;
    float _Complex unit = _Complex_I;

    _TEST_UINT(sizeof(float complex), sizeof(float _Complex));
    _TEST_UINT(sizeof(double complex), sizeof(double _Complex));
    _TEST_UINT(sizeof(long double complex), sizeof(long double _Complex));
    _TEST_UINT(sizeof(_Complex_I), sizeof(float _Complex));
    _TEST_UINT(sizeof(I), sizeof(float _Complex));
    _TEST_FLOAT(REAL(unit, float), 0);
    _TEST_FLOAT(IMAG(unit, float), 1);
    _TEST_TRUE(I == _Complex_I);
    _TEST_TRUE(I * I == -1);
    _TEST_FLOAT(REAL(z, double), 3);
    _TEST_FLOAT(IMAG(z, double), 4);
}

// A program should be able to undefine complex and I and define them again.
// [C99:7.3.1p5]: complex and I, a program's to undefine and redefine
#undef complex
#undef I
#define I 7
static void Test_ComplexRedefine(void)
{
    int complex = I;

    _TEST_INT(complex, 7);
}
#undef I
#define I _Complex_I
#define complex _Complex

// CX_LIMITED_RANGE should be taken at the start of a compound statement and
// leave the finite products and quotients the usual formulas give.
// [C99:7.3.4p2]: CX_LIMITED_RANGE, on to allow the usual formulas, off by default
static void Test_ComplexLimitedRange(void)
{
#pragma STDC CX_LIMITED_RANGE ON
    double complex a = make_double(1, 2);
    double complex b = make_double(3, -4);

    _TEST_TRUE(a * b == make_double(11, 2));
    _TEST_TRUE(make_double(11, 2) / b == a);
    {
#pragma STDC CX_LIMITED_RANGE DEFAULT
        _TEST_TRUE(a * I == make_double(-2, 1));
    }
}

int main(void)
{
    Test_ComplexMacros();
    Test_ComplexRedefine();
    Test_ComplexLimitedRange();
    return _Test_Status();
}
