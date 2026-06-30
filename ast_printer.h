#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "ast.h"

void printProgram(ProgramNode* program);
void printStatement(StatementNode* statement);
void printAST(ASTNode* node);

#endif