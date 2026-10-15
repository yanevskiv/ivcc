// (Test) Status: 200
// A bit-field controlling a _Generic has the type it was declared with, so
// `int bf : 3` picks `int` and `unsigned ubf : 4` picks `unsigned int`.
// Non-standard: a bit-field's type in a generic selection, its declared one,
// as clang has it; gcc gives each width a type of its own, which picks no
// association but the default.
// Liberty: C11 says a bit-field is interpreted as having an integer type of
// its width, and not whether that type is the declared one.
// [C11:6.7.2.1p10]: a bit-field, an integer type of the specified number of bits

struct Bits {
    int      bi_signed : 3;
    unsigned bi_unsigned : 4;
    _Bool    bi_flag : 1;
};

int main(void)
{
    struct Bits bits = { 1, 2, 1 };
    int         status = 0;

    status += _Generic(bits.bi_signed, int: 50, default: 1);
    status += _Generic(bits.bi_unsigned, unsigned int: 50, default: 1);
    status += _Generic(bits.bi_flag, _Bool: 50, default: 1);
    status += _Generic(bits.bi_signed + 0, int: 50, default: 1);
    return status;
}
