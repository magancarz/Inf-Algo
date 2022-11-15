%{
#include <stdio.h>
#include <string.h>

int yywrap();
int yylex();
int lines_count = 1;
int words_count = 0;
%}
%%
^[[:blank:]]+(\n)? {};
[[:blank:]]+(\n)?$     {};
[[:blank:]]+      {printf(" ");};

[a-zA-Z]+                     {printf(yytext); words_count++;};
\n                            {printf("\n"); lines_count++;};
%%
int yywrap() {
    return 1;
}

int main() {
    yylex();

    printf("\nlines count: %d\nwords count: %d\n", lines_count, words_count);
    return 0;
}
