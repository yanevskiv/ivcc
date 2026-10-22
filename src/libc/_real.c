/*
 * C source file for the conversion of text to a floating number.
 *
 * Copyright (C) 2026 Ivan Janevski
 *
 * ivcc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * ivcc is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with ivcc; see
 * the files LICENSE and COPYING.RUNTIME respectively.  If not, see
 * <https://www.gnu.org/licenses/>.
 */


// Module header.
#include <_real.h>

// The exact arithmetic a decimal is rounded by.
#include <_bigint.h>

// The error number of a value out of range.
#include <_sys.h>

// The error number of the last failed call.
#include <_err.h>

// The loop that copies a value's bytes.
#include <_str.h>

// The rounding direction a value is converted in, and long double's fields.
#include <_fpu.h>

// The format of float, its exponents one below C's.
const _Real_Format _Real_FloatFormat = {
    .rf_mant     = _REAL_FLOAT_MANT,
    .rf_min      = _REAL_FLOAT_MIN,
    .rf_max      = _REAL_FLOAT_MAX,
    .rf_explicit = 0
};

// The format of double, its exponents one below C's.
const _Real_Format _Real_DoubleFormat = {
    .rf_mant     = _REAL_DOUBLE_MANT,
    .rf_min      = _REAL_DOUBLE_MIN,
    .rf_max      = _REAL_DOUBLE_MAX,
    .rf_explicit = 0
};

// The format of long double, its exponents one below C's, its lead bit given.
const _Real_Format _Real_LongDoubleFormat = {
    .rf_mant     = _FPU_X86_64_LDBL_MANT,
    .rf_min      = _FPU_X86_64_LDBL_EXP_MIN,
    .rf_max      = _FPU_X86_64_LDBL_EXP_MAX,
    .rf_explicit = 1
};

// Read character index of str, a wide string or a narrow one.
int _Real_ReadChar(const void *str, _Real_Text text, unsigned long index)
{
    if (text == _REAL_TEXT_WIDE) {
        return ((const int *) str)[index];
    }
    return ((const unsigned char *) str)[index];
}

// Check whether ch is white space in the "C" locale.
_Bool _Real_IsSpace(int ch)
{
    return ch == ' ' || (ch >= '\t' && ch <= '\r');
}

// Check whether ch is a letter or a digit in the "C" locale.
_Bool _Real_IsAlnum(int ch)
{
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Match word at index of str in any case, and give its length, or 0.
unsigned long _Real_MatchWord(const void *str, _Real_Text text, unsigned long index, const char *word)
{
    unsigned long i;
    int ch;

    for (i = 0; word[i] != '\0'; i++) {
        ch = _Real_ReadChar(str, text, index + i);
        if (_Real_ToLower(ch) != word[i]) {
            return 0;
        }
    }
    return i;
}

// Read an exponent after letter at index into *exp, and give the index past it.
unsigned long _Real_ReadExponent(const void *str, _Real_Text text, unsigned long index, int letter, long *exp)
{
    unsigned long i = index + 1;
    _Bool negative = 0;
    long value = 0;
    int ch = _Real_ReadChar(str, text, index);

    *exp = 0;
    if (_Real_ToLower(ch) != letter) {
        return index;
    }
    ch = _Real_ReadChar(str, text, i);
    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        i++;
    }
    ch = _Real_ReadChar(str, text, i);
    if (ch < '0' || ch > '9') {
        return index;
    }
    for (; ch >= '0' && ch <= '9'; ch = _Real_ReadChar(str, text, i)) {
        if (value < _REAL_EXP_LIMIT) {
            value = value * 10 + (ch - '0');
        }
        i++;
    }
    *exp = negative ? -value : value;
    return i;
}

// Read a NaN's payload up to stop as strtoull in base 0, or 0, as glibc's.
unsigned long long _Real_ReadPayload(const void *str, _Real_Text text, unsigned long index, unsigned long stop)
{
    unsigned long long value = 0;
    int base = 10;
    int digit;

    if (_Real_ReadChar(str, text, index) == '0') {
        base = 8;
        if (_Real_ToLower(_Real_ReadChar(str, text, index + 1)) == 'x' && _Real_ToHexDigit(_Real_ReadChar(str, text, index + 2)) < _REAL_HEX_LIMIT) {
            base = _REAL_HEX_LIMIT;
            index += 2;
        }
    }
    for (; index < stop; index++) {
        digit = _Real_ToHexDigit(_Real_ReadChar(str, text, index));
        if (digit >= base) {
            return 0;
        }
        value = value > (_REAL_PAYLOAD_MAX - (unsigned long long) digit) / (unsigned long long) base ? _REAL_PAYLOAD_MAX : value * (unsigned long long) base + (unsigned long long) digit;
    }
    return value;
}

