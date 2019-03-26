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
	// POR EXEMPLO:
	// op = +, first = y, second = x, third = 1;
	// y = x+1
} INSTR;
// ------------------------------------------------------------------------------------

ELEM newVar(char *s);
ELEM newInt(int n);
ELEM empty();
INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z);
int getValue(ELEM x); // valor deu um elemento


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
//----------------------------------------------------------------------------------------



int listSize(PROG_LIST x);
void executaLista(PROG_LIST x);
PROG_LIST addProgLast(INSTR s, PROG_LIST l);
PROG_LIST newList(INSTR head, PROG_LIST tail); // criar lista
unsigned int hash(char *s); // ir ver onde ta a variavel
RECORD lookup(char *s); // procura e retorna a posiçao na lista onde se encontra a string
void insert(char *s, int value); // insere variavel/valor na hastable
void init_table(); // limpa table


