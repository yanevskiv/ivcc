// (Test) Status: 0
// A test file for <_real.h> formats against <float.h>'s.

// Includes.
#include <_test.h>
#include <float.h>
#include <_real.h>

// The formats of float and double _real converts to should be float.h's.
static void Test_RealFormats(void)
{
    _Static_assert(FLT_MANT_DIG == _REAL_FLOAT_MANT, "a float's mantissa should be _real's");
    _Static_assert(FLT_MIN_EXP - 1 == _REAL_FLOAT_MIN, "a float's least exponent should be _real's");
    _Static_assert(FLT_MAX_EXP - 1 == _REAL_FLOAT_MAX, "a float's greatest exponent should be _real's");
    _Static_assert(DBL_MANT_DIG == _REAL_DOUBLE_MANT, "a double's mantissa should be _real's");
    _Static_assert(DBL_MIN_EXP - 1 == _REAL_DOUBLE_MIN, "a double's least exponent should be _real's");
    _Static_assert(DBL_MAX_EXP - 1 == _REAL_DOUBLE_MAX, "a double's greatest exponent should be _real's");
}

int main(void)
{
    Test_RealFormats();
    return _Test_Status();
}
