#define HASH_SIZE 7

// ----------------------------------------------------------------------------------
typedef enum { ATRIBUICAO, SUM, SUB, MULT, DIV, IF, PRINT, LER, GOTO, LABEL, QUIT } OpKind;

typedef enum { EMPTY, INT_CONST, STRING } ElemKind;

typedef struct {
	ElemKind kind;
	union { // pode ser uma variavel em formato string ou um valor int
		int val; 
		char *name;
	} content;
} ELEM; 

typedef struct {
	OpKind op;
	ELEM first;
	ELEM second;
	ELEM third;
} INSTR;

ELEM newVar(char *s);
ELEM newInt(int n);
ELEM empty();
INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z);
int getValue(ELEM x); 


// ---------- hashmap -------------------------------------------------------------------

typedef struct hashmap {
	char *string;
	int chave;
	struct hashmap *next;
} *HASHMAP;

HASHMAP newHash(char *s, int v, HASHMAP tail);
HASHMAP addHashLast(char *s, int v, HASHMAP h);
void printHash(HASHMAP h);
int procurarPosicao(char *labelName, HASHMAP hm);

// ----------- listas e tables ----------------------------------------------------------
typedef struct prog_list { // lsita de instruçoes
	INSTR instrucao;
	struct prog_list *next;
} *PROG_LIST;

typedef struct record { // hashtable com o valor das variaveis
	char *variavel; 
	int valor;
	struct record *next;
} *RECORD;

RECORD table[HASH_SIZE]; // HAST TABLE DEFINIDA COMO VARIAVEL GLOBAL

void printList(PROG_LIST x);
void imprimeInst(INSTR x);
int listSize(PROG_LIST x);
void executaLista(PROG_LIST x, HASHMAP hm);
PROG_LIST addProgLast(INSTR s, PROG_LIST l);
PROG_LIST newList(INSTR head, PROG_LIST tail); // criar lista
unsigned int hash(char *s); // ir ver onde ta a variavel
RECORD lookup(char *s); // procura e retorna a posiçao na lista onde se encontra a string
void insert(char *s, int value); // insere variavel/valor na hastable
void init_table(); // limpa table