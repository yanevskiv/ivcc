// (Test) Compiler error: [ERR_SEM_COMPARE_COMPLEX]
// Can't order complex values.

double _Complex a;
double _Complex b;

int f(void)
{
    return a < b;
}
