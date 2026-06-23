#ifndef AST_H
#define AST_H
#include "parser.h"
typedef enum{
    AST_NUMBER
} ASTNodeType;

typedef struct ASTNode{
    ASTNodeType type;
} ASTNode;

typedef struct{
    ASTNodeType type;
    int value;
} NumberNode;

//Prototypes
NumberNode* createNumberNode(int value);
ASTNode* parseNumber(Parser* parser);
#endif