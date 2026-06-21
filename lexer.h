#include<stdio.h>
#include"token.h"

typedef struct{
 char* source;
 int curr;
}Lexer;


void lexerinit(Lexer* lex,char* source);
char peek(Lexer* lex);
char advance(Lexer* lex);
int atEnd(Lexer* lex);
void skipspace(Lexer* lexer);
Token makeToken(TokenType type,char* lexeme);
Token getToken(Lexer* lexer);