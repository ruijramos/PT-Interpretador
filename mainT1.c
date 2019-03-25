#include "Trabalho1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxSize 20


INSTR avaliarInstrucao(char *s) {
	INSTR x;

	// reservas de espaço
	OpKind op;
	char *first = malloc(maxSize*sizeof(char));
	char *second = malloc(maxSize*sizeof(char));
	char *third = malloc(maxSize*sizeof(char));
	char *token = malloc(maxSize*sizeof(char));

	token = strtok(s, " "); // primeira palavra da string da instrução
	
	// SAO STRING NAO SE USA SWITCH
	if(strcmp(token, "PRINT")==0) {
		op = PRINT;
		while(token != NULL) {
			token = strtok(NULL, " ");
			first = token;
		}
		ELEM first1 = newVar(first);
		ELEM y = empty();
		x = newInstr(op, first1, y, y);
		return x;
	}

	if(strcmp(token, "LER")==0) { // LER x 4 ... x = 4
		op = LER;
		int i=1;
		while(token != NULL) {
			token = strtok(NULL, " ");
			if(i==1) first = token;
			if(i==2) second = token;
			i++;
		}
		ELEM first1 = newVar(first);
		int secondtoInt = atoi(second);
		ELEM second1 = newInt(secondtoInt);
		ELEM y = empty();	
		x = newInstr(op, first1, second1, y);
		return x;
	}

	return x;
}

int main() {
	PROG_LIST lista = malloc(sizeof(struct prog_list));
	
	char *auxiliar = malloc(maxSize*sizeof(char));
	scanf("%[^\n]",auxiliar);getchar();

	while(strcmp(auxiliar, "QUIT")!=0) {
		INSTR x = avaliarInstrucao(auxiliar);
		addProgLast(x, lista);
		scanf("%[^\n]",auxiliar);getchar();
	}

	executaLista(lista);
	
	return 0;
}