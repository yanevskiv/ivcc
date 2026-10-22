// (Test) Status: 0
// A test file for <_fpu.h> long double fields.

// Includes.
#include <_test.h>
#include <_fpu.h>

// A long double's leading significand bit and its exponent of every bit set.
#define LEAD (1ULL << (_FPU_X86_64_LDBL_MANT - 1))
#define ONES (2U * _FPU_X86_64_LDBL_EXP_MAX + 1)

// The fields should read and make a long double's bits, its classes taking the
// x87's refused encodings as NaNs, and the sign functions should write them.
static void Test_LongDoubleFields(void)
{
    long double unnormal = _Fpu_x86_64_MakeValue(0, _FPU_X86_64_LDBL_EXP_MAX, 0);
    long double pseudo_inf = _Fpu_x86_64_MakeValue(0, ONES, 0);
    long double inf = _Fpu_x86_64_MakeValue(0, ONES, LEAD);
    long double nan = _Fpu_x86_64_MakeValue(0, ONES, LEAD | 1U);
    int exp;

    _TEST_FLOAT(_Fpu_x86_64_MakeValue(1, _FPU_X86_64_LDBL_EXP_MAX, LEAD), -1.0L);
    _TEST_UINT(_Fpu_x86_64_ReadExponent(-1.0L), _FPU_X86_64_LDBL_EXP_MAX);
    _TEST_UINT(_Fpu_x86_64_ReadSignificand(1.5L), LEAD | LEAD >> 1);
    _TEST_UINT(_Fpu_x86_64_ReadSignificand(_FPU_X86_64_LDBL_TRUE_MIN), 1U);

    _TEST_INT(_Fpu_x86_64_ReadClass(-0.0L), _FPU_CLASS_ZERO);
    _TEST_INT(_Fpu_x86_64_ReadClass(_FPU_X86_64_LDBL_TRUE_MIN), _FPU_CLASS_SUBNORMAL);
    _TEST_INT(_Fpu_x86_64_ReadClass(_FPU_X86_64_LDBL_MIN), _FPU_CLASS_NORMAL);
    _TEST_INT(_Fpu_x86_64_ReadClass(-inf), _FPU_CLASS_INFINITE);
    _TEST_INT(_Fpu_x86_64_ReadClass(_Fpu_x86_64_MakeNan(1U)), _FPU_CLASS_NAN);

    _TEST_TRUE(_Fpu_x86_64_IsNan(nan));
    _TEST_TRUE(_Fpu_x86_64_IsNan(unnormal));
    _TEST_TRUE(_Fpu_x86_64_IsNan(pseudo_inf));
    _TEST_TRUE(! _Fpu_x86_64_IsNan(inf));
    _TEST_TRUE(! _Fpu_x86_64_IsNan(_FPU_X86_64_LDBL_TRUE_MIN));
    _TEST_TRUE(_Fpu_x86_64_IsInf(inf));
    _TEST_TRUE(_Fpu_x86_64_IsInf(-inf));
    _TEST_TRUE(! _Fpu_x86_64_IsInf(pseudo_inf));
    _TEST_TRUE(_Fpu_x86_64_IsNegative(-0.0L));
    _TEST_TRUE(! _Fpu_x86_64_IsNegative(0.0L));

    _TEST_FLOAT(_Fpu_x86_64_ClearSign(-2.5L), 2.5L);
    _TEST_FLOAT(_Fpu_x86_64_CopySign(2.5L, -0.0L), -2.5L);
    _TEST_FLOAT(_Fpu_x86_64_CopySign(-2.5L, 1.0L), 2.5L);

    _TEST_UINT(_Fpu_x86_64_SplitValue(_FPU_X86_64_LDBL_TRUE_MIN, &exp), _FPU_SPLIT_TOP);
    _TEST_INT(exp, _FPU_X86_64_LDBL_EXP_MIN - _FPU_X86_64_LDBL_MANT + 1);
    _TEST_FLOAT(_Fpu_x86_64_JoinValue(exp, _FPU_SPLIT_TOP), _FPU_X86_64_LDBL_TRUE_MIN);
    _TEST_FLOAT(_Fpu_x86_64_StepValue(1.0L, _FPU_STEP_UP), 1.0L + _FPU_X86_64_LDBL_EPSILON);
    _TEST_FLOAT(_Fpu_x86_64_StepValue(1.0L, _FPU_STEP_DOWN), 1.0L - _FPU_X86_64_LDBL_EPSILON / 2);
}

int main(void)
{
    Test_LongDoubleFields();
    return _Test_Status();
}
