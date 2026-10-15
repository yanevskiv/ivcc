// (Test) Compiler error: [ERR_GEN_INIT_COMPLEX_NOT_CONSTANT]
// Can't initialize a file-scope complex object with a run-time value.

double x;
double _Complex z = x;
