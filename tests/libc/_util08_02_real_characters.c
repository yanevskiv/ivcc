// (Test) Status: 0
// A test file for <_real.h> characters, digits and words.

// Include helpers.
#include "_util08_00_real_helpers.inc"

// A character should be classed and converted as in "C", a word in any case.
static void Test_RealCharacters(void)
{
    const int wide[] = { 'I', 'n', 'F', 0x20AC, 0 };

    _TEST_TRUE(_Real_IsSpace(' '));
    _TEST_TRUE(_Real_IsSpace('\t'));
    _TEST_TRUE(_Real_IsSpace('\r'));
    _TEST_TRUE(! _Real_IsSpace('\0'));
    _TEST_TRUE(! _Real_IsSpace('1'));
    _TEST_TRUE(_Real_IsAlnum('0'));
    _TEST_TRUE(_Real_IsAlnum('9'));
    _TEST_TRUE(_Real_IsAlnum('a'));
    _TEST_TRUE(_Real_IsAlnum('Z'));
    _TEST_TRUE(! _Real_IsAlnum('_'));
    _TEST_TRUE(! _Real_IsAlnum(')'));
    _TEST_TRUE(! _Real_IsAlnum(0x20AC));
    _TEST_INT(_Real_ToLower('A'), 'a');
    _TEST_INT(_Real_ToLower('Z'), 'z');
    _TEST_INT(_Real_ToLower('a'), 'a');
    _TEST_INT(_Real_ToLower('@'), '@');
    _TEST_INT(_Real_ToLower('['), '[');
    _TEST_INT(_Real_ToHexDigit('0'), 0);
    _TEST_INT(_Real_ToHexDigit('9'), 9);
    _TEST_INT(_Real_ToHexDigit('a'), 10);
    _TEST_INT(_Real_ToHexDigit('F'), 15);
    _TEST_INT(_Real_ToHexDigit('g'), _REAL_HEX_LIMIT);
    _TEST_INT(_Real_ToHexDigit('G'), _REAL_HEX_LIMIT);
    _TEST_INT(_Real_ToHexDigit('\0'), _REAL_HEX_LIMIT);
    _TEST_UINT(_Real_MatchWord("INFinity", _REAL_TEXT_NARROW, 0, "inf"), 3);
    _TEST_UINT(_Real_MatchWord("INFinity", _REAL_TEXT_NARROW, 0, "infinity"), 8);
    _TEST_UINT(_Real_MatchWord("-nan", _REAL_TEXT_NARROW, 1, "nan"), 3);
    _TEST_UINT(_Real_MatchWord("inx", _REAL_TEXT_NARROW, 0, "inf"), 0);
    _TEST_UINT(_Real_MatchWord("in", _REAL_TEXT_NARROW, 0, "inf"), 0);
    _TEST_UINT(_Real_MatchWord(wide, _REAL_TEXT_WIDE, 0, "inf"), 3);
    _TEST_INT(_Real_ReadChar(wide, _REAL_TEXT_WIDE, 3), 0x20AC);
    _TEST_INT(_Real_ReadChar("\377", _REAL_TEXT_NARROW, 0), 255);
}

int main(void)
{
    Test_RealCharacters();
    return _Test_Status();
}
