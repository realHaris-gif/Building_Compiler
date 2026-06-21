#include "lexer.h"
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


void lexerinit(Lexer* lex,char* source){
    lex->source = source;
    lex->curr = 0;
}
char peek(Lexer* lex){
    return lex->source[lex->curr];
}
char advance(Lexer* lex){
    return lex->source[lex->curr++];
}
int atEnd(Lexer* lex){
    return peek(lex)=='\0'; 
}

void skipspace(Lexer *lexer){
     while (!atEnd(lexer) &&
           isspace(lexer->source[lexer->curr])){
        lexer->curr++;
    }
}

Token makeToken(TokenType type, char* lexeme){
    Token t;
    t.type = type;
    t.lexeme = malloc(sizeof(lexeme+1));
    strcpy(t.lexeme,lexeme);
    return t;
}

Token getToken(Lexer *lexer)
{
    skipspace(lexer);

    if (atEnd(lexer))
    {
        return makeToken(TOKEN_EOF, "EOF");
    }

    char c = advance(lexer);
    
    switch (c)
    {
        case '+':
            return makeToken(TOKEN_PLUS, "+");

        case '-':
            return makeToken(TOKEN_MINUS, "-");

        case '*':
            return makeToken(TOKEN_STAR, "*");

        case '/':
            return makeToken(TOKEN_SLASH, "/");

        case '=':
            return makeToken(TOKEN_ASSIGN, "=");

        case ';':
            return makeToken(TOKEN_SEMICOLON, ";");
    }

    return makeToken(TOKEN_ERROR, "UNKNOWN");
}