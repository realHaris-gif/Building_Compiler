#include"lexer.h"
typedef struct{
    Lexer* lexer;
    Token current;

}Parser;

void parserInit(Parser* parser, Lexer* lexer);
int match(Parser* parser, TokenType expected);
char advanceParser(Parser* parser);
void consume(Parser* parser, TokenType expected);
