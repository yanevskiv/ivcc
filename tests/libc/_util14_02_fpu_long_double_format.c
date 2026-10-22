// (Test) Status: 0
// A test file for <_fpu.h> long double format against <float.h>'s.

// Includes.
#include <_test.h>
#include <limits.h>
#include <float.h>
#include <_fpu.h>

// The long double format _fpu reads should be float.h's.
static void Test_LongDoubleFormat(void)
{
    _Static_assert(LDBL_MANT_DIG == _FPU_X86_64_LDBL_MANT, "a long double's mantissa should be _fpu's");
    _Static_assert(LDBL_MIN_EXP - 1 == _FPU_X86_64_LDBL_EXP_MIN, "a long double's least exponent should be _fpu's");
    _Static_assert(LDBL_MAX_EXP - 1 == _FPU_X86_64_LDBL_EXP_MAX, "a long double's greatest exponent should be _fpu's");
    _Static_assert(LDBL_MAX_EXP == 1 << (_FPU_X86_64_LDBL_EXP_BITS - 1), "a long double's exponent should fill its bits");
    _Static_assert(_FPU_X86_64_LDBL_MANT <= _FPU_SPLIT_BITS, "a long double's mantissa should fit a split significand");
    _Static_assert(_FPU_SPLIT_BITS == sizeof(unsigned long long) * CHAR_BIT, "a split significand should fill a word");
    _Static_assert(_FPU_SPLIT_TOP == 1ULL << _FPU_SPLIT_SHIFT, "a split significand's top bit should be at its place");

    _TEST_TRUE(_FPU_X86_64_LDBL_MIN == LDBL_MIN);
    _TEST_TRUE(_FPU_X86_64_LDBL_MAX == LDBL_MAX);
    _TEST_TRUE(_FPU_X86_64_LDBL_EPSILON == LDBL_EPSILON);
    _TEST_TRUE(_FPU_X86_64_LDBL_TRUE_MIN == LDBL_MIN * LDBL_EPSILON);
    _TEST_TRUE(_FPU_X86_64_LDBL_INTEGRAL == 1 / LDBL_EPSILON);
}

int main(void)
{
    Test_LongDoubleFormat();
    return _Test_Status();
}
