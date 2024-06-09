#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


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

void print_token(Token token,int index)
{
	/*
	print the token index - value and if the token is one of the permited types
	*/
	printf("TOKEN INDEX: ");
	printf("'%d' ",index);
	printf("TOKEN VALUE: ");
	printf("'");
	for(int i=0;token.value[i] != '\0';i++)
	{
		printf("%c",token.value[i]);
	}
	printf("' ");
    switch(token.type){
	case INT:
		printf("TOKEN TYPE: INT\n");
        break;
	case KEYWORD:
		printf("TOKEN TYPE: KEYWORD\n");
        break;
	case OPERATOR:
		printf("TOKEN TYPE: OPERATOR\n");
        break;
	case SEPARATOR:
		printf("TOKEN TYPE: SEPARATOR\n");
        break;
    case END_OF_TOKENS:
		printf("END_OF_TOKENS\n");
        break;
	case IDENTIFIER:
		printf("IDENTIFIER\n");
        break;
    case BEGINNING:
		printf("BEGINNING\n");
        break;
    
    }
}
Token *generate_number(char *current,int *current_index)
{
	/*
	generate a number token reserving space to them and init them while the next character in he file is a number 
	*/
	Token *token = malloc(sizeof(Token));
	token->type = INT;
	char *value = malloc(sizeof(char) * 4);
	int value_index = 0;
	while(isdigit(current[*current_index]) && current[*current_index] != '\0')
	{
		if(!isdigit(current[*current_index]))
		{
			break;
		}
		value[value_index] = current[*current_index];
		value_index++;
		*current_index+=1;	
	}

	if(!isdigit(current[*current_index]))
	{
		*current_index-=1;
	}
	value[value_index] ='\0';
	token->value = value;
	return token;
}

Token *generate_keyword(char *current,int *current_index)
{
	/*
	generate a keyword token reserving space to it and init it 
	*/
	Token *token = malloc(sizeof(Token));
	char *keyword = malloc(sizeof(char) * 4);
	int keyword_index = 0;
	while(isalpha(current[*current_index]) && current[*current_index] != '(' && current[*current_index] != ')')
	{
		keyword[keyword_index] = current[*current_index];
		keyword_index++;
		*current_index+=1;
	}

	if(current[*current_index] == '(' || current[*current_index] == ')')
	{
		*current_index-=1;
	}
	if(strcmp(keyword,"exit"))
	{
		token->type = KEYWORD;
		token->value = "EXIT";
	}

	return token;
}

Token *generate_separator_or_operator(char *current,int *current_index,TokenType type)
{
	/*
	generate a separator or operator token reserving space to them and init them 
	*/
    Token *token = malloc(sizeof(Token));
    token->value = malloc(sizeof(char) * 2);
    token->value[0] = current[*current_index];
    token->value[1] = '\0';
    token->type = type;
    return token;
}
size_t tokens_index;
Token *lexer(FILE *file)
{
	/*
	the body of the lexer file, takes a stream of character and convert it to tokens
	*/
	int length;
	char *current = 0;

	fseek(file,0,SEEK_END); //set te cursor to end
	length = ftell(file);  //read the length of the file
	printf("\nlength file: %d\n",length);
	fseek(file,0,SEEK_SET);//set the cursor to beginning

	current = malloc(sizeof(char) * length); //read all the archive
	fread(current,1,length,file);

	fclose(file);
	
    current[length + 1] = '\0';//set null to end
	int current_index = 0;

	Token *tokens = malloc(sizeof(Token));
	tokens_index = 0;
	while(current[current_index] != '\0')
	{
		Token *token = malloc(sizeof(Token));
		
		if(isalpha(current[current_index]))
		{
			token = generate_keyword(current,&current_index);
			tokens[tokens_index] = *token;
			tokens_index++;
		}
		else if(current[current_index] == '(')
		{
            token = generate_separator_or_operator(current,&current_index,SEPARATOR);
			tokens[tokens_index] = *token;
			tokens_index++;
		}
		else if(current[current_index] == '+' || current[current_index] == '-' || current[current_index] == '*' || current[current_index] == '/')
		{
            token = generate_separator_or_operator(current,&current_index,OPERATOR);
			tokens[tokens_index] = *token;
			tokens_index++;
		}
		else if(isdigit(current[current_index]))
		{
			token = generate_number(current,&current_index);
			tokens[tokens_index] = *token;
			tokens_index++;
		}
		else if(current[current_index] == ')')
		{
            token = generate_separator_or_operator(current,&current_index,SEPARATOR);
			tokens[tokens_index] = *token;
			tokens_index++;
		}
		
		else if(current[current_index] == ';')
		{
            token = generate_separator_or_operator(current,&current_index,SEPARATOR);
			tokens[tokens_index] = *token;
			tokens_index++;
		} 
		if(current[current_index] == '\0')
		{
			break;
		}
		tokens = realloc(tokens, (tokens_index + 1) * sizeof(Token));
		free(token);
		current_index++;

	}
	tokens[tokens_index].value = '\0';
	tokens[tokens_index].type = END_OF_TOKENS;
	printf("tokens index %ld ",tokens_index);
	printf("current index in file counting spaces %d ",current_index);
	printf("last token type %d\n",tokens[tokens_index].type);
	printf("\n------------END OF LEXER FILE------------\n\n");
	return tokens;
}