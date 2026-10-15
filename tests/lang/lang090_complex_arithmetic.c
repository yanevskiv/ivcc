// (Test) Compiler flags: -lm
// (Test) Status: 200
// Complex arithmetic: + and - part by part, * and / by a real operand part by
// part, * and / of two complex operands by the library's helpers, the
// compound assignments, and a real operand kept real.

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

double _Complex gz = (double _Complex) 3 * 2 + 1;
float _Complex gf = (float _Complex) 6 / 4;

// Make a double complex value of its parts.
double _Complex make(double x, double y)
{
    double _Complex z;

    REAL(z, double) = x;
    IMAG(z, double) = y;
    return z;
}

// Return whether z has the parts x and y, a zero's sign counted.
int has(double _Complex z, double x, double y)
{
    if (REAL(z, double) != x || IMAG(z, double) != y) {
        return 0;
    }
    return 1 / REAL(z, double) == 1 / x && 1 / IMAG(z, double) == 1 / y;
}

// + and - add or subtract the parts, and a real operand's missing imaginary
// part leaves the other's, negated by - when the real operand is the left.
// [C99:6.3.1.8p1]: the usual arithmetic conversions, each operand keeping its type domain
// [C99:G.5.2p2]:   + and -, by the usual mathematical formula
int check_additive(void)
{
    double _Complex z = make(3, 4);
    double _Complex w = make(1, -1);
    double _Complex zero = make(1, 0);
    double x = 2;

    if (! has(z + w, 4, 3) || ! has(z - w, 2, 5)) return 1;
    if (! has(x + z, 5, 4) || ! has(z + x, 5, 4)) return 2;
    if (! has(x - z, -1, -4) || ! has(z - x, 1, 4)) return 3;
    if (! has(1 - zero, 0, -0.0)) return 4;
    if (! has(zero - 1, 0, 0) || ! has(-0.0 + make(0, -0.0), 0, -0.0)) return 5;
    if (! has(z + 1, 4, 4) || ! has(2.5f - z, -0.5, -4)) return 6;
    return 0;
}

// * and / by a real operand scale each part, a zero part keeping its sign
// where a complex multiplication would add +0 to it.
// [C99:G.5.1p2]: * of a real and a complex operand, each part times the real one
// [C99:G.5.1p3]: / by a real operand, each part divided by it
int check_real_factor(void)
{
    double _Complex z = make(3, 0);
    double _Complex w = make(1.5, -2);

    if (! has(2 * w, 3, -4) || ! has(w * 2, 3, -4)) return 11;
    if (! has(w / 2, 0.75, -1) || ! has(w / 0.5f, 3, -4)) return 12;
    if (! has(-1.0 * z, -3, -0.0) || ! has(z * -1.0, -3, -0.0)) return 13;
    if (! has(z / -1.0, -3, -0.0)) return 14;
    if (! has(gz, 7, 0) || REAL(gf, float) != 1.5f || IMAG(gf, float) != 0) return 15;
    return 0;
}

// * and / of two complex operands follow the usual formula where it is exact,
// in each of the three types, and / by a complex operand takes a real one too.
// [C99:6.5.5p4]: *, the product, and /, the quotient
// [C99:G.5.1p3]: / by a complex operand, complex division
int check_complex_factor(void)
{
    double _Complex z = make(1, 2);
    double _Complex w = make(3, 4);
    float _Complex fz;
    long double _Complex lz;
    long double _Complex lw;

    if (! has(z * w, -5, 10) || ! has(w * z, -5, 10)) return 21;
    if (! has(make(-5, 10) / w, 1, 2) || ! has(make(-5, 10) / z, 3, 4)) return 22;
    if (! has(10 / make(1, 2), 2, -4) || ! has(z / make(0, 1), 2, -1)) return 23;
    REAL(fz, float) = 1.5f;
    IMAG(fz, float) = 2.5f;
    fz = fz * fz;
    if (REAL(fz, float) != -4 || IMAG(fz, float) != 7.5f) return 24;
    fz = fz / (float _Complex) 2;
    if (REAL(fz, float) != -2 || IMAG(fz, float) != 3.75f) return 25;
    REAL(lz, long double) = 1.25L;
    IMAG(lz, long double) = 3;
    lw = lz * lz;
    if (REAL(lw, long double) != -7.4375L || IMAG(lw, long double) != 7.5L) return 26;
    lw = lw / (long double _Complex) 2;
    if (REAL(lw, long double) != -3.71875L || IMAG(lw, long double) != 3.75L) return 27;
    return 0;
}

// A compound assignment computes as its binary operator, a real left operand
// taking the result's real part.
// [C99:6.5.16.2p3]: E1 op= E2, as E1 = E1 op (E2), E1 evaluated once
// [C99:6.3.1.7p2]:  a complex value converted to real, its imaginary part discarded
int check_compound(void)
{
    double _Complex z = make(3, 4);
    double _Complex arr[2];
    double x = 1;
    int i = 0;

    z += 1;
    if (! has(z, 4, 4)) return 31;
    z -= make(0, 4);
    if (! has(z, 4, 0)) return 32;
    z *= make(1, 1);
    if (! has(z, 4, 4)) return 33;
    z /= make(1, 1);
    if (! has(z, 4, 0)) return 34;
    z /= 2;
    if (! has(z, 2, 0)) return 35;
    x += make(2, 5);
    if (x != 3) return 36;
    x *= make(2, 5);
    if (x != 6) return 37;
    arr[0] = make(1, 1);
    arr[1] = make(2, 2);
    arr[i++] *= arr[1];
    if (i != 1 || ! has(arr[0], 0, 4)) return 38;
    return 0;
}

// The usual arithmetic conversions bring both operands to the wider real
// type, and an integer operand to the complex operand's real type.
// [C99:6.3.1.8p1]: the usual arithmetic conversions, each operand keeping its type domain
int check_mixed(void)
{
    float _Complex fz;
    long double _Complex lz;
    double _Complex z = make(0.5, 0.25);

    REAL(fz, float) = 1.5f;
    IMAG(fz, float) = 0.5f;
    if (sizeof(fz + z) != sizeof(double _Complex)) return 41;
    if (sizeof(fz * 1.0L) != sizeof(long double _Complex)) return 42;
    if (sizeof(3 * fz) != sizeof(float _Complex)) return 43;
    if (! has(fz + z, 2, 0.75) || ! has(fz * z, 0.625, 0.625)) return 44;
    lz = fz * 2.0L;
    if (REAL(lz, long double) != 3 || IMAG(lz, long double) != 1) return 45;
    if (! has(z * 4u, 2, 1) || ! has(-3LL * z, -1.5, -0.75)) return 46;
    return 0;
}

int main(void)
{
    int status = check_additive();

    if (! status) {
        status = check_real_factor();
    }
    if (! status) {
        status = check_complex_factor();
    }
    if (! status) {
        status = check_compound();
    }
    if (! status) {
        status = check_mixed();
    }
    return status ? status : 200;
}
