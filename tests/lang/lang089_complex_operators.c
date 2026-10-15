// (Test) Status: 200
// Operators on complex values that need no complex arithmetic: == and !=,
// unary + and -, casts, assignment, and members and elements of complex type.

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

struct Pair {
    int            tag;
    double _Complex z;
};

long double _Complex gn = -(long double _Complex) 1;
double _Complex gm = -(double _Complex) (float _Complex) 0.5;

// Complex values are equal when both their real and their imaginary parts are,
// after the usual arithmetic conversions bring the operands to one type.
// [C99:6.3.1.8p1]: the usual arithmetic conversions
// [C99:6.5.9p4]:   complex values equal when both their parts are
int check_equality(void)
{
    double _Complex a;
    double _Complex b;
    float _Complex fz;
    long double _Complex lz;

    REAL(a, double) = 1;
    IMAG(a, double) = 2;
    b = a;
    if (! (a == b) || a != b) return 1;
    IMAG(b, double) = 3;
    if (a == b || ! (a != b)) return 2;
    REAL(b, double) = 1;
    IMAG(b, double) = 0;
    if (b != 1 || 1.0 != b || b == 2) return 3;
    IMAG(b, double) = -0.0;
    if (b != 1.0f) return 4;
    REAL(fz, float) = 0.1f;
    IMAG(fz, float) = 0;
    if (fz == 0.1 || fz != 0.1f) return 5;
    REAL(lz, long double) = 0.1f;
    IMAG(lz, long double) = 0;
    if (lz != fz || fz != lz) return 6;
    IMAG(lz, long double) = 0.0L / 0.0L;
    if (lz == lz || ! (lz != lz)) return 7;
    return 0;
}

// Unary minus negates both parts, a zero part to a zero of the other sign, and
// unary plus leaves the value alone.
// [C99:6.5.3.3p2]: unary +, the value of its operand
// [C99:6.5.3.3p3]: unary -, the negative of its operand
int check_unary(void)
{
    double _Complex z;
    double _Complex n;
    float _Complex fz;
    long double _Complex lz;

    REAL(z, double) = 1.5;
    IMAG(z, double) = 0;
    n = -z;
    if (REAL(n, double) != -1.5 || IMAG(n, double) != 0 || 1 / IMAG(n, double) > 0) return 11;
    n = +z;
    if (n != z) return 12;
    if (-(-z) != z) return 13;
    REAL(fz, float) = -2;
    IMAG(fz, float) = 4;
    fz = -fz;
    if (REAL(fz, float) != 2 || IMAG(fz, float) != -4) return 14;
    REAL(lz, long double) = 0;
    IMAG(lz, long double) = -0.25L;
    lz = -lz;
    if (1 / REAL(lz, long double) > 0 || IMAG(lz, long double) != 0.25L) return 15;
    if (REAL(gn, long double) != -1 || 1 / IMAG(gn, long double) > 0) return 16;
    if (REAL(gm, double) != -0.5 || 1 / IMAG(gm, double) > 0) return 17;
    return 0;
}

// A cast converts to a complex type or from one, a cast to void evaluates.
// [C99:6.5.4p2]: a cast, scalar to scalar or anything to void
int check_casts(void)
{
    double _Complex z;
    int calls = 0;

    REAL(z, double) = 2.75;
    IMAG(z, double) = -1;
    if ((int) z != 2 || (float) z != 2.75f || (long double) z != 2.75L) return 21;
    if ((_Bool) z != 1 || (char) (float _Complex) z != 2) return 22;
    if ((double _Complex) (float _Complex) z != z) return 23;
    if ((long double _Complex) 3 != 3.0) return 24;
    (void) (calls++, z);
    if (calls != 1) return 25;
    return 0;
}

// A complex value assigns whole, into a member, an element or a compound
// literal, and a conditional or a comma yields it.
// [C99:6.5.15p5]:   a conditional's arithmetic result
// [C99:6.5.16.1p1]: simple assignment between arithmetic types
// [C99:6.5.17p2]:   a comma's value, its right operand's
int check_assignment(void)
{
    struct Pair pair;
    struct Pair copy;
    long double _Complex arr[3];
    double _Complex *lit = &(double _Complex) { 4.0 };
    double _Complex z;
    long double _Complex lz;

    REAL(z, double) = 5;
    IMAG(z, double) = 6;
    pair.tag = 1;
    pair.z = z;
    copy = pair;
    if (copy.z != z || copy.tag != 1) return 31;
    arr[0] = z;
    arr[2] = arr[0];
    arr[1] = 1;
    if (arr[2] != z || arr[1] != 1.0L) return 32;
    *lit = arr[2];
    if (*lit != z) return 33;
    lz = (copy.tag ? z : 0);
    if (lz != z) return 34;
    lz = (copy.tag, 7);
    if (lz != 7) return 35;
    z = lz = arr[0];
    if (z != arr[2]) return 36;
    return 0;
}

int main(void)
{
    int status = check_equality();

    if (! status) {
        status = check_unary();
    }
    if (! status) {
        status = check_casts();
    }
    if (! status) {
        status = check_assignment();
    }
    return status ? status : 200;
}
