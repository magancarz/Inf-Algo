%{
#include <stdbool.h>

bool print_doc = false;
%}

%x string_mode
%x comment_single_line
%x comment_multi_line
%x docs_single_line
%x docs_multi_lines
 
%%

\#include[[:blank:]].*\n	{ ECHO; }

\"				{ ECHO; BEGIN(string_mode); }
\/\/				BEGIN(comment_single_line);
\/\*				BEGIN(comment_multi_line);
\/\/\/|\/\/!			{ if(print_doc) ECHO; BEGIN(docs_single_line); }
\/\*\*|\/\*!			{ if(print_doc) ECHO; BEGIN(docs_multi_lines); }

<string_mode>{
\\\"				{ECHO;}
\"				{ ECHO; BEGIN(0); }
}

<comment_single_line>{
.				{ };
\n				{ ECHO; BEGIN(0); }
}

<comment_multi_line>{
.				{ };
\*\/				BEGIN(0);
}

<docs_single_line>{
.				if(print_doc) ECHO;
\n				{ ECHO; BEGIN(0); }
}

<docs_multi_lines>{
.				if(print_doc) ECHO;
\*\/				{ if(print_doc) ECHO; BEGIN(0); }
}

%%

int yywrap() {}

int main(int argc, char** argv) {
	if (argc > 1)
		print_doc = true;
	yylex();
}
