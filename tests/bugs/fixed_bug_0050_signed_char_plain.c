// (Test) Compiler error: [ERR_PAR_CONFLICTING_TYPES]
// bug_0050. Plain char and signed char were one type: `char` and
// `signed char` both named `Ast_TypeChar`, so declaring one object with
// each was taken as declaring it twice alike. They are two types, and
// neither is compatible with the other, so the second declaration
// conflicts with the first.
// [C99:6.2.5p15]: char, signed char and unsigned char, the character types
// [C99:6.7p4]:    one object's declarations, of compatible types

extern char        letter;
extern signed char letter;

int main(void)
{
    return 0;
}
