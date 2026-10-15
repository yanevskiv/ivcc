// (Test) Status: 200
// A file-scope _Bool initialized from a complex constant, converted as by
// assignment with no cast written.
// Standard: the conversion folds, 1 when either part is nonzero.
// Unlike: gcc 14 refuses it as not constant, so no language test holds this.
// [C99:6.3.1.2p1]: a scalar converted to _Bool, 0 if it compares equal to 0
// [C99:6.6p7]:     an initializer's constants, arithmetic ones among them

_Bool half = (double _Complex) 0.5;
_Bool zero = (float _Complex) 0;
_Bool small = (long double _Complex) 1e-4000L;

int main(void)
{
    if (half != 1) return 1;
    if (zero != 0) return 2;
    if (small != 1) return 3;
    return 200;
}
