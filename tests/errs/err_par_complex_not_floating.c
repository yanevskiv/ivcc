// (Test) Compiler error: [ERR_PAR_COMPLEX_NOT_FLOATING]
// Can't have a complex integer type.
// Note: gcc takes it, and refuses it only with -pedantic-errors.

_Complex int x;
