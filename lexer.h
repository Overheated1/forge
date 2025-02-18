#ifndef LEXER_H_
#define LEXER_H_

typedef enum 
{
	BEGINNING,
	INT,
	KEYWORD,
	OPERATOR,
	SEPARATOR,
	IDENTIFIER,
	END_OF_TOKENS,
} TokenType;

typedef struct 
{
	TokenType type;
	char *value;
} Token;


void print_token(Token token,int index);
Token *generate_number(char *current,int *current_index);
Token *generate_keyword(char *current,int *current_index);
Token *generate_separator_or_operator(char *current,int *current_index,TokenType type);
Token *lexer(FILE *file);
#endif