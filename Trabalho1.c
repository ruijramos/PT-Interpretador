#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho1.h"
#define MULTIPLIER 31

// vão ser usadas no parce -----------------------------------
ELEM newVar(char *s) {
	ELEM y;
	y.kind = STRING;
	y.content.name = s;
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
	new -> elem = head;
	new -> next = tail;
	return new;
}

void addProgLast(INSTR s, PROG_LIST l) {
    if(l == NULL) {
    	l->elem = s;
    	l->next = NULL;
    	return;
    }

    while((l->next) != NULL) {
    	l = l->next;
    }
    l->next = newList(s, NULL);
}
// -------------------------------------------------------------

// exemplo
// x=2
// y=x+4
// PROG_LIST p = newList(newInstr(ATRIBUICAO, newVar("x"), newInt(2), empty()))
// newList(newInstr(ADD, newVar("y"), newVar("x"), newInt(4), NULL))

unsigned int hash(char *variavel) { // retorna o indice de onde está a string 
	unsigned int h;
	unsigned char *p;
	h=0;

	for(p=(unsigned char *)variavel; *p != '\0'; p++) {
		h = MULTIPLIER*h + *p;
	}

	return h%HASH_SIZE;
}

RECORD lookup(char *variavel) { // procura e retorna a posiçao na lista onde se encontra a string
	int index;
	RECORD p;
	index = hash(variavel);

	for( p=table[index]; p!=NULL; p=p->next) {
		if(strcmp(variavel, p->variavel)==0) return p;
	}

	return NULL;
}

void insert(char *variavel, int value) { // insere variavel/valor na table
	int index;
	RECORD p;
	p = (RECORD)malloc(sizeof(struct record));
	index = hash(variavel);

	p->variavel = variavel; 
	p->valor = value;
	(p->next) = table[index];
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
			printf("%s\n", x->elem.op);
			switch(x->elem.op) {
				case ATRIBUICAO:		
					insert(x->elem.first.content.name, getValue(x->elem.second)); // first = second
				break;

				case SUM:
					insert(x->elem.first.content.name, getValue(x->elem.second)+getValue(x->elem.third)); // first = second + third
				break;

				case SUB:
					insert(x->elem.first.content.name, getValue(x->elem.second)-getValue(x->elem.third)); // first = second - third
				break;

				case MULT:
					insert(x->elem.first.content.name, getValue(x->elem.second)*getValue(x->elem.third));// first = second * third
				break;

				// -- em falta ------------------------------------------------------------------------------------------------------
				case IF: 
					if(getValue(x->elem.first)!=-1) { // se a varaivel ja tem valor siga para o goto
						// ir para o goto
					}
				break;
				// ------------------------------------------------------------------------------------------------------------------

				case PRINT:
					if(getValue(x->elem.first)!=-1)	printf("%d\n", getValue(x->elem.first));
					else printf("Variável sem valor inserido. \n");
				break;

				case LER:
					insert(x->elem.first.content.name, getValue(x->elem.second)); // LER X 4 --> x=4
				break;

				// -- em falta -------------------------------------------------------------------------------------------------------
				case GOTO:

				break;
				// -------------------------------------------------------------------------------------------------------------------

				case LABEL:
					continue; // chegamos ao LABEL
				break;

				default:
					return;
			}
			x = x->next; // segue para a proxima instrução
		}
	}
}


