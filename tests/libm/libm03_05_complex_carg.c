// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> carg.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

// carg should be the arc tangent of the imaginary part by the real one,
// atan2's value bit for bit, in [-pi, +pi], the sign of a zero imaginary
// part choosing the side of the cut along the negative real axis.
// [C99:7.3.3p1]:   a branch cut's sides, by the sign of zero
// [C99:7.3.9.1p2]: carg, a branch cut along the negative real axis
// [C99:7.3.9.1p3]: carg, in [-pi, +pi]
// [C99:G.6p6]:     carg(x + iy) as atan2(y, x)
// [C99:F.9.1.4p1]: atan2 of zeros and infinities, footnote 322
static void Test_ComplexCarg(void)
{
    static const double parts[][2] = {
        { 1, 1 }, { -1, 1 }, { -1, -1 }, { 0.5, -3 }, { -2, 0 }, { -2, -0.0 }, { 0, 0 }, { -0.0, 0 },
        { 0, -0.0 }, { -0.0, -0.0 }, { INFINITY, 1 }, { -INFINITY, -1 }, { INFINITY, -INFINITY }, { NAN, 1 },
    };
    double pi = atan2(0, -1);

    for (size_t k = 0; k < sizeof(parts) / sizeof(parts[0]); k++) {
        double x = parts[k][0];
        double y = parts[k][1];
        double got = carg(make_double(x, y));
        float gotf = cargf(make_float((float) x, (float) y));
        long double gotl = cargl(make_ldouble(x, y));

        _TEST_TRUE(memcmp(&got, &(double) { atan2(y, x) }, sizeof(got)) == 0);
        _TEST_TRUE(memcmp(&gotf, &(float) { atan2f((float) y, (float) x) }, sizeof(gotf)) == 0);
        _TEST_TRUE(gotl == atan2l(y, x) || (isnan(gotl) && isnan(atan2l(y, x))));
        _TEST_TRUE(isnan(got) || (got >= -pi && got <= pi));
    }
    _TEST_FLOAT(carg(make_double(-2, 0)), pi);
    _TEST_FLOAT(carg(make_double(-2, -0.0)), -pi);
    _TEST_TRUE(carg(make_double(3, -0.0)) == 0 && signbit(carg(make_double(3, -0.0))));
    _TEST_FLOAT(cargf(make_float(-1, 0)), (float) pi);
    _TEST_FLOAT(cargl(make_ldouble(-1, -0.0L)), -atan2l(0, -1));
}

int main(void)
{
    Test_ComplexCarg();
    return _Test_Status();
}
