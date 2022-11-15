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

\#include[[:blank:]].*\n               	{ printf(yytext); }
\"                      				{ printf(yytext); BEGIN(string_mode); }
\/(\\\n)*\/(\/|!)((\\\n)|.)*         	{ if (docs) printf(yytext); }
\/(\\\n)*\/((\\\n)|.)*            		{ };
\/\*(\*|!)      						{ if (docs) printf(yytext); BEGIN(documentation); }
(\\\n)*\/(\\\n)*\*         				{ BEGIN(comment_mode); }

<string_mode>{
(\\\n)*\"     							{ printf(yytext); BEGIN(0); }
.                       				{ printf(yytext); }
}

<documentation>{
.|\n                    				{ if(docs) printf(yytext); }
(\\\n)*\*(\\\n)*\/        				{ if(docs) printf(yytext); BEGIN(0); }
}

<comment_mode>{
.|\n                    				{ };
(\\\n)*\*(\\\n)*\/        				{ BEGIN(0); }
}

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
