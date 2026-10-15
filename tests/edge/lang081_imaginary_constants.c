// (Test) Status: 200
// gcc's imaginary constants: a floating constant ending in i, I, j or J, before
// or after its f, F, l or L, has the complex type of its real type and the
// value (+0, v), at file scope and in a block.
// Non-standard: an imaginary floating constant, as gcc takes it.
// Liberty: an extension that no strictly conforming program can tell.
// [C99:4p6]:       extensions that alter no strictly conforming program
// [C99:6.4.4.2p1]: f, l, F and L, the floating suffixes

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

double _Complex gd = 2.0i;
float _Complex gf = 1.5fi;
long double _Complex gl = 3.0Li;
double _Complex gn = -2.0j;
double _Complex gh = 0x1p3I;

// Every spelling of the suffix gives the type its letters ask for.
int check_types(void)
{
    if (sizeof(2.0i) != sizeof(double _Complex)) return 1;
    if (sizeof(2.0if) != sizeof(float _Complex)) return 2;
    if (sizeof(2.0Fi) != sizeof(float _Complex)) return 3;
    if (sizeof(2.0iL) != sizeof(long double _Complex)) return 4;
    if (sizeof(2.0lJ) != sizeof(long double _Complex)) return 5;
    if (sizeof(2e3j) != sizeof(double _Complex)) return 6;
    if (sizeof(.5I) != sizeof(double _Complex)) return 7;
    return 0;
}

// An imaginary constant is (+0, v), and its negation (-0, -v).
int check_values(void)
{
    double _Complex z = 2.5i;
    long double _Complex lz = -0x1.8p1Li;
    float _Complex fz = 0.1fi;

    if (REAL(z, double) != 0 || 1 / REAL(z, double) < 0 || IMAG(z, double) != 2.5) return 11;
    if (1 / REAL(lz, long double) > 0 || IMAG(lz, long double) != -3) return 12;
    if (REAL(fz, float) != 0 || IMAG(fz, float) != 0.1f) return 13;
    if (2.0i != 2.0i || 2.0i == 2.0 || 2.0i == -2.0i) return 14;
    if (! 1e-300i || (_Bool) 0.0i) return 15;
    return 0;
}

// File-scope imaginary constants are folded part by part.
int check_static(void)
{
    if (REAL(gd, double) != 0 || IMAG(gd, double) != 2) return 21;
    if (REAL(gf, float) != 0 || IMAG(gf, float) != 1.5f) return 22;
    if (REAL(gl, long double) != 0 || IMAG(gl, long double) != 3) return 23;
    if (1 / REAL(gn, double) > 0 || IMAG(gn, double) != -2) return 24;
    if (IMAG(gh, double) != 8) return 25;
    return 0;
}

int main(void)
{
    int status = check_types();

    if (! status) {
        status = check_values();
    }
    if (! status) {
        status = check_static();
    }
    return status ? status : 200;
}
