#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    TOKEN_INT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_RETURN,

    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_ASSIGN,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_EQUAL_EQUAL,
    TOKEN_LESS_THEN,
    TOKEN_LESS_THEN_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_THEN_EQUAL,
    TOKEN_NOT_EQUAL_TO,

    TOKEN_SEMICOLON,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_LBRACE,
    TOKEN_RBRACE,

    TOKEN_COMMA,

    TOKEN_EOF,
    TOKEN_ERROR

} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
} Token;

#endif


