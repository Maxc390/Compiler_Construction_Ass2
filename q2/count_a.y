%{
#include <stdio.h>
#include <stdlib.h>

int yylex();        // Declare yylex
int yyerror(const char *s);  // Declare yyerror
int count = 0;      // Declare and initialize counter for 'a'
%}

%token A B

%%
S : A S { count++; }
  | B
  ;
%%

int main() {
    printf("Enter a string: ");
    yyparse();  // Start parsing the input
    printf("Number of 'a's: %d\n", count);
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

