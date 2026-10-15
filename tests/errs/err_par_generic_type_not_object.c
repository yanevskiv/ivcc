// (Test) Compiler error: [ERR_PAR_GENERIC_TYPE_NOT_OBJECT]
// Can't name an incomplete type in a generic association.

struct Later;

int value = _Generic(1, struct Later: 1, default: 2);
