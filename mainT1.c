#include "Trabalho1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxSize 20


INSTR avaliarInstrucao(char *s) {
	INSTR x;

	// reservas de espaço
	char *op = malloc(maxSize*sizeof(char));
	char *first = malloc(maxSize*sizeof(char));
	char *second = malloc(maxSize*sizeof(char));
	char *third = malloc(maxSize*sizeof(char));
	char *token = malloc(maxSize*sizeof(char));

	token = strtok(s, " "); // primeira palavra da string da instrução
	puts(token);
	
	// SAO STRING NAO SE USA SWITCH
	if(strcmp(token, "PRINT")==0) {
		op = token;
		puts(op);
		while(token != NULL) {
			token = strtok(NULL, " ");
			first = token;
			puts(first);
		}
		ELEM first1 = newVar(first);
		ELEM y = empty();
		x = newInstr(op, first1, y, y);
		return x;
	}

	return x;
}

/*
token = strtok(s, " "); // primeira palavra da string da instrução
while(token != NULL) {
	token = strtok(NULL, " ");
}
*/

int main() {
	PROG_LIST lista = malloc(sizeof(struct prog_list));
	
	char *auxiliar = malloc(maxSize*sizeof(char));
	gets(auxiliar);

	while(strcmp(auxiliar, "QUIT")!=0) {
		INSTR x = avaliarInstrucao(auxiliar);
		addProgLast(x, lista);
		strcpy(auxiliar, "");
		gets(auxiliar);
	}

	executaLista(lista);
	
	return 0;
}