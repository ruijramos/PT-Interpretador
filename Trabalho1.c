#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho1.h"
#include <ctype.h>
#define MULTIPLIER 32

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


INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z) { // nova instrução
	INSTR aux;
	aux.op = oper;
	aux.first = x;
	aux.second = y;
	aux.third = z;
	return aux;
}

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

unsigned int hash(char *s) { // retorna o indice de onde está a string na hash table
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
		if(lookup(x.content.name)!=NULL) return lookup(x.content.name)->valor;
		else return -1;
	}
	if(x.kind==INT_CONST) {
		return x.content.val;
	}
	else return -1;
}

void executaLista(PROG_LIST x, HASHMAP hm) { // executa a lista de instruçoes
	int progresso=1; // PARA SABER EM Q INSTRUÇÃO VAMOS A LER
	int posicaoParaIr=1; // PARA OS GOTOS
	if(x==NULL) { // se é nula
		printf("Nenhuma instrução a apresentar.\n");
		return;
	}
	else {
		while(x != NULL) { // enquanto houver instruções para ler 
			if(posicaoParaIr<=progresso) {
				switch(x->instrucao.op) {
					case ATRIBUICAO:	// done	
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second)); // first = second
					break;

					case SUM:          // done
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second)+getValue(x->instrucao.third)); // first = second + third
					break;

					case SUB:          // done
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second)-getValue(x->instrucao.third)); // first = second - third
					break;

					case MULT:         // done
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second)*getValue(x->instrucao.third));// first = second * third
					break;

					case DIV:          // done
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second)/getValue(x->instrucao.third));
					break;

					case IF:           // done
						if(getValue(x->instrucao.first)!=-1) { // se a variavel n tem valor associado, n faz o goto
							posicaoParaIr = procurarPosicao(x->instrucao.third.content.name, hm);
						}
					break;

					case PRINT:        // done
						if(getValue(x->instrucao.first)!=-1) {
							printf("%s = %d\n", x->instrucao.first.content.name,getValue(x->instrucao.first));
						}
					break;

					case LER:          // done
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second));
					break;

					case GOTO:         // done
						posicaoParaIr = procurarPosicao(x->instrucao.first.content.name, hm);
					break;

					case LABEL:        // done
						 // chegamos ao LABEL e continuamos para a frente 
					break;

					default:
						return;
				}
			}
		x = x->next; // segue para a proxima instrução
		progresso++;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------


HASHMAP newHash(char *s, int v, HASHMAP tail) {
	HASHMAP new = malloc(sizeof(struct hashmap));
	new -> string = strdup(s);
	new -> chave = v;
	new -> next = tail;
	return new;
}	

HASHMAP addHashLast(char *s, int v, HASHMAP h) {
	HASHMAP aux = h;
    if(h == NULL) {
    	return newHash(s, v, NULL);
    }
    while((h->next) != NULL) {
    	h = h->next;
    }
    h->next = newHash(s, v, NULL);
    return aux;
}

void printHash(HASHMAP h) {
	if(h==NULL) printf("HashMap vazio.\n");
	else {
		while(h!=NULL) {
			printf("LABEL: %s, posição: %d\n", h->string, h->chave);
			h = h->next;
		}
	}
}

int procurarPosicao(char *labelName, HASHMAP h) {
	while(h!=NULL) {
		if(strcmp(h->string,labelName)==0) {
			return h->chave;
		}
		h = h->next;
	}
	return -1;
}