// Read a NaN's parenthesized characters at index, and give the index past them.
unsigned long _Real_ReadNotANumber(const void *str, _Real_Text text, unsigned long index, unsigned long long *payload)
{
    unsigned long i = index + 1;
    int ch;

    *payload = 0;
    if (_Real_ReadChar(str, text, index) != '(') {
        return index;
    }
    for (ch = _Real_ReadChar(str, text, i); ch == '_' || _Real_IsAlnum(ch); ch = _Real_ReadChar(str, text, i)) {
        i++;
    }
    if (ch != ')') {
        return index;
    }
    *payload = _Real_ReadPayload(str, text, index + 1, i);
    return i + 1;
}

// Scan a decimal's digits and exponent at index, and give the index past them.
unsigned long _Real_ScanDecimal(const void *str, _Real_Text text, unsigned long index, int point, _Real_Decimal *dec)
{
    unsigned long i;
    _Bool digits = 0;
    _Bool fraction = 0;
    long exp;
    int ch;

    dec->rd_first = 0;
    dec->rd_count = 0;
    dec->rd_exp = 0;
    dec->rd_sticky = 0;
    for (i = index; ; i++) {
        ch = _Real_ReadChar(str, text, i);
        if (ch == point && ! fraction) {
            fraction = 1;
            continue;
        }
        if (ch < '0' || ch > '9') {
            break;
        }
        digits = 1;
        if (dec->rd_count == 0 && ch == '0') {
            dec->rd_exp -= fraction;
            continue;
        }
        if (dec->rd_count == 0) {
            dec->rd_first = i;
        }
        if (dec->rd_count < _REAL_DIGITS) {
            dec->rd_count++;
            dec->rd_exp -= fraction;
        } else {
            dec->rd_sticky |= ch != '0';
            dec->rd_exp += ! fraction;
        }
    }
    if (! digits) {
        return index;
    }
    i = _Real_ReadExponent(str, text, i, 'e', &exp);
    dec->rd_exp += exp;
    return i;
}

// Read a hexadecimal's digits and exponent at index, and give the end.
unsigned long _Real_ReadHex(const void *str, _Real_Text text, unsigned long index, int point, _Real_Unrounded *value)
{
    unsigned long long mant = 0;
    unsigned int extra = 0;
    _Bool sticky = 0;
    _Bool fraction = 0;
    long count = 0;
    long exp = 0;
    long power;
    unsigned long i;
    int ch;
    int digit;

    for (i = index; ; i++) {
        ch = _Real_ReadChar(str, text, i);
        if (ch == point && ! fraction) {
            fraction = 1;
            continue;
        }
        digit = _Real_ToHexDigit(ch);
        if (digit == _REAL_HEX_LIMIT) {
            break;
        }
        if (count == 0 && digit == 0) {
            exp -= fraction * _REAL_HEX_BITS;
            continue;
        }
        if (count < _REAL_MANT_BITS / _REAL_HEX_BITS) {
            mant = mant << _REAL_HEX_BITS | (unsigned long long) digit;
            exp -= fraction * _REAL_HEX_BITS;
        } else {
            if (count == _REAL_MANT_BITS / _REAL_HEX_BITS) {
                extra = (unsigned int) digit;
            } else {
                sticky |= digit != 0;
            }
            exp += ! fraction * _REAL_HEX_BITS;
        }
        count++;
    }
    i = _Real_ReadExponent(str, text, i, 'p', &power);
    value->ru_mant = mant;
    value->ru_exp = exp + power + _REAL_MANT_BITS - 1;
    value->ru_rest = _REAL_REST_NONE;
    if (mant == 0) {
        return i;
    }
    while (mant >> (_REAL_MANT_BITS - 1) == 0) {
        mant = mant << 1 | extra >> (_REAL_HEX_BITS - 1);
        extra = extra << 1 & (_REAL_HEX_LIMIT - 1);
        value->ru_exp--;
    }
    value->ru_mant = mant;
    if (extra > _REAL_HEX_TOP || (extra == _REAL_HEX_TOP && sticky)) {
        value->ru_rest = _REAL_REST_ABOVE;
    } else if (extra == _REAL_HEX_TOP) {
        value->ru_rest = _REAL_REST_HALF;
    } else if (extra != 0 || sticky) {
        value->ru_rest = _REAL_REST_BELOW;
    }
    return i;
}

