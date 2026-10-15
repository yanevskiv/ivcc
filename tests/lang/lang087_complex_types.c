// (Test) Status: 200
// Complex types. `float`, `double` and `long double` take `_Complex` in any
// order, and each complex type is laid out as an array of two of its real
// type, the real part first, inside structs and arrays too.

typedef double _Complex dcomplex;

struct Holder {
    char                 tag;
    float _Complex       fz;
    long double _Complex lz;
    _Complex double      dz[2];
};

// The specifiers name the same type in any order, and a typedef names it too.
// [C99:6.7.2p2]: float _Complex, double _Complex and long double _Complex
int check_specifiers(void)
{
    _Complex float a;
    float _Complex *pa = &a;
    double _Complex b;
    _Complex double *pb = &b;
    dcomplex *pt = &b;
    long double _Complex c;
    long _Complex double *pc = &c;
    _Complex long double *pd = &c;
    const double _Complex k = 2.0;
    const _Complex double *pk = &k;

    if (pa != &a || pb != &b || pt != &b) return 1;
    if (pc != &c || pd != &c || pk != &k) return 2;
    return 0;
}

// Each complex type is two of its real type: its size, its alignment, and the
// real part first.
// [C99:6.2.5p11]: three complex types
// [C99:6.2.5p13]: the representation and alignment of an array of two, real part first
int check_layout(void)
{
    double parts[2] = { 3.0, 4.0 };
    double _Complex *z = (double _Complex *) parts;
    double _Complex copy = *z;
    double *back = (double *) &copy;

    if (sizeof(float _Complex) != 2 * sizeof(float)) return 11;
    if (sizeof(double _Complex) != 2 * sizeof(double)) return 12;
    if (sizeof(long double _Complex) != 2 * sizeof(long double)) return 13;
    if (_Alignof(float _Complex) != _Alignof(float)) return 14;
    if (_Alignof(double _Complex) != _Alignof(double)) return 15;
    if (_Alignof(long double _Complex) != _Alignof(long double)) return 16;
    if (back[0] != 3.0 || back[1] != 4.0) return 17;
    return 0;
}

// A complex member and a complex element sit where their alignment puts them.
// [C99:6.7.2.1p13]: members at increasing addresses
int check_members(void)
{
    struct Holder holder;
    long double *lz = (long double *) &holder.lz;
    double *dz = (double *) holder.dz;

    if (__builtin_offsetof(struct Holder, fz) != 4) return 21;
    if (__builtin_offsetof(struct Holder, lz) != 16) return 22;
    if (__builtin_offsetof(struct Holder, dz) != 48) return 23;
    if (sizeof(struct Holder) != 80) return 24;

    lz[0] = 1.5L;
    lz[1] = -2.5L;
    dz[2] = 6.0;
    dz[3] = 7.0;
    holder.dz[0] = holder.dz[1];
    if (lz[0] != 1.5L || lz[1] != -2.5L) return 25;
    if (dz[0] != 6.0 || dz[1] != 7.0) return 26;
    return 0;
}

int main(void)
{
    int status = check_specifiers();

    if (! status) {
        status = check_layout();
    }
    if (! status) {
        status = check_members();
    }
    return status ? status : 200;
}
