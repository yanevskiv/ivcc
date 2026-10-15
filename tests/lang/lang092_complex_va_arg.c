// (Test) Status: 200
// va_arg of each complex type: from the registers and past them, a complex
// double the last SSE register cannot hold, and as a member of a struct.

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

struct pair {
    float _Complex a;
    float _Complex b;
};

struct tagged {
    int i;
    float _Complex f;
};

// Make a complex value of each type of its parts.
float _Complex make_float(float x, float y)
{
    float _Complex z;

    REAL(z, float) = x;
    IMAG(z, float) = y;
    return z;
}

double _Complex make_double(double x, double y)
{
    double _Complex z;

    REAL(z, double) = x;
    IMAG(z, double) = y;
    return z;
}

long double _Complex make_ldouble(long double x, long double y)
{
    long double _Complex z;

    REAL(z, long double) = x;
    IMAG(z, long double) = y;
    return z;
}

// Return the index of the first argument that is not (k, -k) in its kind:
// f float, d double, l long double complex, r double, i int; or -1.
int first_wrong(const char *kinds, ...)
{
    __builtin_va_list ap;
    int k;

    __builtin_va_start(ap, kinds);
    for (k = 0; kinds[k]; k++) {
        int ok = 0;

        if (kinds[k] == 'f') {
            ok = __builtin_va_arg(ap, float _Complex) == make_float(k, -k);
        } else if (kinds[k] == 'd') {
            ok = __builtin_va_arg(ap, double _Complex) == make_double(k, -k);
        } else if (kinds[k] == 'l') {
            ok = __builtin_va_arg(ap, long double _Complex) == make_ldouble(k, -k);
        } else if (kinds[k] == 'r') {
            ok = __builtin_va_arg(ap, double) == k;
        } else if (kinds[k] == 'i') {
            ok = __builtin_va_arg(ap, int) == k;
        }
        if (! ok) {
            break;
        }
    }
    __builtin_va_end(ap);
    return kinds[k] ? k : -1;
}

// Sum the n structs with complex members that follow.
double _Complex sum_structs(int n, ...)
{
    __builtin_va_list ap;
    double _Complex sum = 0;

    __builtin_va_start(ap, n);
    for (int k = 0; k < n; k++) {
        struct pair p = __builtin_va_arg(ap, struct pair);
        struct tagged t = __builtin_va_arg(ap, struct tagged);

        sum += p.a + p.b + t.f + t.i;
    }
    __builtin_va_end(ap);
    return sum;
}

// Each type alone and mixed, from the save area.
// [C99:7.15.1.1p2]: va_arg, the next argument's value in its type
// [Amd64-SysV:3.5.7]: va_arg, by the classes of the argument
int check_registers(void)
{
    if (first_wrong("fdl", make_float(0, 0), make_double(1, -1), make_ldouble(2, -2)) != -1) return 1;
    if (first_wrong("ifrdil", 0, make_float(1, -1), 2.0, make_double(3, -3), 4, make_ldouble(5, -5)) != -1) return 2;
    return 0;
}

// Past the registers: the overflow area, and a complex double with one SSE
// register left, which goes to the stack while the double after it does not.
int check_overflow(void)
{
    if (first_wrong("ffffffffffdd", make_float(0, 0), make_float(1, -1), make_float(2, -2), make_float(3, -3), make_float(4, -4),
                    make_float(5, -5), make_float(6, -6), make_float(7, -7), make_float(8, -8), make_float(9, -9),
                    make_double(10, -10), make_double(11, -11)) != -1) return 11;
    if (first_wrong("rrrrrrrdrf", 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, make_double(7, -7), 8.0, make_float(9, -9)) != -1) return 12;
    if (first_wrong("dldldl", make_double(0, 0), make_ldouble(1, -1), make_double(2, -2), make_ldouble(3, -3), make_double(4, -4),
                    make_ldouble(5, -5)) != -1) return 13;
    return 0;
}

// Structs with complex members, in SSE and integer registers and past them.
int check_structs(void)
{
    struct pair p = { make_float(1, 2), make_float(3, 4) };
    struct tagged t = { 5, make_float(6, 7) };

    if (sum_structs(1, p, t) != make_double(15, 13)) return 21;
    if (sum_structs(4, p, t, p, t, p, t, p, t) != make_double(60, 52)) return 22;
    return 0;
}

int main(void)
{
    int status = check_registers();

    if (! status) {
        status = check_overflow();
    }
    if (! status) {
        status = check_structs();
    }
    return status ? status : 200;
}
