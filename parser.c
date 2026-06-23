#include "parser.h"
#include<stdlib.h>
void parserInit(Parser* parser, Lexer* lexer){
    parser->lexer = lexer;
    parser->current = getToken(lexer);
}

int match(Parser* parser, TokenType expected){
    if(parser->current.type!=expected) return 0;

    advanceParser(parser);

    return 1;
}

void advanceParser(Parser* parser){
     parser->current = getToken(parser->lexer);
}

void consume(Parser* parser, TokenType expected){
    if(parser->current.type != expected){
        printf( "Parser Error at line %d\n",
            parser->current.line
        );
        exit(1);
    }
    advanceParser(parser);
}