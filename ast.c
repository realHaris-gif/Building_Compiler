#include <stdlib.h>
#include "ast.h"
#include <string.h>

NumberNode* createNumberNode(int value){
    NumberNode* node =  malloc(sizeof(NumberNode));
    node->type = AST_NUMBER;
    node->value = value;
    return node;
}
UnaryNode*createUnaryNode( TokenType op,  ASTNode* operand){
    UnaryNode* node =
        malloc(sizeof(UnaryNode));

    node->type = AST_UNARY;
    node->op = op;
    node->operand = operand;

    return node;
}

ASTNode* parseNumber(Parser* parser){
    int value = atoi(parser->current.lexeme);

    //Consume the Number
    consume(parser, TOKEN_NUMBER);

    return (ASTNode*) createNumberNode(value);
}

BinaryNode* createBinaryNode( TokenType op,  ASTNode* left, ASTNode* right){
    BinaryNode* node = malloc(sizeof(BinaryNode));

    node->type = AST_BINARY;
    node->op = op;
    node->left = left;
    node->right = right;

    return node;
}

AssignmentNode* createAssignmentNode(char* name,ASTNode* value){
    AssignmentNode* node = malloc(sizeof(AssignmentNode));
    node->type = AST_ASSIGNMENT;
    node->name = malloc(strlen(name) + 1);
    strcpy(node->name,name);
    node->value = value;
    return node;
}

VariableNode* createVariableNode(char* variableName){
    VariableNode* node = malloc(sizeof(VariableNode));
    
    node->type = AST_VARIABLE;
    node->name = malloc(strlen(variableName) + 1);;
    strcpy(node->name,variableName);
    return node;

}

ASTNode* parseIdentifier(Parser* parser){
    VariableNode* node = createVariableNode(parser->current.lexeme);
    consume(parser, TOKEN_IDENTIFIER);
    return (ASTNode*)node;
}
ASTNode* parsePrimary(Parser* parser){
    if(parser->current.type == TOKEN_NUMBER) {
        return parseNumber(parser);
    }
     if(parser->current.type == TOKEN_IDENTIFIER){
        return parseIdentifier(parser);
    }

     if(parser->current.type == TOKEN_LPAREN){
        consume(parser, TOKEN_LPAREN);

        ASTNode* expr = parseExpression(parser);

        consume(parser, TOKEN_RPAREN);

        return expr;
    }
    printf("Expected number\n");
    exit(1);
}


ASTNode* parseFactor(Parser* parser){
    if(parser->current.type == TOKEN_PLUS){
        consume(parser, TOKEN_PLUS);

        ASTNode* operand = parseFactor(parser);

        return (ASTNode*)createUnaryNode( TOKEN_PLUS,operand);
    }

    if(parser->current.type == TOKEN_MINUS) {
        consume(parser, TOKEN_MINUS);

        ASTNode* operand = parseFactor(parser);

        return (ASTNode*)createUnaryNode(TOKEN_MINUS,operand);
    }
    return parsePrimary(parser);
}



ASTNode* parseTerm(Parser* parser)
{
    ASTNode* left = parseFactor(parser);

    while(parser->current.type == TOKEN_STAR ||
          parser->current.type == TOKEN_SLASH){
        TokenType op = parser->current.type;

        advanceParser(parser);

        ASTNode* right = parseFactor(parser);

        left = (ASTNode*) createBinaryNode(op,left,right);
    }

    return left;
}

ASTNode* parseAdditive(Parser* parser){
    ASTNode* left = parseTerm(parser);

    while(parser->current.type == TOKEN_PLUS ||
          parser->current.type == TOKEN_MINUS){
        TokenType op = parser->current.type;

        advanceParser(parser);

        ASTNode* right = parseTerm(parser);

        left = (ASTNode*) createBinaryNode(op,left,right);
    }

    return left;
}

ASTNode* parseAssignment(Parser* parser){
    if( parser->current.type == TOKEN_IDENTIFIER &&
        parser->next.type == TOKEN_ASSIGN) {
        char* name =parser->current.lexeme;

        consume(parser, TOKEN_IDENTIFIER);
        consume(parser, TOKEN_ASSIGN);


        ASTNode* value = parseAssignment(parser);

        return (ASTNode*)  createAssignmentNode( name,value);
    }

    return parseAdditive(parser);
}

ASTNode*parseExpression(Parser* parser){
    return parseAssignment(parser);
};