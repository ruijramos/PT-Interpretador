#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include <ctype.h>
#define MULTIPLIER 32
#define maxSize 20

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

unsigned int hash(char *s) { 
	unsigned int h;
	unsigned char *p;
	h=0;

	for(p=(unsigned char *)s; *p != '\0'; p++) {
		h = MULTIPLIER*h + *p;
	}

	return h%HASH_SIZE;
}

RECORD lookup(char *s) { 
	int index;
	RECORD p;
	index = hash(s);

	for( p=table[index]; p!=NULL; p=p->next) {
		if(strcmp(s, p->variavel)==0) return p;
	}

	return NULL;
}

void insert(char *s, int value) { 
	int index;
	RECORD p;
	p = (RECORD)malloc(sizeof(struct record));
	index = hash(s);

	p->variavel = s; 
	p->valor = value;
	p->next = table[index];
	table[index] = p;
}

void init_table() { 
	for(int i=0; i<HASH_SIZE; i++) {
		table[i] = NULL;
	}
}

int getValue(ELEM x) { 
	if(x.kind==STRING) {
		if(lookup(x.content.name)!=NULL) return lookup(x.content.name)->valor;
		else return -1000;
	}
	if(x.kind==INT_CONST) {
		return x.content.val;
	}
	else return -1000;
}

void executaLista(PROG_LIST x, HASHMAP hm, int comecar) { // executa a lista de instruçoes
	PROG_LIST aux = x;
	int progresso=1; // para andar pela prog_list e ver onde começar
	int posicaoParaIr;
	if(x==NULL) { // se é nula
		printf("Nenhuma instrução a apresentar.\n");
		return;
	}
	else {
		while(x != NULL) { // enquanto houver instruções para ler 
			if(comecar<=progresso) {
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

					case IF:           
						if(getValue(x->instrucao.first)!=0) { // se o valor é diferente de 0, o if é executado
							posicaoParaIr = procurarPosicao(x->instrucao.third.content.name, hm); // posição da lista onde está a label  
							executaLista(aux, hm, posicaoParaIr);
							return;
						}						
					break;

					case PRINT:        
						if(getValue(x->instrucao.first)!=-1000) {
							printf("%s = %d\n", x->instrucao.first.content.name,getValue(x->instrucao.first));
						}
					break;

					case LER:          
						insert(x->instrucao.first.content.name, getValue(x->instrucao.second));
					break;

					case GOTO:         
						posicaoParaIr = procurarPosicao(x->instrucao.first.content.name, hm);
					break;

					case LABEL:      
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