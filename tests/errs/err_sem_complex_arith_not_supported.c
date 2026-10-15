// (Test) Compiler error: [ERR_SEM_COMPLEX_ARITH_NOT_SUPPORTED]
// Can't add complex values yet.
// Note: gcc adds them.

double _Complex a;
double _Complex b;

void f(void)
{
    a = a + b;
}
