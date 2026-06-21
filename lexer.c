#include "lexer.h"
#include<stdbool.h>



void lexerinit(lexer* lex,char* source){
    lex->source = source;
    lex->curr = '\0';
}
char peek(lexer* lex){
    return lex->source[lex->curr];
}
char advance(lexer* lex){
    return lex->source[lex->curr++];
}
int atEnd(lexer* lex){
    return lex->source[lex->curr]=='\0'; 
}
