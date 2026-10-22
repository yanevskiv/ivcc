// (Test) Status: 0
// A test file for <_real.h> exponents read.

// Include helpers.
#include "_util08_00_real_helpers.inc"

// An exponent should need its letter and a digit, and be none without them.
static void Test_RealExponent(void)
{
    long exp = 0;

    _TEST_TRUE(raises("e10", 'e', 10, 3));
    _TEST_TRUE(raises("E-5x", 'e', -5, 3));
    _TEST_TRUE(raises("e+07", 'e', 7, 4));
    _TEST_TRUE(raises("P12", 'p', 12, 3));
    _TEST_TRUE(raises("e", 'e', 0, 0));
    _TEST_TRUE(raises("e+", 'e', 0, 0));
    _TEST_TRUE(raises("e-x", 'e', 0, 0));
    _TEST_TRUE(raises("p1", 'e', 0, 0));
    _TEST_TRUE(raises("1", 'e', 0, 0));
    _TEST_TRUE(raises("", 'e', 0, 0));
    _TEST_UINT(_Real_ReadExponent("1e99999999999999999999999999z", _REAL_TEXT_NARROW, 1, 'e', &exp), 28);
    _TEST_TRUE(exp >= _REAL_EXP_LIMIT);
    _TEST_UINT(_Real_ReadExponent("1e-99999999999999999999999999", _REAL_TEXT_NARROW, 1, 'e', &exp), 29);
    _TEST_TRUE(exp <= -_REAL_EXP_LIMIT);
}

int main(void)
{
    Test_RealExponent();
    return _Test_Status();
}
