#include <stdio.h>

#include "ast_printer.h"

void printProgram(ProgramNode* program)
{
    printf("Program\n");

    for(int i = 0; i < program->statementCount; i++)
    {
        printf("Statement %d\n", i + 1);

        printStatement(program->statements[i]);

        printf("\n");
    }
}

void printStatement(StatementNode* statement)
{
    switch(statement->type)
    {
        case AST_EXPRESSION_STATEMENT:
        {
            ExpressionStatementNode* node =
                (ExpressionStatementNode*)statement;

            printf("Expression Statement\n");

            printAST(node->expression);

            break;
        }

        default:
        {
            printf("Unknown Statement\n");
            break;
        }
    }
}

void printAST(ASTNode* node)
{
    switch(node->type)
    {
        case AST_NUMBER:
        {
            NumberNode* number =
                (NumberNode*)node;

            printf("Number : %d\n",
                   number->value);

            break;
        }

        case AST_VARIABLE:
        {
            VariableNode* variable =
                (VariableNode*)node;

            printf("Variable : %s\n",
                   variable->name);

            break;
        }

        case AST_UNARY:
        {
            UnaryNode* unary =
                (UnaryNode*)node;

            printf("Unary\n");

            printf("Operator : %d\n",
                   unary->op);

            printAST(unary->operand);

            break;
        }

        case AST_BINARY:
        {
            BinaryNode* binary =
                (BinaryNode*)node;

            printf("Binary\n");

            printf("Operator : %d\n",
                   binary->op);

            printf("Left\n");

            printAST(binary->left);

            printf("Right\n");

            printAST(binary->right);

            break;
        }

        case AST_ASSIGNMENT:
        {
            AssignmentNode* assignment =
                (AssignmentNode*)node;

            printf("Assignment\n");

            printf("Variable : %s\n",
                   assignment->name);

            printf("Value\n");

            printAST(assignment->value);

            break;
        }

        default:
        {
            printf("Unknown AST Node\n");
            break;
        }
    }
}