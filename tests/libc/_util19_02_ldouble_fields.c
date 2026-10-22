// (Test) Status: 0
// A test file for <_ldouble.h> fields.

// Includes.
#include <_test.h>
#include <_ldouble.h>

// A long double's leading significand bit and its exponent of every bit set.
#define LEAD (1ULL << (_LDOUBLE_MANT - 1))
#define ONES (2U * _LDOUBLE_EXP_MAX + 1)

// The fields should read and make a long double's bits, its classes taking the
// x87's refused encodings as NaNs, and the sign functions should write them.
static void Test_LdoubleFields(void)
{
    long double unnormal = _Ldouble_MakeValue(0, _LDOUBLE_EXP_MAX, 0);
    long double pseudo_inf = _Ldouble_MakeValue(0, ONES, 0);
    long double inf = _Ldouble_MakeValue(0, ONES, LEAD);
    long double nan = _Ldouble_MakeValue(0, ONES, LEAD | 1U);
    int exp;

    _TEST_FLOAT(_Ldouble_MakeValue(1, _LDOUBLE_EXP_MAX, LEAD), -1.0L);
    _TEST_UINT(_Ldouble_ReadExponent(-1.0L), _LDOUBLE_EXP_MAX);
    _TEST_UINT(_Ldouble_ReadSignificand(1.5L), LEAD | LEAD >> 1);
    _TEST_UINT(_Ldouble_ReadSignificand(_LDOUBLE_TRUE_MIN), 1U);

    _TEST_INT(_Ldouble_ReadClass(-0.0L), _LDOUBLE_CLASS_ZERO);
    _TEST_INT(_Ldouble_ReadClass(_LDOUBLE_TRUE_MIN), _LDOUBLE_CLASS_SUBNORMAL);
    _TEST_INT(_Ldouble_ReadClass(_LDOUBLE_MIN), _LDOUBLE_CLASS_NORMAL);
    _TEST_INT(_Ldouble_ReadClass(-inf), _LDOUBLE_CLASS_INFINITE);
    _TEST_INT(_Ldouble_ReadClass(_Ldouble_MakeNan(1U)), _LDOUBLE_CLASS_NAN);

    _TEST_TRUE(_Ldouble_IsNan(nan));
    _TEST_TRUE(_Ldouble_IsNan(unnormal));
    _TEST_TRUE(_Ldouble_IsNan(pseudo_inf));
    _TEST_TRUE(! _Ldouble_IsNan(inf));
    _TEST_TRUE(! _Ldouble_IsNan(_LDOUBLE_TRUE_MIN));
    _TEST_TRUE(_Ldouble_IsInf(inf));
    _TEST_TRUE(_Ldouble_IsInf(-inf));
    _TEST_TRUE(! _Ldouble_IsInf(pseudo_inf));
    _TEST_TRUE(_Ldouble_IsNegative(-0.0L));
    _TEST_TRUE(! _Ldouble_IsNegative(0.0L));

    _TEST_FLOAT(_Ldouble_ClearSign(-2.5L), 2.5L);
    _TEST_FLOAT(_Ldouble_CopySign(2.5L, -0.0L), -2.5L);
    _TEST_FLOAT(_Ldouble_CopySign(-2.5L, 1.0L), 2.5L);

    _TEST_UINT(_Ldouble_SplitValue(_LDOUBLE_TRUE_MIN, &exp), _LDOUBLE_SPLIT_TOP);
    _TEST_INT(exp, _LDOUBLE_EXP_MIN - _LDOUBLE_MANT + 1);
    _TEST_FLOAT(_Ldouble_JoinValue(exp, _LDOUBLE_SPLIT_TOP), _LDOUBLE_TRUE_MIN);
    _TEST_FLOAT(_Ldouble_StepValue(1.0L, _LDOUBLE_STEP_UP), 1.0L + _LDOUBLE_EPSILON);
    _TEST_FLOAT(_Ldouble_StepValue(1.0L, _LDOUBLE_STEP_DOWN), 1.0L - _LDOUBLE_EPSILON / 2);
}

int main(void)
{
    Test_LdoubleFields();
    return _Test_Status();
}
