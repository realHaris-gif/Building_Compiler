#include<stdio.h>
#include"token.h"

typedef struct{
 char* source;
 int curr;
}lexer;


void lexerinit(lexer* lex,char* source);
char peek(lexer* lex);
char advance(lexer* lex);
int atEnd(lexer* lex);