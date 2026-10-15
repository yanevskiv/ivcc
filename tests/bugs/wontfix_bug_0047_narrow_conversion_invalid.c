// (Test) Compiler flags: -lm
// (Test) Status: 7
// bug_0047. A floating value converted to an integer type out of that type's
// range should raise invalid. To a type narrower than the form the compiler
// converts in, or to an unsigned one, it raises nothing, as gcc's and clang's
// raise nothing: the status counts the seven conversions here that raise none.
// [C99:6.3.1.4p1]: a floating value converted to an integer, truncated toward zero
// [C99:F.4p1]:     infinite, NaN or out of range, invalid

#include <fenv.h>

#pragma STDC FENV_ACCESS ON

static volatile float f256 = 256.0f;
static volatile double d128 = 128.0;
static volatile double dminus = -1.0;
static volatile double d2to32 = 4294967296.0;
static volatile long double l128 = 128.0L;
static volatile long double l65536 = 65536.0L;
static volatile signed char sc;
static volatile unsigned char uc;
static volatile unsigned short us;
static volatile unsigned int ui;
static volatile unsigned long ul;

int main(void)
{
    int missed = 0;

    feclearexcept(FE_ALL_EXCEPT);
    uc = (unsigned char) f256;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    sc = (signed char) d128;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    ui = (unsigned int) dminus;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    ui = (unsigned int) d2to32;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    ul = (unsigned long) dminus;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    sc = (signed char) l128;
    missed += ! fetestexcept(FE_INVALID);
    feclearexcept(FE_ALL_EXCEPT);
    us = (unsigned short) l65536;
    missed += ! fetestexcept(FE_INVALID);
    return missed;
}
