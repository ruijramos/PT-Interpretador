#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho1.h"
#define MULTIPLIER 31

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

// ir buscar valor de um ELEM x
// int y = x.content.val;

ELEM empty() {
	ELEM y;
	y.kind = EMPTY;
	return y;
}

INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z) {
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

PROG_LIST newList(INSTR head, PROG_LIST tail) {
	PROG_LIST new = malloc(sizeof(struct prog_list));
	new -> elem = head;
	new -> next = tail;
	return new;
}

void addProgLast(INSTR s, PROG_LIST l) {
    if(l == NULL) return;
    while((l->next) != NULL) {
    	l = l->next;
    }
    l->next = newList(s, NULL);
}

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

void insert(char *variavel, int value) {
	int index;
	RECORD p;
	p = (RECORD)malloc(sizeof(struct record));
	index = hash(variavel);

	p->variavel = variavel; 
	p->valor = value;
	(p->next) = table[index];
	table[index] = p;	
}

void init_table() {
	for(int i=0; i<HASH_SIZE; i++) {
		table[i] = NULL;
	}
}

int getValue(ELEM x) {
	if(x.kind==STRING) {
		return lookup(x.content.name)->valor;
	}
	if(x.kind==INT_CONST) {
		return x.content.val;
	}
	else return -1;
}

void executaLista(PROG_LIST x) {
	if(x==NULL) {
		printf("Nenhuma instrução a apresentar.");
		return;
	}
	else {
		while(x->next != NULL) {
			run(x->elem);
			x = x->next;
		}
	}
}

void run(INSTR x) {
	switch(x.op) {
		case ATRIBUICAO:		
			insert(x.first.content.name, getValue(x.second));
		break;

		case SUM:
			insert(x.first.content.name, getValue(x.second)+getValue(x.third));
		break;

		case SUB:
			insert(x.first.content.name, getValue(x.second)-getValue(x.third));
		break;

		case MULT:
			insert(x.first.content.name, getValue(x.second)*getValue(x.third));
		break;

		case IF:
			if(getValue(x.first)!=NULL) { // se a varaivel ja tem valor siga para o goto

			}
		break;

		case PRINT:
			printf("%d\n", getValue(x.first));
		break;

		case LER:
			//insert(x.first.content.name, getValue(x.second));
		break;

		case GOTO:

		break;

		case LABEL:

		break;

		default:
			return;
	}

}
