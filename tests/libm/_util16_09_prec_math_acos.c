// (Test) Compiler flags: -lm
// (Test) Status: 0
// A test file for <_prec_math.h> __prec_math_acos.

// Include helpers.
#include "_util16_00_prec_math_helpers.inc"

// Defines.
#define MODES 4

// __prec_math_acos should give the arc cosine of x in [0, pi] in each type, in
// the current direction for float and long double, +0 of 1 raising nothing,
// pi/2 of a zero and pi of -1, and a NaN with invalid and EDOM outside [-1,
// +1], an infinity too.
static void Test_PrecMathAcos(void)
{
    static const int modes[MODES] = {_FPU_X86_64_TONEAREST, _FPU_X86_64_DOWNWARD, _FPU_X86_64_UPWARD, _FPU_X86_64_TOWARDZERO};
    static const float valuef[MODES] = {0x1.d2cf5cp+0f, 0x1.d2cf5cp+0f, 0x1.d2cf5ep+0f, 0x1.d2cf5cp+0f};
    static const long double valuel[MODES] = {0x8.60a91c16b9b2c23p-2L, 0x8.60a91c16b9b2c23p-2L, 0x8.60a91c16b9b2c24p-2L, 0x8.60a91c16b9b2c23p-2L};
    volatile double half = 0.5;
    volatile float quarterf = -0.25f;
    volatile long double halfl = -0.5L;
    volatile double zero = 0.0;
    double inf = 1.0 / zero;
    double dnan = zero / zero;

    for (int i = 0; i < MODES; i++) {
        _Fpu_x86_64_WriteRound(modes[i]);
        _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
        _TEST_FLOAT(__prec_math_acosf(quarterf), valuef[i]);
        _TEST_FLOAT(__prec_math_acosl(halfl), valuel[i]);
        _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_INEXACT);
    }
    _Fpu_x86_64_WriteRound(_FPU_X86_64_TONEAREST);
    _TEST_FLOAT(__prec_math_acos(half), 0x1.0c152382d7366p+0);

    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
    _TEST_FLOAT(__prec_math_acos(1.0), 0.0);
    _TEST_FLOAT(__prec_math_acosf(1.0f), 0.0f);
    _TEST_FLOAT(__prec_math_acosl(1.0L), 0.0L);
    _TEST_TRUE(_Long_Double_x86_64_IsNan(__prec_math_acos(dnan)));
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), 0);
    _TEST_FLOAT(__prec_math_acos(-0.0), 0x1.921fb54442d18p+0);
    _TEST_FLOAT(__prec_math_acos(-1.0), 0x1.921fb54442d18p+1);
    _TEST_FLOAT(__prec_math_acosl(0.0L), 0xc.90fdaa22168c235p-3L);

    _Err_Errno = 0;
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
    _TEST_TRUE(_Long_Double_x86_64_IsNan(__prec_math_acos(-1.5)));
    _TEST_INT(_Err_Errno, _SYS_LINUX_EDOM);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_INVALID);
    _Err_Errno = 0;
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
    _TEST_TRUE(_Long_Double_x86_64_IsNan(__prec_math_acosf((float) inf)));
    _TEST_INT(_Err_Errno, _SYS_LINUX_EDOM);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_INVALID);
    _Err_Errno = 0;
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
}

int main(void)
{
    Test_PrecMathAcos();
    return _Test_Status();
}
