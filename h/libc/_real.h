/*
 * C header file for the conversion of text to a floating number.
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


#ifndef _REAL_H
#define _REAL_H

// The significant digits kept, past a long double halfway point's 11515.
#define _REAL_DIGITS 11520

// The decimal exponents past which every format overflows or gives zero.
#define _REAL_EXP10_MAX 4933
#define _REAL_EXP10_MIN (-4951)

// The magnitude an exponent stops growing at, past every format's range.
#define _REAL_EXP_LIMIT 100000000000000000L

// The digits a word of the big integer takes at once, and their scale.
#define _REAL_CHUNK_DIGITS 9
#define _REAL_CHUNK_SCALE  1000000000U

// The bits of a hexadecimal digit, a value past every one, and its top bit.
#define _REAL_HEX_BITS  4
#define _REAL_HEX_LIMIT 16
#define _REAL_HEX_TOP   8

// The bits of the mantissa a number is rounded from.
#define _REAL_MANT_BITS 64

// What lies below a mantissa's last bit, against half that bit.
#define _REAL_REST_NONE  0
#define _REAL_REST_BELOW 1
#define _REAL_REST_HALF  2
#define _REAL_REST_ABOVE 3

// The sign bits of a float and a double.
#define _REAL_FLOAT_SIGN  0x80000000U
#define _REAL_DOUBLE_SIGN 0x8000000000000000ULL

// The greatest payload a NaN's parentheses give.
#define _REAL_PAYLOAD_MAX (~0ULL)

// The character between a number's whole part and its fraction, every locale's.
#define _REAL_POINT '.'

// A float's mantissa bits and its least and greatest exponent, one below C's.
#define _REAL_FLOAT_MANT 24
#define _REAL_FLOAT_MIN  (-126)
#define _REAL_FLOAT_MAX  127

// A double's mantissa bits and its least and greatest exponent, one below C's.
#define _REAL_DOUBLE_MANT 53
#define _REAL_DOUBLE_MIN  (-1022)
#define _REAL_DOUBLE_MAX  1023

// The characters a text to convert is made of.
typedef enum _Real_Text _Real_Text;
enum _Real_Text {
    _REAL_TEXT_NARROW, // a string of char
    _REAL_TEXT_WIDE    // a string of wide characters
};

// A floating type, as the conversion needs to know it.
typedef struct _Real_Format _Real_Format;
struct _Real_Format {
    int rf_mant;       // the bits of its mantissa
    int rf_min;        // its least exponent, one below C's
    int rf_max;        // its greatest exponent, one below C's
    _Bool rf_explicit; // whether it keeps its mantissa's leading bit
};

// A converted number, as the fields of its type.
typedef struct _Real_Rounded _Real_Rounded;
struct _Real_Rounded {
    _Bool rr_negative;          // whether its sign bit is set
    unsigned int rr_exp;        // its biased exponent
    unsigned long long rr_mant; // its mantissa
};

// A number before it is rounded to a type.
typedef struct _Real_Unrounded _Real_Unrounded;
struct _Real_Unrounded {
    unsigned long long ru_mant; // its first 64 bits, from the top one
    long ru_exp;                // the top bit's power of two
    int ru_rest;                // what lies below them, a _REAL_REST_ value
};

// A decimal as it was scanned, before its digits are converted.
typedef struct _Real_Decimal _Real_Decimal;
struct _Real_Decimal {
    unsigned long rd_first; // where its first significant digit is
    long rd_count;          // the digits kept, _REAL_DIGITS at most
    long rd_exp;            // the last kept digit's power of ten
    _Bool rd_sticky;        // whether a digit that was dropped is nonzero
};

// The formats of float, double and long double.
extern const _Real_Format _Real_FloatFormat;
extern const _Real_Format _Real_DoubleFormat;
extern const _Real_Format _Real_LongDoubleFormat;

// Reading
int                _Real_ReadChar(const void *str, _Real_Text text, unsigned long index);
_Bool              _Real_IsSpace(int ch);
_Bool              _Real_IsAlnum(int ch);
unsigned long      _Real_MatchWord(const void *str, _Real_Text text, unsigned long index, const char *word);
unsigned long      _Real_ReadExponent(const void *str, _Real_Text text, unsigned long index, int letter, long *exp);
unsigned long long _Real_ReadPayload(const void *str, _Real_Text text, unsigned long index, unsigned long stop);
unsigned long      _Real_ReadNotANumber(const void *str, _Real_Text text, unsigned long index, unsigned long long *payload);
unsigned long      _Real_ScanDecimal(const void *str, _Real_Text text, unsigned long index, int point, _Real_Decimal *dec);
unsigned long      _Real_ReadHex(const void *str, _Real_Text text, unsigned long index, int point, _Real_Unrounded *value);
void               _Real_DropBits(_Real_Unrounded *value, long bits);
int                _Real_ReadRound(const _Real_Rounded *real);
_Bool              _Real_IsRoundedUp(const _Real_Unrounded *part, int round);
void               _Real_RoundValue(const _Real_Unrounded *value, const _Real_Format *fmt, _Real_Rounded *real);

// Converting
int           _Real_ToLower(int ch);
int           _Real_ToHexDigit(int ch);
void          _Real_ToUnrounded(const void *str, _Real_Text text, int point, const _Real_Decimal *dec, _Real_Unrounded *value);
unsigned long _Real_ToRounded(const void *str, _Real_Text text, const _Real_Format *fmt, _Real_Rounded *real);
float         _Real_ToFloat(const void *str, _Real_Text text, unsigned long *end);
double        _Real_ToDouble(const void *str, _Real_Text text, unsigned long *end);
long double   _Real_ToLongDouble(const void *str, _Real_Text text, unsigned long *end);

#endif // _REAL_H
