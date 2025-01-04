%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(const char *s);
%}

%token NUMBER

%%
input : /* Empty */
      | input expr '\n' { /* Do nothing; allows multiple expressions */ }
      ;

expr : expr '+' term { printf("Result: %d\n", $1 + $3); }
     | expr '-' term { printf("Result: %d\n", $1 - $3); }
     | term
     ;

term : NUMBER
     ;
%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

