#ifndef PARSER_H
#define PARSER_H
#include"lexer.h"
typedef struct{
    Lexer* lexer;
    Token current;
    Token next;

}Parser;

void parserInit(Parser* parser, Lexer* lexer);
int match(Parser* parser, TokenType expected);
void advanceParser(Parser* parser);
void consume(Parser* parser, TokenType expected);

#endif