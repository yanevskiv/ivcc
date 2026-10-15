// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <fenv.h> flags raised by strtod, strtof, strtold and wcstod.

// Include helpers.
#include "libm02_00_fenv_helpers.inc"

// Return the flags strtod raises converting str.
static int strtod_flags(const char *str)
{
    feclearexcept(FE_ALL_EXCEPT);
    (void) strtod(str, NULL);
    return fetestexcept(FE_ALL_EXCEPT);
}

// Return the flags strtof raises converting str.
static int strtof_flags(const char *str)
{
    feclearexcept(FE_ALL_EXCEPT);
    (void) strtof(str, NULL);
    return fetestexcept(FE_ALL_EXCEPT);
}

// Return the flags strtold raises converting str.
static int strtold_flags(const char *str)
{
    feclearexcept(FE_ALL_EXCEPT);
    (void) strtold(str, NULL);
    return fetestexcept(FE_ALL_EXCEPT);
}

// Return the flags wcstod raises converting str.
static int wcstod_flags(const wchar_t *str)
{
    feclearexcept(FE_ALL_EXCEPT);
    (void) wcstod(str, NULL);
    return fetestexcept(FE_ALL_EXCEPT);
}

// strtod and its kin should raise inexact for a value they round, overflow
// with it for one too large, underflow with it for one too small rounded,
// and nothing for a value they convert exactly, a subnormal one too.
// [C99:7.20.1.3p10]: a value out of range HUGE_VAL, and ERANGE
// [C99:F.3p1]:       strtod, IEC 60559's binary-decimal conversion
// [C99:F.5p2]:       the conversions follow IEC 60559's recommended practice
static void Test_FenvStrtodFlags(void)
{
    _TEST_INT(strtod_flags("0.5"), 0);
    _TEST_INT(strtod_flags("0x1.8p3"), 0);
    _TEST_INT(strtod_flags("0x1p-1074"), 0);
    _TEST_INT(strtod_flags("inf"), 0);
    _TEST_INT(strtod_flags("nan"), 0);
    _TEST_INT(strtod_flags("0.1"), FE_INEXACT);
    _TEST_INT(strtod_flags("-0x1.00000000000008p0"), FE_INEXACT);
    _TEST_INT(strtod_flags("1e999"), FE_OVERFLOW | FE_INEXACT);
    _TEST_INT(strtod_flags("-1e999"), FE_OVERFLOW | FE_INEXACT);
    _TEST_INT(strtod_flags("1e-999"), FE_UNDERFLOW | FE_INEXACT);
    _TEST_INT(strtod_flags("4e-324"), FE_UNDERFLOW | FE_INEXACT);

    _TEST_INT(strtof_flags("0.25"), 0);
    _TEST_INT(strtof_flags("0.1"), FE_INEXACT);
    _TEST_INT(strtof_flags("1e39"), FE_OVERFLOW | FE_INEXACT);
    _TEST_INT(strtof_flags("1e-46"), FE_UNDERFLOW | FE_INEXACT);

    _TEST_INT(strtold_flags("0.1"), FE_INEXACT);
    _TEST_INT(strtold_flags("1e5000"), FE_OVERFLOW | FE_INEXACT);
    _TEST_INT(strtold_flags("1e-5000"), FE_UNDERFLOW | FE_INEXACT);

    _TEST_INT(wcstod_flags(L"0.5"), 0);
    _TEST_INT(wcstod_flags(L"0.1"), FE_INEXACT);
    _TEST_INT(wcstod_flags(L"1e999"), FE_OVERFLOW | FE_INEXACT);

    fesetround(FE_TOWARDZERO);
    _TEST_INT(strtod_flags("1e999"), FE_OVERFLOW | FE_INEXACT);
    fesetround(FE_TONEAREST);
    feclearexcept(FE_ALL_EXCEPT);
}

int main(void)
{
    Test_FenvStrtodFlags();
    return _Test_Status();
}
