// (Test) Status: 200
// Conversions to and from complex types. A real value gains a zero imaginary
// part, a complex value converted to a real type loses its imaginary part, and
// between complex types each part converts as its real type does. A complex
// value is a scalar, true when either part is nonzero.

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

double _Complex gd = 2.5;
float _Complex gf = (float _Complex) 0.1;
long double _Complex gl = 1;
int gi = (int) (double _Complex) 7.5;
_Bool gb = (_Bool) (double _Complex) 0.5;
_Bool gz = (_Bool) (float _Complex) 0;

// A real value converted to a complex type takes a +0 imaginary part.
// [C99:6.3.1.7p1]: a real value converted to complex, a zero imaginary part
int check_from_real(void)
{
    double d = 2.5;
    double _Complex z = d;
    float _Complex fz = 3;
    double _Complex near = 0.1L;
    unsigned long big = 18000000000000000000UL;
    long double _Complex lz = big;

    if (REAL(z, double) != 2.5 || IMAG(z, double) != 0) return 1;
    if (1 / IMAG(z, double) < 0) return 2;
    if (REAL(fz, float) != 3.0f || IMAG(fz, float) != 0) return 3;
    if (REAL(near, double) != (double) 0.1L) return 4;
    if (REAL(lz, long double) != 18000000000000000000.0L) return 5;
    return 0;
}

// A complex value converted to a real type keeps its real part alone.
// [C99:6.3.1.7p2]: a complex value converted to real, its imaginary part discarded
int check_to_real(void)
{
    double _Complex z;
    double d;
    int i;
    long double l;
    unsigned long u;

    REAL(z, double) = 1.5;
    IMAG(z, double) = 9.0;
    d = z;
    i = z;
    l = z;
    if (d != 1.5 || i != 1 || l != 1.5L) return 11;
    REAL(z, double) = 1e19;
    u = z;
    if (u != 10000000000000000000UL) return 12;
    return 0;
}

// Between complex types each part converts as its real type does.
// [C99:6.3.1.6p1]: a complex value converted to another, each part as its real type's
int check_between(void)
{
    double _Complex z;
    float _Complex fz;
    long double _Complex lz;
    double _Complex back;

    REAL(z, double) = 0.1;
    IMAG(z, double) = -0.2;
    fz = z;
    lz = z;
    back = lz;
    if (REAL(fz, float) != (float) 0.1 || IMAG(fz, float) != (float) -0.2) return 21;
    if (REAL(lz, long double) != 0.1 || IMAG(lz, long double) != -0.2) return 22;
    if (REAL(back, double) != 0.1 || IMAG(back, double) != -0.2) return 23;
    return 0;
}

// A complex value converted to _Bool is 0 only when both parts are zero, and so
// is false in a condition.
// [C99:6.2.5p21]:  arithmetic types, scalar
// [C99:6.3.1.2p1]: a scalar converted to _Bool, 0 if it compares equal to 0
int check_truth(void)
{
    double _Complex z;
    long double _Complex lz;
    _Bool b;

    REAL(z, double) = 0;
    IMAG(z, double) = -0.0;
    b = z;
    if (b || z || ! (! z)) return 31;
    IMAG(z, double) = 1;
    b = z;
    if (! b || ! z || (z ? 0 : 1)) return 32;
    if (! (z && 1) || ! (0 || z)) return 33;
    REAL(lz, long double) = 0.0L / 0.0L;
    IMAG(lz, long double) = 0;
    if (! lz || (_Bool) lz != 1) return 34;
    while (0 && z) {
        return 35;
    }
    return 0;
}

// The usual arithmetic conversions give a complex type whose real type is the
// wider real type, and a conditional's result takes it.
// [C99:6.3.1.8p1]:  the usual arithmetic conversions
// [C99:6.5.15p5]:   a conditional's arithmetic result, after them
int check_common_type(void)
{
    float _Complex fz = 0;
    long double _Complex lz = 0;

    if (sizeof(1 ? fz : 1.0) != sizeof(double _Complex)) return 41;
    if (sizeof(1 ? 1 : fz) != sizeof(float _Complex)) return 42;
    if (sizeof(1 ? lz : fz) != sizeof(long double _Complex)) return 43;
    if (sizeof(1 ? 1.0f : lz) != sizeof(long double _Complex)) return 44;
    return 0;
}

// A file-scope complex object is filled in at compile time.
// [C99:6.6p8]: an arithmetic constant expression, casts between arithmetic types
int check_static(void)
{
    if (REAL(gd, double) != 2.5 || IMAG(gd, double) != 0) return 51;
    if (REAL(gf, float) != (float) 0.1 || IMAG(gf, float) != 0) return 52;
    if (REAL(gl, long double) != 1 || 1 / IMAG(gl, long double) < 0) return 53;
    if (gi != 7 || gb != 1 || gz != 0) return 54;
    return 0;
}

int main(void)
{
    int status = check_from_real();

    if (! status) {
        status = check_to_real();
    }
    if (! status) {
        status = check_between();
    }
    if (! status) {
        status = check_truth();
    }
    if (! status) {
        status = check_common_type();
    }
    if (! status) {
        status = check_static();
    }
    return status ? status : 200;
}
