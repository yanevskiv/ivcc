// (Test) Compiler flags: -lm
// (Test) Status: 0
// (Test) Output:
// | near 0x1.9p-10 0x2p-10 -0x1.9p-10 0x1.4p+1 0x1p+1
// | up 0x1.9p-10 0x2p-10 -0x1.8p-10 0x1.4p+1 0x2p+1
// | down 0x1.8p-10 0x1p-10 -0x1.9p-10 0x1.4p+1 0x1p+1
// | zero 0x1.8p-10 0x1p-10 -0x1.8p-10 0x1.4p+1 0x1p+1
// | up 0xc.49cp-13 -0xc.49bp-13
// Non-standard: %a and %A should round a value their precision cuts in the
// current direction, a tie to nearest by its even digit, as glibc.
// Liberty: C99 says how they round only where FLT_RADIX is not a power of 2.
// [C99:7.19.6.1p8]:  a and A, as many digits after the point as the precision
// [C99:7.19.6.1p12]: a and A, rounded in the direction for another radix

#include <fenv.h>
#include <stdio.h>

#pragma STDC FENV_ACCESS ON

// Show %a of some values cut short, in one direction.
static void show(const char *name, int round)
{
    fesetround(round);
    printf("%s %.1a %.0a %.1a %.1a %.0a\n", name, 0.0015, 0.0015, -0.0015, 2.5, 2.5);
}

int main(void)
{
    show("near", FE_TONEAREST);
    show("up", FE_UPWARD);
    show("down", FE_DOWNWARD);
    show("zero", FE_TOWARDZERO);
    fesetround(FE_UPWARD);
    printf("up %.3La %.3La\n", (long double) 0.0015, (long double) -0.0015);
    fesetround(FE_TONEAREST);
    return 0;
}
