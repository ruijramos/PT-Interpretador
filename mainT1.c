#include "Trabalho1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxSize 20


INSTR avaliarInstrucao(char *s, HASHMAP hm, int posicao) {
	INSTR x;

	// reservas de espaço
	OpKind op;
	char *first = malloc(maxSize*sizeof(char));
	char *second = malloc(maxSize*sizeof(char));
	char *third = malloc(maxSize*sizeof(char));
	char *token = malloc(maxSize*sizeof(char));

	token = strtok(s, " "); // primeira palavra da string da instrução
	
	if(strcmp(token, "PRINT")==0) { // PRINT x ... valor de x
		op = PRINT;
		int i=1;
		while(token != NULL) {
			token = strtok(NULL, " ");
			if(i==1) first = token;
			i++;
		}
		x = newInstr(op, newVar(first), empty(), empty());
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
		int secondtoInt = atoi(second);
		x = newInstr(op, newVar(first), newInt(secondtoInt), empty());
		return x;
	}
	else if(strcmp(token, "LABEL")==0) { 
		op = LABEL;
		token = strtok(NULL, " ");
		first = token;
		x = newInstr(op, newVar(first), newInt(posicao), empty()); // LABEL L1 ... op = label, first(nome) = L1
		hm = addHashLast(first, posicao, hm);
		return x;
	}
	else if(strcmp(token, "IF")==0) { 
		op = IF;
		token = strtok(NULL, " ");
		first = token;
		token = strtok(NULL, " ");
		second = token;
		token = strtok(NULL, " ");
		third = token;
		x = newInstr(op, newVar(first), newVar(second), newVar(third));
		return x;
	}
	else if(strcmp(token, "GOTO")==0) { 
		op = GOTO;
		token = strtok(NULL, " ");
		first = token; // nome da label de onde é para ir
		x = newInstr(op, newVar(first), empty(), empty());
		return x;
	}
	else {
		first = token;
		int i=1;
		while(token!=NULL) {
			token = strtok(NULL," ");
			if(i==2) second = token;
			if(i==3) {
				if(token==NULL) {
					op = ATRIBUICAO;
					x = newInstr(op, newVar(first), newInt(atoi(second)), empty());
					return x;
				}
				if(strcmp(token, "+")==0) {
					op = SUM;					
				}
				if(strcmp(token, "-")==0) {
					op = SUB;
				}
				if(strcmp(token, "*")==0) {
					op = MULT;
				}
				if(strcmp(token, "/")==0) {
					op = DIV;
				}
			}
			if(i==4) {
				third = token;
			}
			i++;	
		}

		ELEM second1;
		ELEM third1;
		
		if(isdigit(second[0])!=0) second1 = newInt(atoi(second));
		else second1 = newVar(second);

		if(isdigit(third[0])!=0) third1 = newInt(atoi(third));
		else third1 = newVar(third);

		x = newInstr(op, newVar(first), second1, third1);
		return x;
	}
	// -------------------------------------------------------------------------------------------------

	return x;
}

int main() {

	printf("Bem-vindo ao Intrepetador, por favor escreva as suas instruções e encerre com <QUIT>: \n");
	
	char *auxiliar = malloc(maxSize*sizeof(char));
	scanf("%[^\n]",auxiliar);getchar();

	int posicao=1;
	HASHMAP hm = newHash("INICIO", 0, NULL);
	INSTR x = avaliarInstrucao(auxiliar, hm, posicao);
	PROG_LIST lista = newList(x, NULL);

	scanf("%[^\n]",auxiliar);getchar();

	while(strcmp(auxiliar, "<QUIT>")!=0) {
		posicao++;
		INSTR x = avaliarInstrucao(auxiliar, hm, posicao);
		lista = addProgLast(x, lista);
		scanf("%[^\n]",auxiliar);getchar();
	}

	printf("\nNúmero de instruções inseridas: %d\n", listSize(lista));
	printf("\nExecução das instruções: \n");
	executaLista(lista, hm);
	
	return 0;
}