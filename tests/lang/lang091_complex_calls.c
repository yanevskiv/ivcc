// (Test) Status: 200
// Complex values as parameters and results of each type: alone, among
// integers and reals, past the registers, and through a function pointer.

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

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

// Swap the parts of a complex value of each type.
float _Complex swap_float(float _Complex z)
{
    return make_float(IMAG(z, float), REAL(z, float));
}

double _Complex swap_double(double _Complex z)
{
    return make_double(IMAG(z, double), REAL(z, double));
}

long double _Complex swap_ldouble(long double _Complex z)
{
    return make_ldouble(IMAG(z, long double), REAL(z, long double));
}

// Sum complex arguments of each type among integers and reals.
double _Complex sum_mixed(int n, float _Complex f, double x, long double _Complex l, double _Complex d, char c)
{
    return n + f + x + (double _Complex) l + d + c;
}

// Sum nine double complex arguments, more than the SSE registers hold.
double _Complex sum_nine(double _Complex a, double _Complex b, double _Complex c, double _Complex d, double _Complex e,
                         double _Complex f, double _Complex g, double _Complex h, double _Complex i)
{
    return a + b + c + d + e + f + g + h + i;
}

// A complex result of each type, its imaginary part as well as its real one.
// [C99:6.2.5p13]:  a complex type, an array of two of its real type
// [C99:6.8.6.4p3]: return, its value converted as if assigned
int check_results(void)
{
    float _Complex f = make_float(1.5f, -2);
    double _Complex d = make_double(0.25, 8);
    long double _Complex l = make_ldouble(-3, 0.5L);

    if (REAL(f, float) != 1.5f || IMAG(f, float) != -2) return 1;
    if (REAL(d, double) != 0.25 || IMAG(d, double) != 8) return 2;
    if (REAL(l, long double) != -3 || IMAG(l, long double) != 0.5L) return 3;
    if (make_double(1, 2) != make_double(1, 2) || make_double(1, 2) == make_double(1, 3)) return 4;
    return 0;
}

// A complex argument of each type arrives whole.
// [C99:6.5.2.2p7]: arguments converted as if assigned to the parameters
int check_arguments(void)
{
    float _Complex f = swap_float(make_float(1, 2));
    double _Complex d = swap_double(make_double(3, 4));
    long double _Complex l = swap_ldouble(make_ldouble(5, 6));

    if (f != make_float(2, 1)) return 11;
    if (d != make_double(4, 3)) return 12;
    if (l != make_ldouble(6, 5)) return 13;
    if (swap_double(swap_double(d)) != d || swap_double(make_float(1, 2)) != make_double(2, 1)) return 14;
    return 0;
}

// Complex arguments mixed with others, and more than the registers hold.
int check_mixed(void)
{
    double _Complex d = sum_mixed(1, make_float(2, 3), 4, make_ldouble(5, 6), make_double(7, 8), 9);
    double _Complex n = sum_nine(make_double(1, 1), make_double(2, 2), make_double(3, 3), make_double(4, 4), make_double(5, 5),
                                 make_double(6, 6), make_double(7, 7), make_double(8, 8), make_double(9, 9));

    if (d != make_double(28, 17)) return 21;
    if (n != make_double(45, 45)) return 22;
    return 0;
}

// A call through a pointer, its result used directly.
int check_pointer(void)
{
    long double _Complex (*swap)(long double _Complex) = swap_ldouble;
    double _Complex (*make)(double, double) = make_double;

    if (swap(make_ldouble(1, -1)) != make_ldouble(-1, 1)) return 31;
    if (IMAG(*&(double _Complex) { make(2, 7) }, double) != 7) return 32;
    if (make(1, 2) + make(3, 4) != make_double(4, 6)) return 33;
    return 0;
}

int main(void)
{
    int status = check_results();

    if (! status) {
        status = check_arguments();
    }
    if (! status) {
        status = check_mixed();
    }
    if (! status) {
        status = check_pointer();
    }
    return status ? status : 200;
}
