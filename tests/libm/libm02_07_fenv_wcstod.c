// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> rounding directions in wcstod, wcstof and wcstold.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"

// wcstod, wcstof and wcstold should round a decimal and a hexadecimal subject
// sequence in the current direction, a negative one by its own value.
// [C99:3.9p1]:        a correctly rounded result, subject to the rounding mode
// [C99:7.24.4.1.1p5]: a hexadecimal subject sequence correctly rounded
// [C99:7.24.4.1.1p9]: a decimal of DECIMAL_DIG digits correctly rounded
// [C99:F.5p3]:        strtod honours the direction, never negating the value
static void Test_FenvWcstod(void)
{
    fesetround(FE_TONEAREST);
    _TEST_FLOAT(wcstod(L"0.1", NULL), 0x1.999999999999ap-4);
    _TEST_FLOAT(wcstod(L"-0x1.00000000000018p0", NULL), -0x1.0000000000002p0);
    _TEST_FLOAT(wcstof(L"-0.1", NULL), -0x1.99999ap-4f);
    _TEST_FLOAT(wcstold(L"0.1", NULL), 0xc.ccccccccccccccdp-7L);

    fesetround(FE_UPWARD);
    _TEST_FLOAT(wcstod(L"0.1", NULL), 0x1.999999999999ap-4);
    _TEST_FLOAT(wcstod(L"-0.1", NULL), -0x1.9999999999999p-4);
    _TEST_FLOAT(wcstod(L"0x1.00000000000008p0", NULL), 0x1.0000000000001p0);
    _TEST_FLOAT(wcstof(L"-0.1", NULL), -0x1.999998p-4f);
    _TEST_FLOAT(wcstold(L"-0.1", NULL), -0xc.cccccccccccccccp-7L);

    fesetround(FE_DOWNWARD);
    _TEST_FLOAT(wcstod(L"0.1", NULL), 0x1.9999999999999p-4);
    _TEST_FLOAT(wcstod(L"-0x1.00000000000008p0", NULL), -0x1.0000000000001p0);
    _TEST_FLOAT(wcstof(L"0.1", NULL), 0x1.999998p-4f);
    _TEST_FLOAT(wcstold(L"0.1", NULL), 0xc.cccccccccccccccp-7L);

    fesetround(FE_TOWARDZERO);
    _TEST_FLOAT(wcstod(L"-0.1", NULL), -0x1.9999999999999p-4);
    _TEST_FLOAT(wcstod(L"0x1.00000000000018p0", NULL), 0x1.0000000000001p0);
    _TEST_FLOAT(wcstof(L"-0.1", NULL), -0x1.999998p-4f);
    _TEST_FLOAT(wcstold(L"-0.1", NULL), -0xc.cccccccccccccccp-7L);
    fesetround(FE_TONEAREST);
}

int main(void)
{
    Test_FenvWcstod();
    return _Test_Status();
}
