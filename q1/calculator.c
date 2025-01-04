#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input; // Global input string pointer

// Forward declarations
int expression();
int term();
int factor();

// Consume whitespace
void consume_whitespace() {
    while (isspace(*input)) input++;
}

// Match expected character
void match(char expected) {
    if (*input == expected) {
        input++;
    } else {
        fprintf(stderr, "Error: Unexpected character '%c'\n", *input);
        exit(EXIT_FAILURE);
    }
}

// Parse expressions (handles +)
int expression() {
    int result = term();
    consume_whitespace();
    while (*input == '+') {
        match('+');
        consume_whitespace();
        result += term();
        consume_whitespace();
    }
    return result;
}

// Parse terms (handles *)
int term() {
    int result = factor();
    consume_whitespace();
    while (*input == '*') {
        match('*');
        consume_whitespace();
        result *= factor();
        consume_whitespace();
    }
    return result;
}

// Parse factors (numbers or parenthesized expressions)
int factor() {
    consume_whitespace();
    if (isdigit(*input)) {
        int value = 0;
        while (isdigit(*input)) {
            value = value * 10 + (*input - '0');
            input++;
        }
        return value;
    } else if (*input == '(') {
        match('(');
        int value = expression();
        match(')');
        return value;
    } else {
        fprintf(stderr, "Error: Unexpected character '%c'\n", *input);
        exit(EXIT_FAILURE);
    }
}

// Main function
int main() {
    char buffer[256];
    printf("Enter an arithmetic expression: ");
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    int result = expression();
    printf("Result: %d\n", result);
    return 0;
}

