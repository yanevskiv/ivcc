// (Test) Status: 0
// A test file for <_fpu.h> flags and rounding.

// Includes.
#include <_test.h>
#include <_fpu.h>

// Raising, writing and clearing flags should set exactly those, and the
// rounding direction should read back as written, a bad one refused.
static void Test_FpuFlags(void)
{
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), 0);
    _Fpu_x86_64_RaiseFlags(_FPU_X86_64_INVALID | _FPU_X86_64_INEXACT);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_INVALID | _FPU_X86_64_INEXACT);
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_INVALID);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_INEXACT);
    _Fpu_x86_64_WriteFlags(_FPU_X86_64_OVERFLOW, _FPU_X86_64_OVERFLOW | _FPU_X86_64_INEXACT);
    _TEST_INT(_Fpu_x86_64_TestFlags(_FPU_X86_64_EXCEPTS), _FPU_X86_64_OVERFLOW);
    _Fpu_x86_64_ClearFlags(_FPU_X86_64_EXCEPTS);

    _TEST_INT(_Fpu_x86_64_WriteRound(_FPU_X86_64_UPWARD), 0);
    _TEST_INT(_Fpu_x86_64_ReadRound(), _FPU_X86_64_UPWARD);
    _TEST_INT(_Fpu_x86_64_WriteRound(_FPU_X86_64_ROUND_MASK + 1), _FPU_X86_64_FAILED);
    _TEST_INT(_Fpu_x86_64_ReadRound(), _FPU_X86_64_UPWARD);
    _TEST_INT(_Fpu_x86_64_WriteRound(_FPU_X86_64_TONEAREST), 0);
    _TEST_INT(_Fpu_x86_64_ReadRound(), _FPU_X86_64_TONEAREST);
}

int main(void)
{
    Test_FpuFlags();
    return _Test_Status();
}
