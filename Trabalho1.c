#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trabalho1.h"
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

int avaliarIf(INSTR x) { // para avaliar um if, basta avaliar o elemento first q é onde ta a condição
	
	// reservas de espaço
	char *first = malloc(maxSize*sizeof(char));
	first = x.first.content.name;

	if(strlen(first)==4) {
		char *esquerda = malloc(maxSize*sizeof(char));
		char *c1 = malloc(maxSize*sizeof(char));
		char *c2 = malloc(maxSize*sizeof(char));
		char *direita = malloc(maxSize*sizeof(char));

		esquerda[0] = first[0];
		c1[0] = first[1];
		c2[0] = first[2];
		direita[0] = first[3];

		if(c1[0]=='>' && c2[0]=='=') {
			if(isdigit(esquerda[0]) && isdigit(direita[0])) {
				if(atoi(esquerda)>=atoi(direita)) return 1;
			}
			if(isdigit(esquerda[0])) {
				if(atoi(esquerda)>=getValue(newVar(direita))) return 1;
			}
			if(isdigit(direita[0])) {
				if(getValue(newVar(esquerda))>=atoi(direita)) return 1;
			}
			else {
				if(getValue(newVar(esquerda))>=getValue(newVar(direita))) return 1;
			}
		}
		if(c1[0]=='<' && c2[0]=='=') {
			if(isdigit(esquerda[0]) && isdigit(direita[0])) {
				if(atoi(esquerda)<=atoi(direita)) return 1;
			}
			if(isdigit(esquerda[0])) {
				if(atoi(esquerda)<=getValue(newVar(direita))) return 1;
			}
			if(isdigit(direita[0])) {
				if(getValue(newVar(esquerda))<=atoi(direita)) return 1;
			}
			else {
				if(getValue(newVar(esquerda))<=getValue(newVar(direita))) return 1;
			}
		}
		if(c1[0]=='=' && c2[0]=='=') {
			if(isdigit(esquerda[0]) && isdigit(direita[0])) {
				if(atoi(esquerda)==atoi(direita)) return 1;
			}
			if(isdigit(esquerda[0])) {
				if(atoi(esquerda)==getValue(newVar(direita))) return 1;
			}
			if(isdigit(direita[0])) {
				if(getValue(newVar(esquerda))==atoi(direita)) return 1;
			}
			else {
				if(getValue(newVar(esquerda))==getValue(newVar(direita))) return 1;
			}
		}
	}
	if(strlen(first)==3) {
		char *esquerda = malloc(maxSize*sizeof(char));
		char *c = malloc(maxSize*sizeof(char));
		char *direita = malloc(maxSize*sizeof(char));

		esquerda[0] = first[0];
		c[0] = first[1];
		direita[0] = first[2];

		if(c[0]=='>') {
			if(isdigit(esquerda[0]) && isdigit(direita[0])) {
				if(atoi(esquerda)>atoi(direita)) return 1;
			}
			if(isdigit(esquerda[0])) {
				if(atoi(esquerda)>getValue(newVar(direita))) return 1;
			}
			if(isdigit(direita[0])) {
				if(getValue(newVar(esquerda))>atoi(direita)) return 1;
			}
			else {
				if(getValue(newVar(esquerda))>getValue(newVar(direita))) return 1;
			}
		}
		if(c[0]=='<') {
			if(isdigit(esquerda[0]) && isdigit(direita[0])) {
				if(atoi(esquerda)<atoi(direita)) return 1;
			}
			if(isdigit(esquerda[0])) {
				if(atoi(esquerda)<getValue(newVar(direita))) return 1;
			}
			if(isdigit(direita[0])) {
				if(getValue(newVar(esquerda))<atoi(direita)) return 1;
			}
			else {
				if(getValue(newVar(esquerda))<getValue(newVar(direita))) return 1;
			}
		}

	}

	return 0;
	
}

void executaLista(PROG_LIST x, HASHMAP hm, int comecar) { // executa a lista de instruçoes
	PROG_LIST aux = x;
	int progresso=1; // PARA SABER EM Q INSTRUÇÃO VAMOS A LER
	int posicaoParaIr;
	if(x==NULL) { // se é nula
		printf("Nenhuma instrução a apresentar.\n");
		return;
	}
	else {
		while(x != NULL) { // enquanto houver instruções para ler 
			if(comecar<=progresso) {
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
						if(avaliarIf(x->instrucao)==1) { // se sai 1, o if é executado
							posicaoParaIr = procurarPosicao(x->instrucao.third.content.name, hm);
							executaLista(aux, hm, posicaoParaIr);
							return;
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