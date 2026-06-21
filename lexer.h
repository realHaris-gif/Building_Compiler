#include<stdio.h>
#include"token.h"

typedef struct{
 char* source;
 int curr;
}lexer;


void lexerinit(lexer* lex,char* source);
void peek(lexer* lex);
void advance(lexer* lex);
void atEnd(lexer* lex);