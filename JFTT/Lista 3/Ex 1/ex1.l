%option noyywrap
%{
  #include "ex1b.h"
  int yylex();
%}

%%
^#(.|\\\n)*\n   {}
\\\n            {}
[[:blank:]]+ 	{}
[0-9]+	        { yylval = atoi(yytext); return NUM; }
"+"             { return ADD; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"%"             { return MOD; }
"^"             { return POW; }
\(              { return LT_BR; }
\)              { return RT_BR; }
\n              { return EOL; }
.               { return ERROR; }
%%
