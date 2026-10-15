// (Test) Compiler error: [ERR_PAR_GENERIC_TWO_DEFAULTS]
// Can't give a generic selection two default associations.

int value = _Generic(1, default: 1, int: 2, default: 3);
