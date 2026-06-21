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

TokenType checkKeyword(const char *lexeme){
    if (strcmp(lexeme, "int") == 0)
        return TOKEN_INT;

    if (strcmp(lexeme, "if") == 0)
        return TOKEN_IF;

    if (strcmp(lexeme, "else") == 0)
        return TOKEN_ELSE;

    if (strcmp(lexeme, "while") == 0)
        return TOKEN_WHILE;

    if (strcmp(lexeme, "return") == 0)
        return TOKEN_RETURN;

    return TOKEN_IDENTIFIER;
}

Token scanNumber(Lexer* lex){
    char buffer[100];
    int i = 0;
    while(!atEnd(lex) && isdigit(peek(lex))){
        buffer[i++] = advance(lex);
    }
    buffer[i] = '\0';
    return makeToken(TOKEN_NUMBER,buffer);
}


Token scanIdentifier(Lexer* lex){
    char buffer[100];
    int i=0;
    while (
        !atEnd(lex) &&
        (isalnum(peek(lex)) || peek(lex) == '_')
    ){
        buffer[i++] = advance(lex);
    }
    buffer[i] = '\0';
    TokenType type = checkKeyword(buffer);
    return makeToken(type,buffer);
}
Token getToken(Lexer *lexer){
    skipspace(lexer);

    if (atEnd(lexer)) {
        return makeToken(TOKEN_EOF, "EOF");
    }

    

    if(isdigit(peek(lexer))){
        return scanNumber(lexer);
    }

    if(isalnum(peek(lexer))){
        return scanIdentifier(lexer);
    }

    char c = advance(lexer);
    
    switch (c) {
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