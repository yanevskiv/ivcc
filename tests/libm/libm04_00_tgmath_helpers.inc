// Includable helper file for <tgmath.h> tests.

// Includes.
#include <_test.h>
#include <stddef.h>
#include <stdbool.h>
#include <iso646.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>
#include <setjmp.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <math.h>
#include <fenv.h>
#include <complex.h>
#include <tgmath.h>

// Defines.
#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

// The type a macro's result has, by _Generic, C11's.
#define KIND(x) _Generic((x),                                                  \
    float: KIND_FLOAT, double: KIND_DOUBLE, long double: KIND_LDOUBLE,         \
    float _Complex: KIND_FLOAT_COMPLEX, double _Complex: KIND_DOUBLE_COMPLEX,  \
    long double _Complex: KIND_LDOUBLE_COMPLEX, default: KIND_OTHER)

// Whether two results of a type are the same value, NaNs alike.
#define SAME(a, b, T) same_##T((a), (b))

// The types a macro's result may have.
enum {
    KIND_FLOAT = 1,
    KIND_DOUBLE,
    KIND_LDOUBLE,
    KIND_FLOAT_COMPLEX,
    KIND_DOUBLE_COMPLEX,
    KIND_LDOUBLE_COMPLEX,
    KIND_OTHER
};

// Make a complex value of each type of its parts.
static float _Complex make_float(float x, float y)
{
    float _Complex z;

    REAL(z, float) = x;
    IMAG(z, float) = y;
    return z;
}

static double _Complex make_double(double x, double y)
{
    double _Complex z;

    REAL(z, double) = x;
    IMAG(z, double) = y;
    return z;
}

static long double _Complex make_ldouble(long double x, long double y)
{
    long double _Complex z;

    REAL(z, long double) = x;
    IMAG(z, long double) = y;
    return z;
}

// Return whether two values of each type are the same, NaNs alike.
static bool same_float(float a, float b)
{
    return a == b || (a != a && b != b);
}

static bool same_double(double a, double b)
{
    return a == b || (a != a && b != b);
}

static bool same_ldouble(long double a, long double b)
{
    return a == b || (a != a && b != b);
}

static bool same_cfloat(float _Complex a, float _Complex b)
{
    return same_float(REAL(a, float), REAL(b, float)) && same_float(IMAG(a, float), IMAG(b, float));
}

static bool same_cdouble(double _Complex a, double _Complex b)
{
    return same_double(REAL(a, double), REAL(b, double)) && same_double(IMAG(a, double), IMAG(b, double));
}

static bool same_cldouble(long double _Complex a, long double _Complex b)
{
    return same_ldouble(REAL(a, long double), REAL(b, long double)) && same_ldouble(IMAG(a, long double), IMAG(b, long double));
}
