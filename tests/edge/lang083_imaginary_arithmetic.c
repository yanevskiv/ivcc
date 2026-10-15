// (Test) Compiler flags: -lm
// (Test) Status: 200
// gcc's imaginary constants in arithmetic: x + yi spells a complex constant,
// folded in a static initializer with sums, products and quotients of them.
// Non-standard: an imaginary floating constant, as gcc takes it.
// Liberty: an extension that no strictly conforming program can tell.
// [C99:4p6]:   extensions that alter no strictly conforming program
// [C99:6.6p7]: an initializer's arithmetic constant expressions

#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

double _Complex gsum = 1.0 + 2.0i;
double _Complex gdiff = 1.0 - 2.0i;
float _Complex gprod = (1.0f + 2.0if) * (3.0f + 4.0if);
long double _Complex gquot = (-5.0L + 10.0iL) / (3.0L + 4.0iL);
double _Complex greal = 2.0 / (1.0 + 1.0i);
double _Complex gscale = 0.5i * 4 - 1;

// Each static initializer folds to the parts the formula gives.
int check_static(void)
{
    if (REAL(gsum, double) != 1 || IMAG(gsum, double) != 2) return 1;
    if (REAL(gdiff, double) != 1 || IMAG(gdiff, double) != -2) return 2;
    if (REAL(gprod, float) != -5 || IMAG(gprod, float) != 10) return 3;
    if (REAL(gquot, long double) != 1 || IMAG(gquot, long double) != 2) return 4;
    if (REAL(greal, double) != 1 || IMAG(greal, double) != -1) return 5;
    if (REAL(gscale, double) != -1 || IMAG(gscale, double) != 2) return 6;
    return 0;
}

// The same expressions in a block give the same values at run time.
int check_block(void)
{
    double _Complex sum = 1.0 + 2.0i;
    float _Complex prod = (1.0f + 2.0if) * (3.0f + 4.0if);
    long double _Complex quot = (-5.0L + 10.0iL) / (3.0L + 4.0iL);
    double _Complex unit = 1.0i * 1.0i;

    if (sum != gsum || prod != gprod || quot != gquot) return 11;
    if (REAL(unit, double) != -1 || IMAG(unit, double) != 0) return 12;
    if (2.0 / (1.0 + 1.0i) != greal) return 13;
    return 0;
}

int main(void)
{
    int status = check_static();

    if (! status) {
        status = check_block();
    }
    return status ? status : 200;
}
