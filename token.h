#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    TOKEN_INT,

    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_ASSIGN,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_SEMICOLON,

    TOKEN_EOF,
    TOKEN_ERROR

} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
} Token;

#endif


