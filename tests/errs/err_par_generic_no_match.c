// (Test) Compiler error: [ERR_PAR_GENERIC_NO_MATCH]
// Can't pick no association, no type matching and no default given.

int value = _Generic(1.0, int: 1, float: 2);
