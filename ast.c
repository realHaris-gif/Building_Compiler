#include <stdlib.h>
#include "ast.h"


NumberNode* createNumberNode(int value){
    NumberNode* node =  malloc(sizeof(NumberNode));
    node->type = AST_NUMBER;
    node->value = value;
    return node;
}

ASTNode* parseNumber(Parser* parser){
    int value = atoi(parser->current.lexeme);

    //Consume the Number
    consume(parser, TOKEN_NUMBER);

    return (ASTNode*) createNumberNode(value);
}