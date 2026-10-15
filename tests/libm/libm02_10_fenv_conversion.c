// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> invalid raised by a floating to integer conversion.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"
#include <math.h>

// Return whether converting value to int raises invalid.
static bool float_int(float value)
{
    volatile float source = value;
    volatile int result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (int) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// Return whether converting value to long raises invalid.
static bool float_long(float value)
{
    volatile float source = value;
    volatile long result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (long) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// Return whether converting value to int raises invalid.
static bool double_int(double value)
{
    volatile double source = value;
    volatile int result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (int) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// Return whether converting value to long long raises invalid.
static bool double_llong(double value)
{
    volatile double source = value;
    volatile long long result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (long long) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// Return whether converting value to int raises invalid.
static bool ldouble_int(long double value)
{
    volatile long double source = value;
    volatile int result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (int) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// Return whether converting value to long raises invalid.
static bool ldouble_long(long double value)
{
    volatile long double source = value;
    volatile long result;

    feclearexcept(FE_ALL_EXCEPT);
    result = (long) source;
    (void) result;
    return fetestexcept(FE_INVALID) != 0;
}

// A floating value converted to int, long or long long should raise invalid
// when it is infinite or NaN or its integral part is out of the type's range,
// and not when the integral part is in range, however near the end.
// [C99:6.3.1.4p1]: a floating value converted to an integer, truncated toward zero
// [C99:F.4p1]:     infinite, NaN or out of range, invalid
static void Test_FenvConversion(void)
{
    _TEST_TRUE(!float_int(0x1.fffffep30f));
    _TEST_TRUE(float_int(0x1p31f));
    _TEST_TRUE(!float_int(-0x1p31f));
    _TEST_TRUE(float_int(-0x1.000002p31f));
    _TEST_TRUE(float_int(NAN));
    _TEST_TRUE(float_int(INFINITY));
    _TEST_TRUE(!float_long(-0x1p63f));
    _TEST_TRUE(float_long(0x1p63f));

    _TEST_TRUE(!double_int(2147483647.9));
    _TEST_TRUE(double_int(2147483648.0));
    _TEST_TRUE(!double_int(-2147483648.9));
    _TEST_TRUE(double_int(-2147483649.0));
    _TEST_TRUE(double_int(-INFINITY));
    _TEST_TRUE(!double_llong(-0x1p63));
    _TEST_TRUE(double_llong(0x1p63));
    _TEST_TRUE(double_llong(NAN));

    _TEST_TRUE(!ldouble_int(2147483647.9L));
    _TEST_TRUE(ldouble_int(2147483648.0L));
    _TEST_TRUE(!ldouble_int(-2147483648.9L));
    _TEST_TRUE(ldouble_int(-2147483649.0L));
    _TEST_TRUE(!ldouble_long(0x1.fffffffffffffffep62L));
    _TEST_TRUE(ldouble_long(0x1p63L));
    _TEST_TRUE(!ldouble_long(-0x1p63L));
    _TEST_TRUE(ldouble_long(-0x1.0000000000000002p63L));
    _TEST_TRUE(ldouble_long(NAN));
    feclearexcept(FE_ALL_EXCEPT);
}

int main(void)
{
    Test_FenvConversion();
    return _Test_Status();
}
