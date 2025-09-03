%{
#include <stdio.h>
int pc = 0, sc = 0;
%}

%%
printf { pc++; printf("writef"); }
scanf  { sc++; printf("readf"); }
.|\n   { putchar(yytext[0]); }
%%

int yywrap() { return 1; }

int main() {
    printf("Enter code (press Ctrl+D to finish):\n");
    yylex();
    printf("\nNo of printf statements = %d\nNo of scanf statements = %d\n", pc, sc);
    return 0;
}
input:
#include <stdio.h>

int main() {
    printf("Hello World\n");
    scanf("%d", &x);
    printf("Value is %d\n", x);
    return 0;
}
