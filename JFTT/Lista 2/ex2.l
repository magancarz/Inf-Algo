%{
#include <stdio.h>
#include <stdbool.h>

int yywrap();
int yylex();
int lines_count = 0;
int words_count = 0;

bool shebang = false;
void shebang_found() {
    shebang = true;
}

%}

%x string_mode
%x documentation
%%
#!.*\n                          {if(!shebang) {printf(yytext); shebang_found();};};

.?((\"\")|(\'\'))               {printf(yytext);};

[^\\][\"\']{3}                  {printf(yytext); BEGIN(documentation);};
<documentation>[^\\][\"\']{3}   {printf(yytext); BEGIN(0);};

[^\\][\"\']                     {printf(yytext); BEGIN(string_mode);};
<string_mode>[^\\][\"\']        {printf(yytext); BEGIN(0);};

#.*\n?                          {};

%%
int yywrap() {
    return 1;
}

int main() {
    return yylex();
}
