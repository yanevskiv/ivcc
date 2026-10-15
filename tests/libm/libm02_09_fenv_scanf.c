// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> rounding directions in scanf's floating conversions.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"

// sscanf's %f, %lf and %Lf should convert as strtod does, in the current
// direction, a negative number by its own value.
// [C99:7.19.6.2p12]: a, e, f and g, a number of the form strtod expects
// [C99:7.20.1.3p9]:  a decimal of DECIMAL_DIG digits correctly rounded
// [C99:F.5p3]:       strtod honours the direction, never negating the value
static void Test_FenvScanf(void)
{
    float fgot = 0.0f;
    double got = 0.0;
    long double lgot = 0.0L;

    fesetround(FE_UPWARD);
    _TEST_INT(sscanf("0.1 -0.1", "%lf %f", &got, &fgot), 2);
    _TEST_FLOAT(got, 0x1.999999999999ap-4);
    _TEST_FLOAT(fgot, -0x1.999998p-4f);
    _TEST_INT(sscanf("-0.1", "%Lf", &lgot), 1);
    _TEST_FLOAT(lgot, -0xc.cccccccccccccccp-7L);

    fesetround(FE_DOWNWARD);
    _TEST_INT(sscanf("0.1 -0.1", "%lf %f", &got, &fgot), 2);
    _TEST_FLOAT(got, 0x1.9999999999999p-4);
    _TEST_FLOAT(fgot, -0x1.99999ap-4f);
    _TEST_INT(sscanf("0.1", "%Lf", &lgot), 1);
    _TEST_FLOAT(lgot, 0xc.cccccccccccccccp-7L);

    fesetround(FE_TOWARDZERO);
    _TEST_INT(sscanf("-0.1", "%lf", &got), 1);
    _TEST_FLOAT(got, -0x1.9999999999999p-4);
    fesetround(FE_TONEAREST);
}

int main(void)
{
    Test_FenvScanf();
    return _Test_Status();
}
