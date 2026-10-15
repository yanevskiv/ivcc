// (Test) Compiler flags: -lm
// (Test) Status: 200
// CX_LIMITED_RANGE ON is taken and ignored: * and / of complex values still
// call libgcc's helpers, which recover G.5.1's infinities and scale a
// quotient whose usual formula would overflow, as in its default state off.
// Liberty: the pragma allows the usual formulas and does not require them.
// [C99:7.3.4p2]:   CX_LIMITED_RANGE, on to allow the usual formulas, off by default
// [C99:G.5.1p4]:   * and /, an infinite operand giving an infinite or zero result

#pragma STDC CX_LIMITED_RANGE ON

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

// Make a complex value of its parts.
double _Complex make_double(double x, double y)
{
    double _Complex z;

    REAL(z, double) = x;
    IMAG(z, double) = y;
    return z;
}

// Return whether a value has an infinite part, the other perhaps a NaN.
int is_inf(double _Complex z)
{
    double x = REAL(z, double);
    double y = IMAG(z, double);

    return (x - x != 0 && x == x) || (y - y != 0 && y == y);
}

int main(void)
{
    double inf = 1e308 * 10;
    double nan = inf - inf;
    double _Complex big = make_double(1e300, 1e300);
    double _Complex quot = big / big;

    // The usual formula gives NaN + iNaN for each.
    if (! is_inf(make_double(inf, nan) * make_double(1, 1))) return 1;
    if (! is_inf(make_double(1, 1) / make_double(0, 0))) return 2;
    if (REAL(quot, double) != 1 || IMAG(quot, double) != 0) return 3;
    return 200;
}
