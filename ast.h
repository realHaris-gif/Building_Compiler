#ifndef AST_H
#define AST_H
#include "parser.h"
typedef enum{
    AST_NUMBER,
    AST_BINARY,
    AST_UNARY,
    AST_VARIABLE,
    AST_ASSIGNMENT,
    AST_EXPRESSION_STATEMENT,
    AST_PROGRAM
} ASTNodeType;

typedef struct ASTNode{
    ASTNodeType type;
} ASTNode;

typedef struct{
    ASTNodeType type;
    char* name;
    ASTNode* value;

} AssignmentNode;

typedef struct StatementNode{
    ASTNodeType type;
} StatementNode;

typedef struct{
    ASTNodeType type;
    ASTNode* expression;
}ExpressionStatementNode;


typedef struct{
    ASTNodeType type;
    StatementNode** statements;
    int statementCount;
}ProgramNode;



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

typedef struct{
    ASTNodeType type;
    char* name;
} VariableNode;

//Prototypes

ASTNode* parseExpression(Parser* parser);
ASTNode* parseTerm(Parser* parser);
ASTNode* parseFactor(Parser* parser);
ASTNode* parsePrimary(Parser* parser);
ASTNode* parseNumber(Parser* parser);
ASTNode* parseAssignment(Parser* parser);
ASTNode* parseAdditive(Parser* parser);
ASTNode* parseExpression(Parser* parser);
StatementNode* parseStatement(Parser* parser);

NumberNode* createNumberNode(int value);
BinaryNode* createBinaryNode( TokenType op,  ASTNode* left, ASTNode* right);
UnaryNode*createUnaryNode( TokenType op, ASTNode* operand);
VariableNode* createVariableNode(char* variableName);
ExpressionStatementNode* createExpressionStatementNode(ASTNode* expression);
ProgramNode* createProgramNode();
void addStatement(ProgramNode* program,StatementNode* statement);
ProgramNode* parseProgram(Parser* parser);
#endif