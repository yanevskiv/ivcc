// (Test) Compiler flags: -lm
// (Test) Status: 0
// bug_0048. atanl and atan2l raised underflow where the smaller part over the
// larger is below 2^-5461, though the result is near 0, pi/2 or pi and not
// tiny: the cube of that ratio in the arc tangent's series underflowed, and
// below 2^-16382 the ratio itself. The status counts the calls that raise it.
// [C99:7.12.4.3]: atan, in [-pi/2, +pi/2]
// [C99:7.12.4.4]: atan2, in [-pi, +pi]
// [C99:F.9p7]:    underflow, only where the result is tiny

#include <fenv.h>
#include <math.h>

#pragma STDC FENV_ACCESS ON

static volatile long double one = 1.0L;
static volatile long double huge = 0x1p6000L;
static volatile long double small = 0x1p-6000L;
static volatile long double wide = 0x1.8p6000L;
static volatile long double narrow = 0x1.8p-11000L;
static volatile long double least = 0x1p-16440L;
static volatile long double low = 0x1.23456789abcdefp-16360L;
static volatile long double sink;

// Count whether the call that gave result raised underflow, clearing the flags.
static int raised(long double result)
{
    int flag = fetestexcept(FE_UNDERFLOW) != 0;

    sink = result;
    feclearexcept(FE_ALL_EXCEPT);
    return flag;
}

int main(void)
{
    int count = 0;

    feclearexcept(FE_ALL_EXCEPT);
    count += raised(atanl(huge));
    count += raised(atanl(-huge));
    count += raised(atan2l(one, small));
    count += raised(atan2l(small, -one));
    count += raised(atan2l(wide, narrow));
    count += raised(atan2l(least, low));
    return count;
}
