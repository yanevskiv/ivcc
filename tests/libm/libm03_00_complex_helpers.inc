// Includable helper file for <complex.h> tests.

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

// Defines.
#define REAL(z, T) (((T *) &(z))[0])
#define IMAG(z, T) (((T *) &(z))[1])

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

// Return whether a complex value of each type is an infinity, a part of it
// infinite, the other perhaps a NaN.
static bool is_inf_float(float _Complex z)
{
    return isinf(REAL(z, float)) || isinf(IMAG(z, float));
}

static bool is_inf_double(double _Complex z)
{
    return isinf(REAL(z, double)) || isinf(IMAG(z, double));
}

static bool is_inf_ldouble(long double _Complex z)
{
    return isinf(REAL(z, long double)) || isinf(IMAG(z, long double));
}

// Return whether a complex value of each type is a zero, both its parts.
static bool is_zero_float(float _Complex z)
{
    return REAL(z, float) == 0 && IMAG(z, float) == 0;
}

static bool is_zero_double(double _Complex z)
{
    return REAL(z, double) == 0 && IMAG(z, double) == 0;
}

static bool is_zero_ldouble(long double _Complex z)
{
    return REAL(z, long double) == 0 && IMAG(z, long double) == 0;
}

// Return whether a complex value of each type is NaN + iNaN, both its parts.
static bool is_nan_float(float _Complex z)
{
    return isnan(REAL(z, float)) && isnan(IMAG(z, float));
}

static bool is_nan_double(double _Complex z)
{
    return isnan(REAL(z, double)) && isnan(IMAG(z, double));
}

static bool is_nan_ldouble(long double _Complex z)
{
    return isnan(REAL(z, long double)) && isnan(IMAG(z, long double));
}

// Return whether got is within ulps units in the last place of want, in a
// type whose significand has digits bits.
static bool within_ulps(long double got, long double want, int digits, long double ulps)
{
    int exp;

    frexpl(want, &exp);
    return fabsl(got - want) <= ldexpl(ulps, exp - digits);
}
