#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "code_generator.h"

int main(int argc,char *argv[]){
	if(argc < 2){
		printf("ERROR: correct syntax: %s <filename.frg>\n",argv[0]);
		exit(1);
	}

	FILE *file;
	file = fopen(argv[1],"r");

	if(!file){
		printf("ERROR: File not found\n");
		exit(1);
	}
	Token *tokens = lexer(file);
	printf("\n------------PRINTING GENERATED TOKENS FOR THE LEXER------------\n\n");
	for(size_t i =0;tokens[i].type != END_OF_TOKENS;i++){
		print_token(tokens[i],i);
	}
	printf("\n------------END OF PRINTING GENERATED TOKENS FOR THE LEXER------------\n\n");
	Node *root = parser(tokens);
	generate_code(root);
	FILE *assembly_f = fopen("./generated_code/generated_asm.asm","r");
	if(!assembly_f){
		printf("ERROR: Failed to open the asm file");
		exit(1);
	}
	system("./asm_generator.sh");
}