// Drop the low bits of value's mantissa, keeping what they were against half.
void _Real_DropBits(_Real_Unrounded *value, long bits)
{
    unsigned long long mant = value->ru_mant;
    _Bool rest = value->ru_rest != _REAL_REST_NONE;
    _Bool round;
    _Bool lower;

    if (bits > _REAL_MANT_BITS) {
        value->ru_mant = 0;
        value->ru_rest = mant != 0 || rest ? _REAL_REST_BELOW : _REAL_REST_NONE;
        return;
    }
    round = mant >> (bits - 1) & 1;
    lower = (bits > 1 && (mant & ~0ULL >> (_REAL_MANT_BITS + 1 - bits)) != 0) || rest;
    value->ru_mant = bits == _REAL_MANT_BITS ? 0 : mant >> bits;
    if (round) {
        value->ru_rest = lower ? _REAL_REST_ABOVE : _REAL_REST_HALF;
    } else {
        value->ru_rest = lower ? _REAL_REST_BELOW : _REAL_REST_NONE;
    }
}

// Read the direction real's magnitude rounds in, upward away from zero.
int _Real_ReadRound(const _Real_Rounded *real)
{
    int round = _Fpu_x86_64_ReadRound();

    if (real->rr_negative && round == _FPU_X86_64_UPWARD) {
        return _FPU_X86_64_DOWNWARD;
    }
    if (real->rr_negative && round == _FPU_X86_64_DOWNWARD) {
        return _FPU_X86_64_UPWARD;
    }
    return round;
}

// Return whether part's magnitude rounds up to its next mantissa in round.
_Bool _Real_IsRoundedUp(const _Real_Unrounded *part, int round)
{
    if (round == _FPU_X86_64_TONEAREST) {
        return part->ru_rest > _REAL_REST_HALF || (part->ru_rest == _REAL_REST_HALF && (part->ru_mant & 1));
    }
    return round == _FPU_X86_64_UPWARD && part->ru_rest != _REAL_REST_NONE;
}

// Round value to fmt in the current direction, ERANGE and flags as glibc's.
void _Real_RoundValue(const _Real_Unrounded *value, const _Real_Format *fmt, _Real_Rounded *real)
{
    _Real_Unrounded part = *value;
    unsigned long long ones = ~0ULL >> (_REAL_MANT_BITS - fmt->rf_mant);
    int round = _Real_ReadRound(real);
    _Bool tiny;

    real->rr_exp = 0;
    real->rr_mant = 0;
    if (part.ru_mant == 0) {
        return;
    }
    if (fmt->rf_mant < _REAL_MANT_BITS) {
        _Real_DropBits(&part, _REAL_MANT_BITS - fmt->rf_mant);
    }
    tiny = part.ru_exp < fmt->rf_min && ! (part.ru_exp == fmt->rf_min - 1 && part.ru_mant == ones && _Real_IsRoundedUp(&part, round));
    if (part.ru_exp < fmt->rf_min) {
        _Real_DropBits(&part, fmt->rf_min - part.ru_exp);
    }
    if (_Real_IsRoundedUp(&part, round)) {
        part.ru_mant++;
        if (part.ru_exp >= fmt->rf_min && (part.ru_mant & ones) == 0) {
            part.ru_mant = 1ULL << (fmt->rf_mant - 1);
            part.ru_exp++;
        }
    }
    if (part.ru_exp > fmt->rf_max && (round == _FPU_X86_64_TONEAREST || round == _FPU_X86_64_UPWARD)) {
        real->rr_exp = (unsigned int) (2 * fmt->rf_max + 1);
        real->rr_mant = fmt->rf_explicit ? 1ULL << (fmt->rf_mant - 1) : 0;
        _Err_Errno = _SYS_LINUX_ERANGE;
        _Fpu_x86_64_RaiseFlags(_FPU_X86_64_OVERFLOW | _FPU_X86_64_INEXACT);
        return;
    }
    if (part.ru_exp > fmt->rf_max) {
        real->rr_exp = (unsigned int) (2 * fmt->rf_max);
        real->rr_mant = fmt->rf_explicit ? ones : ones >> 1;
        _Err_Errno = _SYS_LINUX_ERANGE;
        _Fpu_x86_64_RaiseFlags(_FPU_X86_64_OVERFLOW | _FPU_X86_64_INEXACT);
        return;
    }
    if (part.ru_exp >= fmt->rf_min) {
        real->rr_exp = (unsigned int) (part.ru_exp + fmt->rf_max);
    } else {
        real->rr_exp = part.ru_mant >> (fmt->rf_mant - 1) != 0;
    }
    real->rr_mant = fmt->rf_explicit ? part.ru_mant : part.ru_mant & ones >> 1;
    if (tiny && part.ru_rest != _REAL_REST_NONE) {
        _Err_Errno = _SYS_LINUX_ERANGE;
        _Fpu_x86_64_RaiseFlags(_FPU_X86_64_UNDERFLOW);
    }
    if (part.ru_rest != _REAL_REST_NONE) {
        _Fpu_x86_64_RaiseFlags(_FPU_X86_64_INEXACT);
    }
}

