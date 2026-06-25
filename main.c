#include <stdio.h>
#include "ast.h"


void printAST(ASTNode* node)
{
    if(node->type == AST_NUMBER)
    {
        NumberNode* num =
            (NumberNode*)node;

        printf("%d",
               num->value);

        return;
    }

    if(node->type == AST_BINARY)
    {
        BinaryNode* bin =
            (BinaryNode*)node;

        printf("(");

        printAST(bin->left);

        switch(bin->op)
        {
            case TOKEN_PLUS:
                printf(" + ");
                break;

            case TOKEN_MINUS:
                printf(" - ");
                break;

            case TOKEN_STAR:
                printf(" * ");
                break;

            case TOKEN_SLASH:
                printf(" / ");
                break;

            default:
                break;
        }

        printAST(bin->right);

        printf(")");
    }
}
void printToken(Token token)
{
    printf("Type=%d  Lexeme=%s  Line=%d\n",
    token.type,
    token.lexeme,
    token.line
);
}

int main(){

    char source[] = "a = b = 5";

    Lexer lexer;
    lexerinit(&lexer, source);

    Parser parser;
    parserInit(&parser, &lexer);

    ASTNode* root =
        parseExpression(&parser);

    if(root != NULL){
        printf("Parsing completed successfully.\n");
    }

    return 0;


}