#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

typedef struct Node
{
    char *value;
    TokenType type;
    struct Node *right;
    struct Node *left;
} Node;

void print_tree(Node *node,int indent,char direction[])
{
    /*
    travel the tree first to he left and them to the right 
    */
    if (node == NULL){
        return;
    }
    for (int i = 0;i < indent;i++){
        printf(" ");
    }
    printf("NODE TYPE: '%d' ",node->type);
    printf("NODE VALUE: '%s' ",node->value);
    printf("NODE DIRECTION: '%s'\n",direction);
    if(node->type == OPERATOR){
    }
    print_tree(node->left,indent + 1,"LEFT");
    print_tree(node->right,indent + 1,"RIGHT");
}

Node *init_node(Node *node,char *value,TokenType type){
    /*
    init a node reserving space to it initializing it and assigning the left and right siblings to null 
    */
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char) * 2);
    node->value = value;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void print_error(char *error_type)
{
    /*
    print the error code
    */
    printf("ERROR: %s\n",error_type);
    exit(1);
}

Token *next_token(Token *current_token)
{
    /*
    increment the pointer taking care that is no END_OF_TOKENS type token
    */

    // printf("\ncurrent token type before next_token function %d",current_token->type);
    // printf("\ncurrent token value before next_token function %s\n",current_token->value);
    Token *temp = current_token;
    temp++;
    // printf("\ntemp type %d\n",temp->type);
    if(temp->type != END_OF_TOKENS){
        current_token++;
    }else{
        // printf
    }
    // printf("\ncurrent token type after next_token function %d",current_token->type);
    // printf("\ncurrent token value after next_token function %s\n",current_token->value);
    return current_token;
}
void token_type_checker(Token *token,TokenType type){
    if(token->type != type){
        print_error("ERROR: Invalid token type");
    }
}
Token *generate_operation_nodes(Node *current,Token *current_token){
    Node *oper_node = malloc(sizeof(Node));
    if(current_token->type == OPERATOR){
        oper_node = init_node(oper_node,current_token->value,OPERATOR);
        current->left->left = oper_node;    //init operator node

        current_token--; //if is operator maybe is because before the operator had a number so decrement the current token
        token_type_checker(current_token,INT);//check if the current node is number
        Node *expr_node = malloc(sizeof(Node));
        expr_node = init_node(expr_node,current_token->value,INT);//1+2+3 guide
        oper_node->left = expr_node;
        current_token+=2;//increment in 2 because the first is the number and the second is an operator so the third maybe is a number too

        token_type_checker(current_token,INT);
        while(current_token->type == INT || current_token->type == OPERATOR){
            if (current_token->type == OPERATOR){
                current_token--;
                token_type_checker(current_token,INT);
                expr_node = init_node(expr_node,current_token->value,INT);
                current_token++;

                Node *oper_node_2 = malloc(sizeof(Node));
                oper_node_2 = init_node(oper_node_2,current_token->value,OPERATOR);
                oper_node->right = oper_node_2;
                oper_node_2->left = expr_node;
                oper_node = oper_node_2;
            }else if (current_token->type == INT){
                expr_node = init_node(expr_node,current_token->value,INT);
                oper_node->right = expr_node;
        }
        current_token++;
        }
    
        // current_token++;            
    }
    
    Token *temp = current_token;
    temp--;
    if(temp->type != INT){
        print_error("Invalid syntax for operator");
    }
    return current_token;
}

Node *parser(Token *tokens)
{
    /*
    the main body of the parser takes a pointer of the tokens array and verify if there are in a correct syntax and build a abstract tree 
    */
    Token *current_token = &tokens[0];
    Node *root = malloc(sizeof(Node));

    root = init_node(root,"PROGRAM",BEGINNING);

    Node *current = root;
    
    while(current_token->type != END_OF_TOKENS)
    {
        if(current == NULL)
        {
            break;
        }

        switch(current_token->type)
        {
            case IDENTIFIER:
                printf("IDENTIFIER\n");
                break;
            case OPERATOR:
                printf("OPERATOR\n");
                break;
            case KEYWORD:
                if(strcmp(current_token->value,"EXIT") == 0){
                    Node *exit_node = malloc(sizeof(Node));
                    exit_node = init_node(exit_node,current_token->value,KEYWORD);
                    root->right = exit_node;
                    current = exit_node;
                    current_token = next_token(current_token);
                    if(strcmp(current_token->value,"(") == 0  && current_token->type == SEPARATOR){
                        Node *open_paren_node = malloc(sizeof(Node));
                        open_paren_node = init_node(open_paren_node,current_token->value,SEPARATOR);
                        current->left = open_paren_node;
                        current_token = next_token(current_token);
                        if(current_token->type == INT){
                            Token *temp = current_token;
                            temp++;
                            if(temp->type == OPERATOR){
                                current_token = next_token(current_token);
                                current_token = generate_operation_nodes(current,current_token);
                            }else{
                                Node *expr_node = malloc(sizeof(Node));
                                expr_node = init_node(expr_node,current_token->value,INT);
                                current->left->left = expr_node;
                                current_token = next_token(current_token);
                            }
                        if(strcmp(current_token->value,")") == 0 && current_token->type == SEPARATOR){
                                Node *close_paren_node = malloc(sizeof(Node));
                                close_paren_node = init_node(close_paren_node,current_token->value,SEPARATOR);
                                current->left->right = close_paren_node;
                                current_token = next_token(current_token);
                                if(strcmp(current_token->value,";") == 0 && current_token->type == SEPARATOR){
                                    Node *semi_node = malloc(sizeof(Node));
                                    semi_node = init_node(semi_node,current_token->value,SEPARATOR);
                                    current->right = semi_node;
                                    break;
                                }else{
                                    print_error("ERROR: Invalid Syntax ON SEMI\n");
                                }
                            }else{
                                print_error("ERROR: Invalid Syntax ON CLOSE PAREN\n");
                            }
                        }else{
                            print_error("ERROR: Invalid Syntax ON NUMBER\n");
                            
                        }
                    }else{
                        print_error("ERROR: Invalid Syntax ON OPEN PAREN\n");
                        
                    }
                }
                break;
            case SEPARATOR:
                printf("SEPARATOR\n");
                break;
            case INT:
                printf("INTEGER\n");
                break;
            case BEGINNING:
                printf("BEGINNING\n");
                break;
            case END_OF_TOKENS:
                printf("END\n");
                break;
        }        
        current_token++;
    }
    print_tree(root,0,"ROOT");
    return root;
}