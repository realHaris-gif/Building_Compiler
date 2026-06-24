#ifndef AST_H
#define AST_H
#include "parser.h"
typedef enum{
    AST_NUMBER,
    AST_BINARY,
    AST_UNARY
} ASTNodeType;

typedef struct ASTNode{
    ASTNodeType type;
} ASTNode;


typedef struct{
    ASTNodeType type;
    TokenType op;
    struct ASTNode* left;
    struct ASTNode* right;

} BinaryNode;

typedef struct
{
    ASTNodeType type;

    TokenType op;

    ASTNode* operand;

} UnaryNode;

typedef struct{
    ASTNodeType type;
    int value;
} NumberNode;

//Prototypes
NumberNode* createNumberNode(int value);
ASTNode* parseNumber(Parser* parser);
BinaryNode* createBinaryNode( TokenType op,  ASTNode* left, ASTNode* right);
ASTNode* parseExpression(Parser* parser);
ASTNode* parseTerm(Parser* parser);
ASTNode* parseFactor(Parser* parser);
ASTNode* parsePrimary(Parser* parser);
UnaryNode*createUnaryNode( TokenType op, ASTNode* operand);
#endif