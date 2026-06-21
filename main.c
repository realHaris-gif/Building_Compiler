#include <stdio.h>
#include "lexer.h"


void printToken(Token token)
{
    printf("Type: %d, Lexeme: %s\n",
           token.type,
           token.lexeme);
}

int main()
{
    char source[] = "x = a / b;";

    Lexer lexer;

    lexerinit(&lexer, source);

    Token token;

    do
    {
        token = getToken(&lexer);
        printToken(token);

    } while (token.type != TOKEN_EOF);

    return 0;
}