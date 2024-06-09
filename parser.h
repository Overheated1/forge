#ifndef PARSER_H_
#define PARSER_H_

typedef struct Node{
    char *value;
    TokenType type;
    struct Node *right;
    struct Node *left;
} Node;


Token *next_token(Token *current_token);
void print_error(char *error_type);
void print_tree(Node *node);
Node *init_node(Node *node,char *value,TokenType type);
Node *parser(Token *tokens);

#endif 