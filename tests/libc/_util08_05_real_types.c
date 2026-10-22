// (Test) Status: 0
// A test file for <_real.h> floats, long doubles and wide text converted.

// Include helpers.
#include "_util08_00_real_helpers.inc"

// A number should round to its own type's mantissa and range, not a double's.
static void Test_RealTypes(void)
{
    const int wide[] = { ' ', '-', '2', '.', '5', 'e', '1', 0x20AC, 0 };
    unsigned long end = 0;

    _Err_Errno = 0;
    _TEST_FLOAT(_Real_ToFloat("16777217", _REAL_TEXT_NARROW, &end), 16777216.0F);
    _TEST_UINT(end, 8);
    _TEST_FLOAT(_Real_ToFloat("16777219", _REAL_TEXT_NARROW, &end), 16777220.0F);
    _TEST_FLOAT(_Real_ToFloat("0.1", _REAL_TEXT_NARROW, &end), 0.1F);
    _TEST_FLOAT(_Real_ToFloat("0x1.fffffep127", _REAL_TEXT_NARROW, &end), 0x1.fffffep127F);
    _TEST_FLOAT(_Real_ToLongDouble("0.1", _REAL_TEXT_NARROW, &end), 0.1L);
    _TEST_FLOAT(_Real_ToLongDouble("18446744073709551617", _REAL_TEXT_NARROW, &end), 18446744073709551616.0L);
    _TEST_UINT(end, 20);
    _TEST_FLOAT(_Real_ToLongDouble("0x1.fffffffffffffffep16383", _REAL_TEXT_NARROW, &end), 0x1.fffffffffffffffep16383L);
    _TEST_FLOAT(_Real_ToLongDouble("1e400", _REAL_TEXT_NARROW, &end), 1e400L);
    _TEST_FLOAT(_Real_ToDouble(wide, _REAL_TEXT_WIDE, &end), -25.0);
    _TEST_UINT(end, 7);
    _TEST_FLOAT(_Real_ToFloat(wide, _REAL_TEXT_WIDE, &end), -25.0F);
    _TEST_FLOAT(_Real_ToLongDouble(wide, _REAL_TEXT_WIDE, &end), -25.0L);
    _TEST_INT(_Err_Errno, 0);
    _TEST_FLOAT(_Real_ToFloat("3.5e38", _REAL_TEXT_NARROW, &end), 1.0F / 0.0F);
    _TEST_INT(_Err_Errno, _SYS_LINUX_ERANGE);
    _Err_Errno = 0;
    _TEST_FLOAT(_Real_ToFloat("1e-50", _REAL_TEXT_NARROW, &end), 0.0F);
    _TEST_INT(_Err_Errno, _SYS_LINUX_ERANGE);
    _Err_Errno = 0;
    _TEST_FLOAT(_Real_ToLongDouble("1e5000", _REAL_TEXT_NARROW, &end), 1.0L / 0.0L);
    _TEST_INT(_Err_Errno, _SYS_LINUX_ERANGE);
}

int main(void)
{
    Test_RealTypes();
    return _Test_Status();
}
