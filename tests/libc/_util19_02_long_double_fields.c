// (Test) Status: 0
// A test file for <_long_double.h> fields.

// Includes.
#include <_test.h>
#include <_long_double.h>

// A long double's leading significand bit and its exponent of every bit set.
#define LEAD (1ULL << (_LONG_DOUBLE_MANT - 1))
#define ONES (2U * _LONG_DOUBLE_EXP_MAX + 1)

// The fields should read and make a long double's bits, its classes taking the
// x87's refused encodings as NaNs, and the sign functions should write them.
static void Test_LongDoubleFields(void)
{
    long double unnormal = _Long_Double_MakeValue(0, _LONG_DOUBLE_EXP_MAX, 0);
    long double pseudo_inf = _Long_Double_MakeValue(0, ONES, 0);
    long double inf = _Long_Double_MakeValue(0, ONES, LEAD);
    long double nan = _Long_Double_MakeValue(0, ONES, LEAD | 1U);
    int exp;

    _TEST_FLOAT(_Long_Double_MakeValue(1, _LONG_DOUBLE_EXP_MAX, LEAD), -1.0L);
    _TEST_UINT(_Long_Double_ReadExponent(-1.0L), _LONG_DOUBLE_EXP_MAX);
    _TEST_UINT(_Long_Double_ReadSignificand(1.5L), LEAD | LEAD >> 1);
    _TEST_UINT(_Long_Double_ReadSignificand(_LONG_DOUBLE_TRUE_MIN), 1U);

    _TEST_INT(_Long_Double_ReadClass(-0.0L), _LONG_DOUBLE_CLASS_ZERO);
    _TEST_INT(_Long_Double_ReadClass(_LONG_DOUBLE_TRUE_MIN), _LONG_DOUBLE_CLASS_SUBNORMAL);
    _TEST_INT(_Long_Double_ReadClass(_LONG_DOUBLE_MIN), _LONG_DOUBLE_CLASS_NORMAL);
    _TEST_INT(_Long_Double_ReadClass(-inf), _LONG_DOUBLE_CLASS_INFINITE);
    _TEST_INT(_Long_Double_ReadClass(_Long_Double_MakeNan(1U)), _LONG_DOUBLE_CLASS_NAN);

    _TEST_TRUE(_Long_Double_IsNan(nan));
    _TEST_TRUE(_Long_Double_IsNan(unnormal));
    _TEST_TRUE(_Long_Double_IsNan(pseudo_inf));
    _TEST_TRUE(! _Long_Double_IsNan(inf));
    _TEST_TRUE(! _Long_Double_IsNan(_LONG_DOUBLE_TRUE_MIN));
    _TEST_TRUE(_Long_Double_IsInf(inf));
    _TEST_TRUE(_Long_Double_IsInf(-inf));
    _TEST_TRUE(! _Long_Double_IsInf(pseudo_inf));
    _TEST_TRUE(_Long_Double_IsNegative(-0.0L));
    _TEST_TRUE(! _Long_Double_IsNegative(0.0L));

    _TEST_FLOAT(_Long_Double_ClearSign(-2.5L), 2.5L);
    _TEST_FLOAT(_Long_Double_CopySign(2.5L, -0.0L), -2.5L);
    _TEST_FLOAT(_Long_Double_CopySign(-2.5L, 1.0L), 2.5L);

    _TEST_UINT(_Long_Double_SplitValue(_LONG_DOUBLE_TRUE_MIN, &exp), _LONG_DOUBLE_SPLIT_TOP);
    _TEST_INT(exp, _LONG_DOUBLE_EXP_MIN - _LONG_DOUBLE_MANT + 1);
    _TEST_FLOAT(_Long_Double_JoinValue(exp, _LONG_DOUBLE_SPLIT_TOP), _LONG_DOUBLE_TRUE_MIN);
    _TEST_FLOAT(_Long_Double_StepValue(1.0L, _LONG_DOUBLE_STEP_UP), 1.0L + _LONG_DOUBLE_EPSILON);
    _TEST_FLOAT(_Long_Double_StepValue(1.0L, _LONG_DOUBLE_STEP_DOWN), 1.0L - _LONG_DOUBLE_EPSILON / 2);
}

int main(void)
{
    Test_LongDoubleFields();
    return _Test_Status();
}
