#include "parser.h"
#include<stdlib.h>
void parserInit(Parser* parser, Lexer* lexer){
    parser->lexer = lexer;
    parser->current = getToken(lexer);
    parser->next = getToken(lexer);
}

int match(Parser* parser, TokenType expected){
    if(parser->current.type!=expected) return 0;

    advanceParser(parser);

    return 1;
}

void advanceParser(Parser* parser){
     parser->current = parser->next;
    parser->next = getToken(parser->lexer);
}

   void consume(Parser* parser, TokenType expected){

    if(parser->current.type == expected){
        advanceParser(parser);
        return;
    }

    printf(
        "Parser Error at line %d\n",
        parser->current.line
    );

    exit(1);
}