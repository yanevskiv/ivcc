// (Test) Compiler flags: -lm
// (Test) Status: 0
// (Test) Output:
// | 1e999 down 0x1.fffffffffffffp+1023 1
// | 1e999 zero 0x1.fffffffffffffp+1023 1
// | 1e999 up inf 1
// | -1e999 up -0x1.fffffffffffffp+1023 1
// | -1e999 down -inf 1
// | 1.7976931348623159e308 down 0x1.fffffffffffffp+1023 0
// | 1.7976931348623159e308 near inf 1
// | 0x1.fffffffffffff8p1023 zero 0x1.fffffffffffffp+1023 0
// | 1e99 float zero 0x1.fffffep+127 1
// Non-standard: strtod should give the greatest finite value where the
// direction rounds an overflow toward zero, and ERANGE only when the value
// rounded in it overflows, as IEC 60559 and glibc.
// Liberty: C99 asks HUGE_VAL of a value out of range and asks the conversion
// to honour the direction, which a directed overflow cannot both meet;
// <math.h> asks HUGE_VAL only in the default rounding.
// [C99:7.12.1p4]:    an overflow HUGE_VAL when default rounding is in effect
// [C99:7.20.1.3p10]: a value out of range HUGE_VAL, and ERANGE
// [C99:F.5p3]:       strtod honours the rounding direction

#include <errno.h>
#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#pragma STDC FENV_ACCESS ON

// Show what strtod and its ERANGE give of str in one direction.
static void show(const char *str, const char *name, int round)
{
    double value;
    int range;

    fesetround(round);
    errno = 0;
    value = strtod(str, NULL);
    range = errno == ERANGE;
    fesetround(FE_TONEAREST);
    printf("%s %s %a %d\n", str, name, value, range);
}

// Show what strtof and its ERANGE give of str in one direction.
static void show_float(const char *str, const char *name, int round)
{
    float value;
    int range;

    fesetround(round);
    errno = 0;
    value = strtof(str, NULL);
    range = errno == ERANGE;
    fesetround(FE_TONEAREST);
    printf("%s float %s %a %d\n", str, name, value, range);
}

int main(void)
{
    show("1e999", "down", FE_DOWNWARD);
    show("1e999", "zero", FE_TOWARDZERO);
    show("1e999", "up", FE_UPWARD);
    show("-1e999", "up", FE_UPWARD);
    show("-1e999", "down", FE_DOWNWARD);
    show("1.7976931348623159e308", "down", FE_DOWNWARD);
    show("1.7976931348623159e308", "near", FE_TONEAREST);
    show("0x1.fffffffffffff8p1023", "zero", FE_TOWARDZERO);
    show_float("1e99", "zero", FE_TOWARDZERO);
    return 0;
}
