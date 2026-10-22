// (Test) Status: 0
// A test file for <_ldouble.h> format against <float.h>'s.

// Includes.
#include <_test.h>
#include <limits.h>
#include <float.h>
#include <_ldouble.h>

// The long double format _ldouble reads should be float.h's.
static void Test_LdoubleFormat(void)
{
    _Static_assert(LDBL_MANT_DIG == _LDOUBLE_MANT, "a long double's mantissa should be _ldouble's");
    _Static_assert(LDBL_MIN_EXP - 1 == _LDOUBLE_EXP_MIN, "a long double's least exponent should be _ldouble's");
    _Static_assert(LDBL_MAX_EXP - 1 == _LDOUBLE_EXP_MAX, "a long double's greatest exponent should be _ldouble's");
    _Static_assert(LDBL_MAX_EXP == 1 << (_LDOUBLE_EXP_BITS - 1), "a long double's exponent should fill its bits");
    _Static_assert(_LDOUBLE_MANT <= _LDOUBLE_SPLIT_BITS, "a long double's mantissa should fit a split significand");
    _Static_assert(_LDOUBLE_SPLIT_BITS == sizeof(unsigned long long) * CHAR_BIT, "a split significand should fill a word");
    _Static_assert(_LDOUBLE_SPLIT_TOP == 1ULL << _LDOUBLE_SPLIT_SHIFT, "a split significand's top bit should be at its place");

    _TEST_TRUE(_LDOUBLE_MIN == LDBL_MIN);
    _TEST_TRUE(_LDOUBLE_MAX == LDBL_MAX);
    _TEST_TRUE(_LDOUBLE_EPSILON == LDBL_EPSILON);
    _TEST_TRUE(_LDOUBLE_TRUE_MIN == LDBL_MIN * LDBL_EPSILON);
    _TEST_TRUE(_LDOUBLE_INTEGRAL == 1 / LDBL_EPSILON);
}

int main(void)
{
    Test_LdoubleFormat();
    return _Test_Status();
}
