%{

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int yylex (void);
int yyerror (char const *);
int p1 = 1234577;
int p2 = 1234576;

bool error = false;
char postfix[256];

void print_err (char *err) {
    printf("Error: %s\n", err);
    error = true;
}

int fix(long long a, int P) {
    if(a < 0) return P + a % P;
    else return a % P;
}

int inverse(long long a, long long P) {
	int m = P;
	int x = 1;
	int y = 0;
	
	while(a > 1) {
		int quotient = a / m;
		int t = m;
		
		m = a % m;
		a = t;
		t = y;
		
		y = x - quotient * y;
		x = t;
	}
	
	if(x < 0) x += P;
	
	return x;
}

int add(int a, int b, int P) {
    return fix(a + b, P);
}

int sub(int a, int b, int P) {
    return fix(a - b, P);
}

int mul(int a, int b, int P) {
    return fix(a * b, P);
}

int divide(long long a, long long b, int P) {
    return fix(a * inverse(b, P), P);
}

int mod(int a, int b, int P) {
    return fix(a % b, P);
}

int power(int a, int b, int P) {
    int ans = 1;
    for(int i = 0; i < b; i++) {
        ans *= a;
        ans %= P;
    }
    return fix(ans, P);
}




%}

%token NUM RT_BR LT_BR
%left ADD SUB
%left MUL DIV MOD
%nonassoc POW
%precedence NEG
%token EOL ERROR

%% 

input:
  %empty
  | input line
;


line:
  exp EOL  { if(!error) printf ("%s\n= %d \n\n", postfix, $1); error = false; memset(postfix, 0, strlen(postfix));}
  | error EOL {printf("ERROR\n\n"); error = false; memset(postfix, 0, strlen(postfix));}
;


exp:      NUM                       { $$ = fix($1, p1); char *s; sprintf(s, "%d", fix($1, p1)); strcat(postfix, s); strcat(postfix," ");}
        | SUB NUM                 { $$ = fix(-$2, p1);  char *s; sprintf(s, "%d", fix(-$2, p1)); strcat(postfix, s); strcat(postfix, " ");}
        | SUB LT_BR exp RT_BR     { $$ = fix(-$3, p1); strcat(postfix, "~ ");}
        | LT_BR exp RT_BR  { $$ = $2; }
        | exp ADD exp     { $$ = add($1, $3, p1); strcat(postfix, "+ "); }
        | exp SUB exp    { $$ = sub($1, $3, p1); strcat(postfix, "- "); }
        | exp MUL exp     { $$ = mul($1, $3, p1); strcat(postfix, "* "); }
        | exp DIV exp      { if($3 == 0) {print_err("Division by zero");} else {$$ = divide($1, $3, p1); strcat(postfix, "/ ");}}
        | exp POW pow_exp   { $$ = power($1, $3, p1); strcat(postfix, "^ ");}
;

pow_exp:  NUM                      { $$ = fix($1, p2); char *s; sprintf(s, "%d", fix($1, p2)); strcat(postfix, s); strcat(postfix, " ");}
        | SUB NUM                { $$ = fix(-$2, p2); char *s; sprintf(s, "%d", fix(-$2, p2)); strcat(postfix, s); strcat(postfix, " ");}
        | SUB LT_BR pow_exp RT_BR    { $$ = fix(-$3, p2); strcat(postfix, "~ ");}
        | LT_BR pow_exp RT_BR          { $$ = $2; }
        | pow_exp ADD pow_exp       { $$ = add($1, $3, p2); strcat(postfix, "+ "); }
        | pow_exp SUB pow_exp      { $$ = sub($1, $3, p2); strcat(postfix, "- "); } 
        | pow_exp MUL pow_exp       { $$ = mul($1, $3, p2); strcat(postfix, "* "); }
        | pow_exp DIV pow_exp        { if($3 == 0) {print_err("Division by zero");} else {$$ = divide($1, $3, p2); strcat(postfix, "/ ");}}
;
%%

int yyerror(char const *s){return 1;}

int main()
{
    strcpy(postfix, "");
    yyparse();
    return 0;
    
}
