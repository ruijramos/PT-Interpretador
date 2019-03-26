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
	
	// SAO STRING NAO SE USA SWITCH ---------------------------------------------------------------------
	if(strcmp(token, "PRINT")==0) { // PRINT x ... valor de x
		op = PRINT;
		int i=1;
		while(token != NULL) {
			token = strtok(NULL, " ");
			if(i==1) first = token;
			i++;
		}
		printf("first (a variavel que se vai printar): %s\n" , first);
		ELEM first1 = newVar(first);
		ELEM y = empty();
		x = newInstr(op, first1, y, y);
		return x;
	}
	else if(strcmp(token, "LER")==0) { // LER x 4 ... x = 4
		op = LER;
		int i=1;
		while(token != NULL) {
			token = strtok(NULL, " ");
			if(i==1) first = token;
			if(i==2) second = token;
			i++;
		}
		printf("first (onde se guarda): %s\n", first);
		printf("second (o valor a guardar): %s\n", second);
		ELEM first1 = newVar(first);
		int secondtoInt = atoi(second);
		ELEM second1 = newInt(secondtoInt);
		ELEM y = empty();	
		x = newInstr(op, first1, second1, y);
		printf("variavel guardada: %s\n", x.first.content.name);
		return x;
	}
	else if(strcmp(token, "LABEL")==0) {
		op = LABEL;
		int i=1;
		while(token!=NULL) {
			token = strtok(NULL, " ");
			if(i==1) first = token;
			i++;
		}
		printf("first (nome do label): %s\n", first);
		ELEM y = empty();
		x = newInstr(op, y, y, y);
		return x;
	}
	// -------------------------------------------------------------------------------------------------

	return x;
}

int main() {
	
	char *auxiliar = malloc(maxSize*sizeof(char));
	scanf("%[^\n]",auxiliar);getchar();
	INSTR x = avaliarInstrucao(auxiliar);
	PROG_LIST lista = newList(x, NULL);

	scanf("%[^\n]",auxiliar);getchar();

	while(strcmp(auxiliar, "QUIT")!=0) {
		INSTR x = avaliarInstrucao(auxiliar);
		lista = addProgLast(x, lista);
		scanf("%[^\n]",auxiliar);getchar();
	}

	printf("Vamos iniciar a execução - Número de instruções: %d\n", listSize(lista));
	executaLista(lista);
	
	return 0;
}