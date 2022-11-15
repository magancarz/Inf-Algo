%{
    #include <stdio.h>
    
    int yylex();
    int yywrap();

    int docs = 0;
%}

%x comment_mode
%x documentation
%x string_mode

%%

\#include[[:blank:]].*\n           	{printf(yytext);};

\"                      		{printf(yytext); BEGIN(string_mode);};
<string_mode>.				{printf(yytext);};
<string_mode>(\\\n)*\"			{printf(yytext); BEGIN(0);};

\/(\\\n)*\/(\/|!)((\\\n)|.)*         	{if (docs) printf(yytext);};
\/(\\\n)*\/((\\\n)|.)*            	{};

\/\*(\*|!)      			{if (docs) printf(yytext); BEGIN(documentation);};
<documentation>.|\n			{if(docs) printf(yytext);};
<documentation>(\\\n)*\*(\\\n)*\/	{if(docs) printf(yytext); BEGIN(0);};

(\\\n)*\/(\\\n)*\*         		{BEGIN(comment_mode);};
<comment_mode>.|\n			{};
<comment_mode>(\\\n)*\*(\\\n)*\/	{BEGIN(0);};

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        docs = 1;
    }
    return yylex();
}
