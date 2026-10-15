// (Test) Compiler flags: -lm
// (Test) Status: 0
// (Test) Output:
// | cpow real 1
// | cpow complex 1
// Non-standard: cpow of 2 to 100 should be 2^100 exactly, and (1 + i) to 30
// should have the imaginary part -2^15 exactly, where glibc's, y clog(x)
// and its exponential computed in double, are 8 and 4 ulps off; computed in
// long double, the product's error is lost in the rounding to double.
// Liberty: the accuracy of <complex.h> is implementation-defined, and cpow
// may be cexp(y clog(x)).
// [C99:5.2.4.2.2p5]: the accuracy of <complex.h>, implementation-defined
// [C99:G.6.4.1p1]:   cpow, footnote 327, cexp(c clog(z))

#include <complex.h>
#include <stdio.h>

// Make a complex value of its parts.
static double complex make_double(double x, double y)
{
    double part[2] = { x, y };

    return *(double complex *) part;
}

int main(void)
{
    double complex power = cpow(make_double(2, 0), make_double(100, 0));
    double complex turn = cpow(make_double(1, 1), make_double(30, 0));

    printf("cpow real %d\n", creal(power) == 0x1p100 && cimag(power) == 0);
    printf("cpow complex %d\n", cimag(turn) == -0x1p15);
    return 0;
}
