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
#!.*\n                          {if(!shebang) {ECHO; shebang_found();}}

.?((\"\")|(\'\'))               {ECHO;}

[^\\][\"\']{3}                  {ECHO; BEGIN(documentation);};
<documentation>[^\\][\"\']{3}   {ECHO; BEGIN(0);};

[^\\][\"\']                     {ECHO; BEGIN(string_mode);};
<string_mode>[^\\][\"\']        {ECHO; BEGIN(0);};

#.*\n?                          {};

%%
int yywrap() {
    return 1;
}

int main() {
    return yylex();
}
