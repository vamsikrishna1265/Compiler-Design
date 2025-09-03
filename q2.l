%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
int space_count = 0;
int line_count = 0;
%}

%%

[ \t]+           { space_count += yyleng; char_count += yyleng; }
\n               { line_count++; char_count++; }
[A-Za-z0-9_]+    { word_count++; char_count += yyleng; }
.                { char_count++; }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            perror("File opening failed");
            return 1;
        }
        yyin = fp;
    }

    yylex();  // Start scanning

    printf("\nCharacter Count: %d\n", char_count);
    printf("Word Count     : %d\n", word_count);
    printf("Space Count    : %d\n", space_count);
    printf("Line Count     : %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}

