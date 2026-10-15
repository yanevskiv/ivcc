// (Test) Compiler flags: -lm
// (Test) Status: 0
// bug_0049. clogl raised underflow where the smaller part over the larger is
// below 2^-16382, though ln |z| and the angle are not tiny: the ratio, taken
// to decide whether the smaller part's share of ln |z| is lost, underflowed.
// Each angle here is near pi/2 or pi; the status counts the calls that raise
// it.
// [C99:7.3.7.2]: clog, in [-ipi, +ipi]
// [C99:F.9p7]:   underflow, only where the result is tiny

#include <complex.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

static volatile long double sink;

// Make a long double complex value of its parts.
static long double complex make_ldouble(long double x, long double y)
{
    long double part[2] = { x, y };

    return *(long double complex *) part;
}

// Count whether clogl of x + iy raised underflow, clearing the flags.
static int raised(long double x, long double y)
{
    int flag;

    feclearexcept(FE_ALL_EXCEPT);
    sink = creall(clogl(make_ldouble(x, y)));
    flag = fetestexcept(FE_UNDERFLOW) != 0;
    feclearexcept(FE_ALL_EXCEPT);
    return flag;
}

int main(void)
{
    int count = 0;

    count += raised(-0x1.8p-11000L, 0x1.8p6000L);
    count += raised(-0x1.8p6000L, -0x1.8p-11000L);
    count += raised(0x1p-16440L, 0.3L);
    count += raised(-0.3L, 0x1p-16440L);
    return count;
}