// Convert ch to lowercase if it is an uppercase letter of the "C" locale.
int _Real_ToLower(int ch)
{
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

// Convert the hex digit ch to its value, or _REAL_HEX_LIMIT for none.
int _Real_ToHexDigit(int ch)
{
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    }
    if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }
    return _REAL_HEX_LIMIT;
}

// Convert a scanned decimal exactly to 64 bits and what lies below them.
void _Real_ToUnrounded(const void *str, _Real_Text text, int point, const _Real_Decimal *dec, _Real_Unrounded *value)
{
    _Bigint_Number num;
    _Bigint_Number den;
    unsigned long i = dec->rd_first;
    long count = dec->rd_count + dec->rd_sticky;
    long exp = dec->rd_exp - dec->rd_sticky;
    long top = dec->rd_count + dec->rd_exp;
    unsigned int chunk = 0;
    unsigned int scale = 1;
    long n;
    int ch;
    int bits;
    int cmp;

    value->ru_mant = (unsigned long long) 1 << (_REAL_MANT_BITS - 1);
    value->ru_rest = _REAL_REST_NONE;
    if (dec->rd_count == 0) {
        value->ru_mant = 0;
        return;
    }
    if (top > _REAL_EXP10_MAX || top < _REAL_EXP10_MIN) {
        value->ru_exp = top > 0 ? _REAL_EXP_LIMIT : -_REAL_EXP_LIMIT;
        return;
    }
    _Bigint_SetValue(&num, 0);
    for (n = 0; n < count; n++) {
        ch = n < dec->rd_count ? _Real_ReadChar(str, text, i) : '1';
        i++;
        if (ch == point) {
            ch = _Real_ReadChar(str, text, i);
            i++;
        }
        chunk = chunk * 10 + (unsigned int) (ch - '0');
        scale *= 10;
        if (scale == _REAL_CHUNK_SCALE || n == count - 1) {
            _Bigint_MulAddWords(&num, scale, chunk);
            chunk = 0;
            scale = 1;
        }
    }
    _Bigint_SetValue(&den, 1);
    if (exp >= 0) {
        _Bigint_MulPow5(&num, (int) exp);
    } else {
        _Bigint_MulPow5(&den, (int) -exp);
    }
    bits = _Bigint_CountBits(&num) - _Bigint_CountBits(&den);
    if (bits > 0) {
        _Bigint_ShiftBitsLeft(&den, bits);
    } else {
        _Bigint_ShiftBitsLeft(&num, -bits);
    }
    if (_Bigint_CompareNumbers(&num, &den) < 0) {
        _Bigint_ShiftBitsLeft(&num, 1);
        bits--;
    }
    value->ru_exp = exp + bits;
    _Bigint_ShiftBitsLeft(&num, _REAL_MANT_BITS - 1);
    value->ru_mant = _Bigint_DivideNumber(&num, &den);
    if (num.bn_len != 0) {
        _Bigint_ShiftBitsLeft(&num, 1);
        cmp = _Bigint_CompareNumbers(&num, &den);
        value->ru_rest = cmp < 0 ? _REAL_REST_BELOW : cmp == 0 ? _REAL_REST_HALF : _REAL_REST_ABOVE;
    }
}

