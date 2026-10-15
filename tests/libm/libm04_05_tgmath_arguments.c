// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for the arguments <tgmath.h>'s macros take.

// Include helpers.
#include "libm04_00_tgmath_helpers.inc"

// The values of an enumerated type.
enum Level {
    LEVEL_LOW = 1,
    LEVEL_HIGH
};

// Each macro should evaluate each argument once, count an argument of every
// integer type as double, take the widest of its generic arguments and a
// complex one's domain, and give way to the function where its name is not
// followed by a parenthesis.
// [C99:7.1.4p1]: a library macro, its arguments evaluated once, suppressed by parentheses
// [C99:7.22p3]:  long double if any is, else double if any is or is an integer, else float
// [C99:7.22p4]:  a complex function if any argument is complex, else a real one
static void Test_TgmathArguments(void)
{
    float              values[3] = { 1, 4, 9 };
    int                index = 0;
    int                count = 0;
    float             *ptr = values;
    _Bool              flag = 1;
    char               letter = 4;
    unsigned long long huge = 16;
    enum Level         level = LEVEL_HIGH;
    float              arg_f = 0.5f;
    float _Complex     arg_cf = make_float(0.5f, 2);
    int                exps[2] = { 0, 0 };

    _TEST_TRUE(sqrt(values[index++]) == 1 && index == 1);
    _TEST_TRUE(pow(values[index++], ++count) == 4 && index == 2 && count == 1);
    _TEST_TRUE(fma(*ptr++, values[1], values[index++]) == 13 && index == 3);
    _TEST_TRUE(ptr == values + 1);
    _TEST_TRUE(frexp(values[--index], &exps[count++]) == 0.5625f && index == 2 && count == 2);
    _TEST_INT(exps[1], 4);

    _TEST_INT(KIND(sqrt(flag)), KIND_DOUBLE);
    _TEST_INT(KIND(sqrt(letter)), KIND_DOUBLE);
    _TEST_INT(KIND(sqrt(huge)), KIND_DOUBLE);
    _TEST_INT(KIND(sqrt(level)), KIND_DOUBLE);
    _TEST_INT(KIND(sqrt('a')), KIND_DOUBLE);
    _TEST_TRUE(sqrt(letter) == 2 && sqrt(huge) == 4);

    _TEST_INT(KIND(atan2(arg_f, letter)), KIND_DOUBLE);
    _TEST_INT(KIND(hypot(arg_f, 1.0f)), KIND_FLOAT);
    _TEST_INT(KIND(fmax(arg_f, 1.0)), KIND_DOUBLE);
    _TEST_INT(KIND(fmin(1.0L, arg_f)), KIND_LDOUBLE);
    _TEST_INT(KIND(pow(arg_cf, letter)), KIND_DOUBLE_COMPLEX);
    _TEST_INT(KIND(pow(arg_cf, 2.0f)), KIND_FLOAT_COMPLEX);
    _TEST_INT(KIND(pow(1.0L, arg_cf)), KIND_LDOUBLE_COMPLEX);

    _TEST_INT(KIND((sqrt)(arg_f)), KIND_DOUBLE);
    _TEST_INT(KIND((fabs)(-arg_f)), KIND_DOUBLE);
    _TEST_INT(KIND((creal)(arg_cf)), KIND_DOUBLE);
}

int main(void)
{
    Test_TgmathArguments();
    return _Test_Status();
}
