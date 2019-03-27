#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho1.h"
#include <ctype.h>
#define MULTIPLIER 32

// vão ser usadas no parce -----------------------------------
ELEM newVar(char *s) {
	ELEM y;
	y.kind = STRING;
	y.content.name = strdup(s);	
	return y;
}

ELEM newInt(int n) {
	ELEM y;
	y.kind = INT_CONST;
	y.content.val = n;
	return y;
}

ELEM empty() {
	ELEM y;
	y.kind = EMPTY;
	return y;
}

// -----------------------------------------------------------

INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z) { // nova instrução
	INSTR aux;
	aux.op = oper;
	aux.first = x;
	aux.second = y;
	aux.third = z;
	return aux;
	// Exemplo
	// x = y + 2
	// k = newInstr(ADD, newVar("x"), newVar("y"), newInt(2));
	// k é a representação em memória da instrução
}

// meter uma instrução na lista -------------------------------
PROG_LIST newList(INSTR head, PROG_LIST tail) {
	PROG_LIST new = malloc(sizeof(struct prog_list));
	new -> instrucao = head;
	new -> next = tail;
	return new;
}

PROG_LIST addProgLast(INSTR s, PROG_LIST l) {
    PROG_LIST aux = l;
    if(l == NULL) {
    	return newList(s, NULL);
    }
    while((l->next) != NULL) {
    	l = l->next;
    }
    l->next = newList(s, NULL);
    return aux;
}

int listSize(PROG_LIST x) {
	if(x==NULL) return 0;
	else {
		int size=0;
		while(x != NULL) {
			size++;
			x = x->next;
		}
		return size;
	}
	return -1;
}

void imprimeInst(INSTR x) {
	switch(x.op) {
				case ATRIBUICAO:		
					printf("ATRIBUICAO ");
				break;

				case SUM:
					printf("SUM ");
					printf("%s ", x.first.content.name);
				break;

				case SUB:
					printf("SUB ");
				break;

				case MULT:
					printf("MULT ");
				break;

				case DIV: 
					printf("DIV ");
				break;

				case IF: 
					printf("IF ");
				break;

				case PRINT:
					printf("PRINT ");
					printf("%s \n", x.first.content.name);
				break;

				case LER:
					printf("LER ");
					printf("%s %d\n", x.first.content.name, getValue(x.second));
				break;

				case GOTO:
					printf("GOTO ");
				break;

				case LABEL:
					printf("LABEL");
				break;

				default:
					return;
	}
	return;
}

void printList(PROG_LIST x) {
	if(x==NULL) printf("Lista vazia\n");
	else {
		int i=1;
		while(x!=NULL) {
			printf("Instrução %d: ", i);
			imprimeInst(x->instrucao);
			x=x->next;
			i++;
		}
	}
}
// -------------------------------------------------------------

// exemplo
// x=2
// y=x+4
// PROG_LIST p = newList(newInstr(ATRIBUICAO, newVar("x"), newInt(2), empty()))
// newList(newInstr(ADD, newVar("y"), newVar("x"), newInt(4), NULL))

unsigned int hash(char *s) { // retorna o indice de onde está a string 
	unsigned int h;
	unsigned char *p;
	h=0;

	for(p=(unsigned char *)s; *p != '\0'; p++) {
		h = MULTIPLIER*h + *p;
	}

	return h%HASH_SIZE;
}

RECORD lookup(char *s) { // procura e retorna a posiçao na lista onde se encontra a string
	int index;
	RECORD p;
	index = hash(s);

	for( p=table[index]; p!=NULL; p=p->next) {
		if(strcmp(s, p->variavel)==0) return p;
	}

	return NULL;
}

void insert(char *s, int value) { // insere variavel/valor na table
	int index;
	RECORD p;
	p = (RECORD)malloc(sizeof(struct record));
	index = hash(s);

	p->variavel = s; 
	p->valor = value;
	p->next = table[index];
	table[index] = p;
}

void init_table() { // limpa a tabela
	for(int i=0; i<HASH_SIZE; i++) {
		table[i] = NULL;
	}
}

int getValue(ELEM x) { // retorna o valor de um elemento
	if(x.kind==STRING) {
		return lookup(x.content.name)->valor;
	}
	if(x.kind==INT_CONST) {
		return x.content.val;
	}
	else return -1;
}

void executaLista(PROG_LIST x) { // executa a lista de instruçoes
	if(x==NULL) { // se é nula
		printf("Nenhuma instrução a apresentar.\n");
		return;
	}
	else {
		while(x != NULL) { // enquanto houver instruções para ler 
			// entra aqui e percorre bem a cena
			switch(x->instrucao.op) {
				case ATRIBUICAO:		
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second)); // first = second
				break;

				case SUM:
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second)+getValue(x->instrucao.third)); // first = second + third
				break;

				case SUB:
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second)-getValue(x->instrucao.third)); // first = second - third
				break;

				case MULT:
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second)*getValue(x->instrucao.third));// first = second * third
				break;

				case DIV: 
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second)/getValue(x->instrucao.third));
				break;

				// -- em falta ------------------------------------------------------------------------------------------------------
				case IF: 
					if(getValue(x->instrucao.first)!=-1) { // se a varaivel ja tem valor siga para o goto
						// ir para o goto
					}
				break;
				// ------------------------------------------------------------------------------------------------------------------

				case PRINT:
					if(getValue(x->instrucao.first)!=-1) {
						printf("%d\n", getValue(x->instrucao.first));
					}
				break;

				case LER:
					insert(x->instrucao.first.content.name, getValue(x->instrucao.second));
				break;

				// -- em falta -------------------------------------------------------------------------------------------------------
				case GOTO:

				break;
				// -------------------------------------------------------------------------------------------------------------------

				case LABEL:
					x = x->next; 
					continue; // chegamos ao LABEL
				break;

				default:
					return;
			}
			x = x->next; // segue para a proxima instrução
		}
	}
}


