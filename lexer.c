#include "lexer.h"
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


void lexerinit(Lexer* lex, char* source){
    lex->source = source;
    lex->curr = 0;
    lex->line = 1;
}
char peek(Lexer* lex){
    return lex->source[lex->curr];
}
char advance(Lexer* lex){
    char c = lex->source[lex->curr++];

    if(c == '\n')  lex->line++;
    
    return c;
}


char lookAhead(Lexer* lex){
    if(lex->source[lex->curr+1]!= '\0'){
        return lex->source[lex->curr+1];
    }
    else return '\0';
}
int atEnd(Lexer* lex){
    return peek(lex)=='\0'; 
}

void skipspace(Lexer *lexer){
    while (!atEnd(lexer) &&  isspace(peek(lexer))){
        advance(lexer);
    }
}
void skipBlockComment(Lexer *lexer){
    while (!atEnd(lexer)){
        if (peek(lexer) == '*' &&
            lookAhead(lexer) == '/'){
            advance(lexer);
            advance(lexer);

            return;
        }

        advance(lexer);
    }
}
void skipLineComment(Lexer *lexer){
    while (!atEnd(lexer) && peek(lexer) != '\n'){
        advance(lexer);
    }
}

Token makeToken(Lexer *lex,TokenType type,char *lexeme){
    Token t;
    t.type = type;
    t.line = lex->line;
    t.lexeme = malloc(strlen(lexeme) + 1);
    strcpy(t.lexeme, lexeme);
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
    return makeToken(lex,TOKEN_NUMBER,buffer);
}

Token scanString(Lexer *lexer){
    char buffer[256];
    int i = 0;
    while (!atEnd(lexer) && peek(lexer) != '"'){
        buffer[i++] = advance(lexer);
    }

    if (atEnd(lexer)){
        return makeToken(lexer,TOKEN_ERROR, "Unterminated String");
    }

    advance(lexer);
    buffer[i] = '\0';

    return makeToken(lexer,TOKEN_STRING, buffer);
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
    return makeToken(lex,type,buffer);
}


Token getToken(Lexer *lexer){
    
    skipspace(lexer);

    if (atEnd(lexer)) {
        return makeToken(lexer,TOKEN_EOF, "EOF");
    }

    if(isdigit(peek(lexer))){
        return scanNumber(lexer);
    }

    if(isalnum(peek(lexer))){
        return scanIdentifier(lexer);
    }
    if (peek(lexer) == '"'){
    advance(lexer);
    return scanString(lexer);
    }
    char c = advance(lexer);
    
    switch (c) {
        case '+':
            return makeToken(lexer,TOKEN_PLUS, "+");

        case '-':
            return makeToken(lexer,TOKEN_MINUS, "-");

        case '*':
            return makeToken(lexer,TOKEN_STAR, "*");

       case '/':
             if (peek(lexer) == '/'){
                advance(lexer);
                skipLineComment(lexer);
                return getToken(lexer);
                }
            if (peek(lexer) == '*'){
                advance(lexer);

                skipBlockComment(lexer);

                return getToken(lexer);
            }
            return makeToken(lexer,TOKEN_SLASH, "/");

        case '=':
        if(peek(lexer) == '='){
            advance(lexer);
            return makeToken(lexer,TOKEN_EQUAL_EQUAL, "==");
        }
        return makeToken(lexer,TOKEN_ASSIGN, "=");

        case ';':
            return makeToken(lexer,TOKEN_SEMICOLON, ";");
        
        case '>':
            if(peek(lexer)=='='){
             advance(lexer);
             return makeToken(lexer,TOKEN_GREATER_THEN_EQUAL, ">=");}
        
            else  return makeToken(lexer,TOKEN_GREATER, ";");
        case '<':
        if(peek(lexer)=='=') {
            advance(lexer);
            return makeToken(lexer,TOKEN_LESS_THEN_EQUAL, "<=");}
            else  return makeToken(lexer,TOKEN_LESS_THEN, "<=");
        case '!':
        if(peek(lexer)=='='){ 
            advance(lexer);
            return makeToken(lexer,TOKEN_NOT_EQUAL_TO, "!=");}
            else  return makeToken(lexer,TOKEN_ERROR, "UNKNOWN");

        case '(':
            return makeToken(lexer,TOKEN_LPAREN, "(");

        case ')':
            return makeToken(lexer,TOKEN_RPAREN, ")");

        case '{':
            return makeToken(lexer,TOKEN_LBRACE, "{");

        case '}':
            return makeToken(lexer,TOKEN_RBRACE, "}");

         case ',':
            return makeToken(lexer,TOKEN_COMMA, ",");
    }

    return makeToken(lexer,TOKEN_ERROR, "UNKNOWN");
}