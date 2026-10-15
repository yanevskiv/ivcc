// (Test) Status: 42
// _Generic, C11's, as gcc takes it under C99. It picks the association whose
// type is compatible with its controlling expression's, else the default;
// the controlling expression is converted as an operand is, its qualifiers
// dropped and an array or a function made a pointer, and never evaluated,
// nor is any association but the one picked. The result is that
// association's expression, an lvalue or a function where it is one, and a
// constant where it is one.
// [C11:6.5.1.1p1]: _Generic, a controlling expression and associations
// [C11:6.5.1.1p3]: the association picked, the others never evaluated
// [C11:6.5.1.1p4]: its type, value and lvalue-ness the picked expression's

struct Pair {
    int pa_first;
    int pa_second;
};

#define KIND(x) _Generic((x),                                                \
    _Bool: 1, char: 2, signed char: 3, unsigned char: 4,                     \
    short: 5, unsigned short: 6, int: 7, unsigned int: 8,                    \
    long: 9, unsigned long: 10, long long: 11, unsigned long long: 12,       \
    float: 13, double: 14, long double: 15,                                  \
    float _Complex: 16, double _Complex: 17, long double _Complex: 18,       \
    char *: 19, const char *: 20, int *: 21, struct Pair: 22,                \
    struct Pair *: 23, int (*)(int): 24, default: 0)

static int twice(int x)
{
    return 2 * x;
}

static float half_float(float x)
{
    return x / 2;
}

static double half_double(double x)
{
    return x / 2;
}

#define HALF(x) _Generic((x), float: half_float, default: half_double)(x)

_Static_assert(KIND((_Bool) 1) == 1, "_Bool");
_Static_assert(KIND('a') == 7, "a character constant is an int");
_Static_assert(KIND((char) 'a') == 2, "plain char");
_Static_assert(KIND((signed char) 'a') == 3, "signed char, apart from char");
_Static_assert(KIND((unsigned char) 'a') == 4, "unsigned char");
_Static_assert(KIND((short) 1) == 5, "short");
_Static_assert(KIND((unsigned short) 1) == 6, "unsigned short");
_Static_assert(KIND(1) == 7, "int");
_Static_assert(KIND(1u) == 8, "unsigned int");
_Static_assert(KIND(1l) == 9, "long");
_Static_assert(KIND(1ul) == 10, "unsigned long");
_Static_assert(KIND(1ll) == 11, "long long, apart from long");
_Static_assert(KIND(1ull) == 12, "unsigned long long");
_Static_assert(KIND(1.0f) == 13, "float");
_Static_assert(KIND(1.0) == 14, "double");
_Static_assert(KIND(1.0L) == 15, "long double");
_Static_assert(KIND("text") == 19, "a string literal, made a char pointer");
_Static_assert(KIND(twice) == 24, "a function, made a pointer");
_Static_assert(_Generic(1, default: 5, int: 6) == 6, "the default goes anywhere");
_Static_assert(_Generic(1.0, int: 5, default: 6) == 6, "the default");
_Static_assert(_Generic(_Generic(1, int: 1.0f), float: 1, default: 2) == 1, "nested");

enum {
    PICKED = _Generic(1u, unsigned int: 3, int: 4)
};

static int sized[_Generic(1l, long: 5, default: 1)];

// Return the kinds of objects, each converted as an operand is.
static int check_objects(void)
{
    const int        fixed = 1;
    volatile double  moving = 1;
    int              row[4];
    char             text[4];
    const char      *view = "text";
    float _Complex   small = 1;
    double _Complex  middle = 1;
    long double _Complex large = 1;
    struct Pair      pair = { 1, 2 };
    struct Pair     *ptr = &pair;

    if (KIND(fixed) != 7 || KIND(moving) != 14) {
        return 1;
    }
    if (KIND(row) != 21 || KIND(text) != 19 || KIND(view) != 20) {
        return 2;
    }
    if (KIND(small) != 16 || KIND(middle) != 17 || KIND(large) != 18) {
        return 3;
    }
    if (KIND(pair) != 22 || KIND(ptr) != 23 || KIND(&fixed) != 0) {
        return 4;
    }
    if (KIND(fixed + 1.0f) != 13 || KIND(row[0] + 1l) != 9) {
        return 5;
    }
    return 0;
}

// Return whether only the association picked is evaluated, and the
// controlling expression never is.
static int check_evaluation(void)
{
    int count = 0;
    int other = 0;
    int value = _Generic(count++, int: count + 10, default: other++);

    if (count != 0 || other != 0 || value != 10) {
        return 6;
    }
    value = _Generic(1.0, int: other++, double: ++count);
    if (count != 1 || other != 0 || value != 1) {
        return 7;
    }
    _Generic(count, int: (void) ++count, default: (void) ++other);
    if (count != 2 || other != 0) {
        return 8;
    }
    return 0;
}

// Return whether the picked expression keeps what it is: an lvalue, a
// function to call, a constant.
static int check_results(void)
{
    int    a = 1;
    double b = 2;
    int   *ptr = &_Generic(1, int: a, double: b);

    _Generic(1.0, int: a, double: b) = 5;
    *ptr += 2;
    if (a != 3 || b != 5) {
        return 9;
    }
    if (HALF(3.0f) != 1.5f || HALF(3) != 1.5) {
        return 10;
    }
    if (_Generic(0, int: twice, default: twice)(21) != 42) {
        return 11;
    }
    switch (a) {
        case _Generic(a, int: 3, default: 4): {
            break;
        }
        default: {
            return 12;
        }
    }
    if (PICKED != 3 || sizeof(sized) != 5 * sizeof(int)) {
        return 13;
    }
    return 0;
}

int main(void)
{
    int status = check_objects();

    if (! status) {
        status = check_evaluation();
    }
    if (! status) {
        status = check_results();
    }
    return status ? status : 42;
}