// Convert the number at the start of str to fmt's fields, and give its end.
unsigned long _Real_ToRounded(const void *str, _Real_Text text, const _Real_Format *fmt, _Real_Rounded *real)
{
    _Real_Unrounded value;
    _Real_Decimal dec;
    unsigned long long payload;
    int point = _REAL_POINT;
    unsigned long i = 0;
    unsigned long end;
    int ch;

    real->rr_negative = 0;
    real->rr_exp = (unsigned int) (2 * fmt->rf_max + 1);
    real->rr_mant = fmt->rf_explicit ? 1ULL << (fmt->rf_mant - 1) : 0;
    while (_Real_IsSpace(_Real_ReadChar(str, text, i))) {
        i++;
    }
    ch = _Real_ReadChar(str, text, i);
    if (ch == '+' || ch == '-') {
        real->rr_negative = ch == '-';
        i++;
    }
    if (_Real_MatchWord(str, text, i, "inf")) {
        end = _Real_MatchWord(str, text, i, "infinity");
        return i + (end != 0 ? end : _Real_MatchWord(str, text, i, "inf"));
    }
    if (_Real_MatchWord(str, text, i, "nan")) {
        end = _Real_ReadNotANumber(str, text, i + _Real_MatchWord(str, text, i, "nan"), &payload);
        real->rr_mant |= 1ULL << (fmt->rf_mant - 2) | (payload & ~0ULL >> (_REAL_MANT_BITS + 1 - fmt->rf_mant));
        return end;
    }
    ch = _Real_ReadChar(str, text, i) == '0' ? _Real_ReadChar(str, text, i + 1) : 0;
    if ((ch == 'x' || ch == 'X')
        && (_Real_ToHexDigit(_Real_ReadChar(str, text, i + 2)) < _REAL_HEX_LIMIT
            || (_Real_ReadChar(str, text, i + 2) == point && _Real_ToHexDigit(_Real_ReadChar(str, text, i + 3)) < _REAL_HEX_LIMIT))) {
        end = _Real_ReadHex(str, text, i + 2, point, &value);
    } else {
        end = _Real_ScanDecimal(str, text, i, point, &dec);
        if (end == i) {
            real->rr_negative = 0;
            real->rr_exp = 0;
            real->rr_mant = 0;
            return 0;
        }
        _Real_ToUnrounded(str, text, point, &dec, &value);
    }
    _Real_RoundValue(&value, fmt, real);
    return end;
}


// Convert the number at the start of str to a float, and give its end.
float _Real_ToFloat(const void *str, _Real_Text text, unsigned long *end)
{
    _Real_Rounded real;
    float value;
    unsigned int bits;

    *end = _Real_ToRounded(str, text, &_Real_FloatFormat, &real);
    bits = real.rr_exp << (_REAL_FLOAT_MANT - 1) | (unsigned int) real.rr_mant;
    if (real.rr_negative) {
        bits |= _REAL_FLOAT_SIGN;
    }
    _Str_CopyBytes(&value, &bits, sizeof(value));
    return value;
}

// Convert the number at the start of str to a double, and give its end.
double _Real_ToDouble(const void *str, _Real_Text text, unsigned long *end)
{
    _Real_Rounded real;
    double value;
    unsigned long long bits;

    *end = _Real_ToRounded(str, text, &_Real_DoubleFormat, &real);
    bits = (unsigned long long) real.rr_exp << (_REAL_DOUBLE_MANT - 1) | real.rr_mant;
    if (real.rr_negative) {
        bits |= _REAL_DOUBLE_SIGN;
    }
    _Str_CopyBytes(&value, &bits, sizeof(value));
    return value;
}

// Convert the number at the start of str to a long double, and give its end.
long double _Real_ToLongDouble(const void *str, _Real_Text text, unsigned long *end)
{
    _Real_Rounded real;

    *end = _Real_ToRounded(str, text, &_Real_LongDoubleFormat, &real);
    return _Fpu_x86_64_MakeValue(real.rr_negative, real.rr_exp, real.rr_mant);
}
