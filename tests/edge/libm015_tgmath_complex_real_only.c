// (Test) Compiler flags: -lm
// (Test) Compiler error: [ERR_PAR_GENERIC_NO_MATCH]
// A complex argument to a macro of a real function alone is refused: the
// type its argument counts as is a generic selection with no association
// for a complex type and no default.
// Non-standard: ceil of a float complex fails to compile, as gcc's
// __builtin_tgmath refuses it, where it might invoke ceil of the real part.
// Liberty: a complex argument to such a macro is undefined behaviour.
// [C99:7.22p5]: a complex argument to a macro of a real function, undefined

#include <tgmath.h>

int main(void)
{
    float _Complex z = 2.5f;

    return (int) ceil(z);
}
