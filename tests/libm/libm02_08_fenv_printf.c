// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> rounding directions in printf's decimal conversions.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"

// Defines.
#define HOLD 32

// snprintf should write value by format as want.
static bool prints(const char *want, const char *format, double value)
{
    char got[HOLD];

    snprintf(got, sizeof(got), format, value);
    return _TEST_STR(got, want);
}

// %f, %e and %g should round a value to their precision in the current
// direction, a negative one by its own value, a tie only to nearest by its
// even digit.
// [C99:3.9p1]:       a correctly rounded result, subject to the rounding mode
// [C99:7.19.6.1p13]: e, f and g of DECIMAL_DIG digits correctly rounded
// [C99:F.5p2]:       decimal conversions correctly rounded in the current mode
static void Test_FenvPrintf(void)
{
    fesetround(FE_TONEAREST);
    _TEST_TRUE(prints("0.002", "%.3f", 0.0015));
    _TEST_TRUE(prints("-0.002", "%.3f", -0.0015));
    _TEST_TRUE(prints("1.50e-03", "%.2e", 0.0015));
    _TEST_TRUE(prints("2", "%.0f", 2.5));
    _TEST_TRUE(prints("-2", "%.0f", -2.5));
    _TEST_TRUE(prints("0", "%.0f", 0.0001));
    _TEST_TRUE(prints("1000", "%.0f", 999.5));
    _TEST_TRUE(prints("1e+03", "%.3g", 999.5));

    fesetround(FE_UPWARD);
    _TEST_TRUE(prints("0.002", "%.3f", 0.0015));
    _TEST_TRUE(prints("-0.001", "%.3f", -0.0015));
    _TEST_TRUE(prints("1.51e-03", "%.2e", 0.0015));
    _TEST_TRUE(prints("-1.50e-03", "%.2e", -0.0015));
    _TEST_TRUE(prints("3", "%.0f", 2.5));
    _TEST_TRUE(prints("-2", "%.0f", -2.5));
    _TEST_TRUE(prints("1", "%.0f", 0.0001));
    _TEST_TRUE(prints("-0", "%.0f", -0.0001));
    _TEST_TRUE(prints("1.00e+01", "%.2e", 9.99));
    _TEST_TRUE(prints("0.334", "%.3g", 1.0 / 3.0));

    fesetround(FE_DOWNWARD);
    _TEST_TRUE(prints("0.001", "%.3f", 0.0015));
    _TEST_TRUE(prints("-0.002", "%.3f", -0.0015));
    _TEST_TRUE(prints("-3", "%.0f", -2.5));
    _TEST_TRUE(prints("0", "%.0f", 0.0001));
    _TEST_TRUE(prints("-1", "%.0f", -0.0001));
    _TEST_TRUE(prints("999", "%.0f", 999.5));
    _TEST_TRUE(prints("999", "%.3g", 999.5));
    _TEST_TRUE(prints("9", "%.0f", 9.99));

    fesetround(FE_TOWARDZERO);
    _TEST_TRUE(prints("0.001", "%.3f", 0.0015));
    _TEST_TRUE(prints("-0.001", "%.3f", -0.0015));
    _TEST_TRUE(prints("-2", "%.0f", -2.5));
    _TEST_TRUE(prints("-0", "%.0f", -0.0001));
    _TEST_TRUE(prints("999", "%.0f", 999.5));
    _TEST_TRUE(prints("9.99e+00", "%.2e", 9.99));
    fesetround(FE_TONEAREST);
}

int main(void)
{
    Test_FenvPrintf();
    return _Test_Status();
}
