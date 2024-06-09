#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "lexer.h"
#include "parser.h"

char current_oper[] = "mov";
void get_operation(char operation[]){
    /*
    makes a string copy in the current operation to with the help of the 
    macros do the operation in less code lines and complexity 
    */
    if(strcmp(operation,"+") == 0){
        strcpy(current_oper,"add");
    }
    if(strcmp(operation,"-") == 0){
        strcpy(current_oper,"sub");
    }
    if(strcmp(operation,"*") == 0){
        strcpy(current_oper,"mpl");
    }
    if(strcmp(operation,"/") == 0){
        strcpy(current_oper,"dvi");
    }
}
void traverse_tree(Node *node,int is_left,FILE *file){
    if(node == NULL){
        return;
    }
    if(strcmp(node->value, "EXIT") == 0){
        fprintf(file,"    mov rax,60\n");
    }
    if(strcmp(node->value, "(") == 0){
    }
    if(strcmp(node->value, ")") == 0){
    }
    printf("\nvalue %s\n",node->value);
    printf("type %d\n",node->type);
    if(node->type == OPERATOR){
        get_operation(node->value);
        if(strcmp(current_oper,"*") == 0 || strcmp(current_oper,"/") == 0){
            fprintf(file,"    mov rdi,1\n");
        }
        fprintf(file,"    %s rdi,%s\n",current_oper,node->left->value);
            while(node->right->type == OPERATOR){
                node = node->right;
                fprintf(file,"    %s rdi,%s\n",current_oper,node->left->value);
                get_operation(node->value);
                if(node->right->type == INT){
                    fprintf(file,"    %s rdi,%s\n",current_oper,node->right->value);
                }
            }
    }
    if(node->type == INT){
        printf("value -- '%s'",node->value);
        fprintf(file,"    %s rdi,%s\n",current_oper,node->value);//atoi ascii to int
    }
    if(strcmp(node->value, ";") == 0){
        fprintf(file,"    syscall");//atoi ascii to int
    }
    if(is_left){    
        // printf
    }else{

    }
    for(size_t i = 0;node->value[i] != '\0';i++){
        printf("%c",node->value[i]);
    }
    printf("\n");
    traverse_tree(node->left,1,file);
    traverse_tree(node->right,0,file);
}
int generate_code(Node *root){
    char code[] = 
    "%macro mpl 2\n"
    "mov rax, %2\n"
    "imul %1    \n"
    "mov  %1, rax\n"
    "mov rax,60\n"
    "%endmacro\n"
    "%macro dvi 2\n"
    "mov rax, %2\n"
    "idiv %1    \n"
    "mov  %1, rax\n"
    "mov rax,60\n"
    "%endmacro\n"
    "section .data\n"
    "section .text\n"
    "global _start\n"
    "  _start:\n";
    FILE *file = fopen("./generated_code/generated_asm.asm","w");
    assert(file != NULL && "FILE COULD NOT BE OPENED");
    fprintf(file,"%s",code);
    traverse_tree(root,0,file);
    fclose(file);
    return 0;
}