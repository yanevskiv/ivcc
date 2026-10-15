// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> unary minus, a sign flip in any direction.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"
#include <math.h>

// Operands the compiler cannot fold.
static volatile float fzero = 0.0f;
static volatile double zero = 0.0;
static volatile long double lzero = 0.0L;
static volatile float fnan = NAN;
static volatile double dnan = NAN;
static volatile long double lnan = NAN;

// Unary minus should flip a zero's sign in every direction, never giving
// 0 - x's +0, and flip a NaN's sign raising no flag.
// [C99:6.5.3.3p3]: unary -, the negative of its operand
// [C99:F.3p1]:     the - operator, IEC 60559's subtract
// [C99:F.8.2p1]:   -x and 0 - x differ where x is +0
static void Test_FenvNegation(void)
{
    for (int iter = 0; iter < MODES; iter++) {
        fesetround(modes[iter]);
        _TEST_TRUE(signbit(-fzero) != 0);
        _TEST_TRUE(signbit(-zero) != 0);
        _TEST_TRUE(signbit(-lzero) != 0);
        _TEST_TRUE(signbit(-(-zero)) == 0);
        _TEST_TRUE(signbit(-(-lzero)) == 0);
    }
    fesetround(FE_TONEAREST);

    feclearexcept(FE_ALL_EXCEPT);
    _TEST_TRUE(signbit(-fnan) != 0);
    _TEST_TRUE(signbit(-dnan) != 0);
    _TEST_TRUE(signbit(-lnan) != 0);
    _TEST_INT(fetestexcept(FE_ALL_EXCEPT), 0);
}

int main(void)
{
    Test_FenvNegation();
    return _Test_Status();
}
