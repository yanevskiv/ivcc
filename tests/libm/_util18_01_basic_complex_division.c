// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <_basic_complex.h> parts, boxes and scaled division.

// Includes.
#include <_test.h>
#include <_exact.h>
#include <_basic_math.h>
#include <_basic_complex.h>

// Defines.
#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

// A joined value should hold its parts in order, and a box should keep a
// part's sign, an infinity to 1 and anything else to 0, a NaN cleared alone.
static void Test_BasicComplexParts(void)
{
    float _Complex f = _Basic_Complex_JoinFloat(1.5f, -2);
    double _Complex d = _Basic_Complex_JoinDouble(-0.0, 3);
    long double _Complex l = _Basic_Complex_JoinLDouble(0x1p-16445L, -0x1p16383L);

    _TEST_FLOAT(REAL(f, float), 1.5f);
    _TEST_FLOAT(IMAG(f, float), -2);
    _TEST_TRUE(REAL(d, double) == 0 && _BASIC_MATH_SIGNBIT(REAL(d, double)));
    _TEST_FLOAT(IMAG(d, double), 3);
    _TEST_FLOAT(REAL(l, long double), 0x1p-16445L);
    _TEST_FLOAT(IMAG(l, long double), -0x1p16383L);

    _TEST_FLOAT(_Basic_Complex_BoxInfinity(-_EXACT_INFINITY), -1);
    _TEST_FLOAT(_Basic_Complex_BoxInfinity(_EXACT_INFINITY), 1);
    _TEST_TRUE(_Basic_Complex_BoxInfinity(-2.5L) == 0 && _BASIC_MATH_SIGNBIT(_Basic_Complex_BoxInfinity(-2.5L)));
    _TEST_TRUE(_Basic_Complex_ClearNan(-__builtin_nanl("")) == 0 && _BASIC_MATH_SIGNBIT(_Basic_Complex_ClearNan(-__builtin_nanl(""))));
    _TEST_FLOAT(_Basic_Complex_ClearNan(-2.5L), -2.5L);
}

// Division should scale operands near the largest value down and ones near
// the least up, as libgcc's, so a quotient whose formula would overflow or
// underflow in its terms comes out whole.
static void Test_BasicComplexScaled(void)
{
    double _Complex d = __basic_complex_divdc3(0x1p1023, 0x1p1023, 0x1p1023, 0x1p1023);
    long double _Complex l = __basic_complex_divxc3(0x1p16383L, -0x1p16383L, 0x1p16383L, 0x1p16383L);

    _TEST_FLOAT(REAL(d, double), 1);
    _TEST_FLOAT(IMAG(d, double), 0);
    _TEST_FLOAT(REAL(l, long double), 0);
    _TEST_FLOAT(IMAG(l, long double), -1);
    d = __basic_complex_divdc3(0x1p-1070, 0x1p-1070, 0x1p-1072, 0);
    _TEST_FLOAT(REAL(d, double), 4);
    _TEST_FLOAT(IMAG(d, double), 4);
    l = __basic_complex_divxc3(0x1p-16440L, 0, 0, 0x1p-16442L);
    _TEST_FLOAT(REAL(l, long double), 0);
    _TEST_FLOAT(IMAG(l, long double), -4);
    d = __basic_complex_divdc3(1, 0, 0x1p-1060, 0x1p1000);
    _TEST_FLOAT(REAL(d, double), 0);
    _TEST_FLOAT(IMAG(d, double), -0x1p-1000);
}

// A float quotient should be computed in double, so terms past float's
// range still give the quotient.
static void Test_BasicComplexFloat(void)
{
    float _Complex f = __basic_complex_divsc3(0x1p127f, 0x1p127f, 0x1p127f, 0x1p127f);

    _TEST_FLOAT(REAL(f, float), 1);
    _TEST_FLOAT(IMAG(f, float), 0);
    f = __basic_complex_divsc3(0x1p-149f, 0, 0x1p-149f, 0x1p-149f);
    _TEST_FLOAT(REAL(f, float), 0.5f);
    _TEST_FLOAT(IMAG(f, float), -0.5f);
}

int main(void)
{
    Test_BasicComplexParts();
    Test_BasicComplexScaled();
    Test_BasicComplexFloat();
    return _Test_Status();
}
