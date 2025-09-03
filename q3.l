%{
#include <stdio.h>
int com = 0;
%}

%s COMMENT

%%
"/*"             { BEGIN(COMMENT); }
<COMMENT>[^*]*   { /* stay in comment */ }
<COMMENT>"*/"    { BEGIN(INITIAL); com++; }
"//".*           { com++; }      // single-line comment
\n               { /* ignore newline */ }
.                { /* ignore other chars */ }
%%

int yywrap() { return 1; }

int main() {
    printf("Enter code (press Ctrl+D to end):\n");
    yylex();
    printf("Number of comment lines = %d\n", com);
    return 0;
}
