// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> rounding directions in strtod, strtof and strtold.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"

// strtod, strtof and strtold should round a decimal and a hexadecimal subject
// sequence in the current direction, a negative one by its own value, and a
// value below the least normal one to a subnormal one or zero the same way.
// [C99:3.9p1]:       a correctly rounded result, subject to the rounding mode
// [C99:7.20.1.3p5]:  a hexadecimal subject sequence correctly rounded
// [C99:7.20.1.3p10]: an underflow no greater than the least normal value
// [C99:F.5p2]:       a decimal of DECIMAL_DIG digits correctly rounded
// [C99:F.5p3]:       strtod honours the direction, never negating the value
static void Test_FenvStrtod(void)
{
    fesetround(FE_TONEAREST);
    _TEST_FLOAT(strtod("0.1", NULL), 0x1.999999999999ap-4);
    _TEST_FLOAT(strtod("-0.1", NULL), -0x1.999999999999ap-4);
    _TEST_FLOAT(strtod("0x1.00000000000008p0", NULL), 1.0);
    _TEST_FLOAT(strtod("-0x1.00000000000018p0", NULL), -0x1.0000000000002p0);
    _TEST_FLOAT(strtod("1e-999", NULL), 0.0);
    _TEST_FLOAT(strtod("2.2250738585072012e-308", NULL), DBL_MIN);
    _TEST_FLOAT(strtof("0.1", NULL), 0x1.99999ap-4f);
    _TEST_FLOAT(strtold("0.1", NULL), 0xc.ccccccccccccccdp-7L);
    _TEST_FLOAT(strtold("-0.1", NULL), -0xc.ccccccccccccccdp-7L);

    fesetround(FE_UPWARD);
    _TEST_FLOAT(strtod("0.1", NULL), 0x1.999999999999ap-4);
    _TEST_FLOAT(strtod("-0.1", NULL), -0x1.9999999999999p-4);
    _TEST_FLOAT(strtod("0x1.00000000000008p0", NULL), 0x1.0000000000001p0);
    _TEST_FLOAT(strtod("-0x1.00000000000018p0", NULL), -0x1.0000000000001p0);
    _TEST_FLOAT(strtod("1e-999", NULL), 0x1p-1074);
    _TEST_FLOAT(strtod("-1e-999", NULL), -0.0);
    _TEST_FLOAT(strtod("2.2250738585072012e-308", NULL), DBL_MIN);
    _TEST_FLOAT(strtof("0.1", NULL), 0x1.99999ap-4f);
    _TEST_FLOAT(strtof("-0.1", NULL), -0x1.999998p-4f);
    _TEST_FLOAT(strtold("0.1", NULL), 0xc.ccccccccccccccdp-7L);
    _TEST_FLOAT(strtold("-0.1", NULL), -0xc.cccccccccccccccp-7L);

    fesetround(FE_DOWNWARD);
    _TEST_FLOAT(strtod("0.1", NULL), 0x1.9999999999999p-4);
    _TEST_FLOAT(strtod("-0.1", NULL), -0x1.999999999999ap-4);
    _TEST_FLOAT(strtod("0x1.00000000000008p0", NULL), 1.0);
    _TEST_FLOAT(strtod("-0x1.00000000000008p0", NULL), -0x1.0000000000001p0);
    _TEST_FLOAT(strtod("1e-999", NULL), 0.0);
    _TEST_FLOAT(strtod("-1e-999", NULL), -0x1p-1074);
    _TEST_FLOAT(strtod("2.2250738585072012e-308", NULL), 0x0.fffffffffffffp-1022);
    _TEST_FLOAT(strtof("0.1", NULL), 0x1.999998p-4f);
    _TEST_FLOAT(strtof("-0.1", NULL), -0x1.99999ap-4f);
    _TEST_FLOAT(strtold("0.1", NULL), 0xc.cccccccccccccccp-7L);
    _TEST_FLOAT(strtold("-0.1", NULL), -0xc.ccccccccccccccdp-7L);

    fesetround(FE_TOWARDZERO);
    _TEST_FLOAT(strtod("0.1", NULL), 0x1.9999999999999p-4);
    _TEST_FLOAT(strtod("-0.1", NULL), -0x1.9999999999999p-4);
    _TEST_FLOAT(strtod("0x1.00000000000018p0", NULL), 0x1.0000000000001p0);
    _TEST_FLOAT(strtod("-0x1.00000000000018p0", NULL), -0x1.0000000000001p0);
    _TEST_FLOAT(strtod("-1e-999", NULL), -0.0);
    _TEST_FLOAT(strtod("2.2250738585072012e-308", NULL), 0x0.fffffffffffffp-1022);
    _TEST_FLOAT(strtof("-0.1", NULL), -0x1.999998p-4f);
    _TEST_FLOAT(strtold("-0.1", NULL), -0xc.cccccccccccccccp-7L);
    fesetround(FE_TONEAREST);
}

int main(void)
{
    Test_FenvStrtod();
    return _Test_Status();
}
