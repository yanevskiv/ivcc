// (Test) Compiler error: [ERR_PAR_GENERIC_TYPES_COMPATIBLE]
// Can't name compatible types in two generic associations.

typedef int Number;

int value = _Generic(1, int: 1, Number: 2);
