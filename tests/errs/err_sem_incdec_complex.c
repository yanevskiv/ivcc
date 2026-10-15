// (Test) Compiler error: [ERR_SEM_INCDEC_COMPLEX]
// Can't increment a complex value.
// Note: gcc takes it, and refuses it only with -pedantic-errors.

double _Complex z;

void f(void)
{
    z++;
}
