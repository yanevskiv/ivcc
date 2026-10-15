// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <complex.h> cabs.

// Include helpers.
#include "libm03_00_complex_helpers.inc"

// cabs should be the hypotenuse of the parts, hypot's value bit for bit,
// so an infinite part gives +inf even beside a NaN, in each type.
// [C99:7.3.8.1p2]: cabs, the complex absolute value
// [C99:G.6p6]:     cabs(x + iy) as hypot(x, y)
// [C99:F.9.4.3p1]: hypot of a zero, and of an infinity even with a NaN
static void Test_ComplexCabs(void)
{
    static const double parts[][2] = {
        { 3, 4 }, { -3, -4 }, { 1, 1 }, { 0.1, -7 }, { -0.0, -0.0 }, { -5, 0 },
        { DBL_MAX, DBL_MAX }, { DBL_MIN, 0x1p-1074 }, { NAN, 1 }, { 1, NAN },
    };

    for (size_t k = 0; k < sizeof(parts) / sizeof(parts[0]); k++) {
        double x = parts[k][0];
        double y = parts[k][1];
        double got = cabs(make_double(x, y));
        float gotf = cabsf(make_float((float) x, (float) y));
        long double gotl = cabsl(make_ldouble(x, y));

        _TEST_TRUE(memcmp(&got, &(double) { hypot(x, y) }, sizeof(got)) == 0);
        _TEST_TRUE(memcmp(&gotf, &(float) { hypotf((float) x, (float) y) }, sizeof(gotf)) == 0);
        _TEST_TRUE(gotl == hypotl(x, y) || (isnan(gotl) && isnan(hypotl(x, y))));
    }
    _TEST_FLOAT(cabs(make_double(3, 4)), 5);
    _TEST_FLOAT(cabsf(make_float(-3, 4)), 5);
    _TEST_FLOAT(cabsl(make_ldouble(3, -4)), 5);
    _TEST_FLOAT(cabs(make_double(-2.5, 0)), 2.5);
    _TEST_TRUE(cabs(make_double(-0.0, -0.0)) == 0 && ! signbit(cabs(make_double(-0.0, -0.0))));
    _TEST_FLOAT(cabs(make_double(NAN, -INFINITY)), INFINITY);
    _TEST_FLOAT(cabsf(make_float(-INFINITY, NAN)), INFINITY);
    _TEST_FLOAT(cabsl(make_ldouble(NAN, INFINITY)), INFINITY);
    _TEST_TRUE(isnan(cabs(make_double(NAN, 2))));
}

int main(void)
{
    Test_ComplexCabs();
    return _Test_Status();
}
