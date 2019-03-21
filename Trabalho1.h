#define HASH_SIZE 11

// ----------------------------------------------------------------------------------
typedef enum { ATRIBUICAO, SUM, SUB, MULT, IF_I, PRINT, LER, GOTO_I, LABEL } OpKind;

typedef enum { EMPTY, INT_CONST, STRING } ElemKind;

typedef struct {
	ElemKind kind;
	union { // pode ser uma variavel em formato string ou um valor int
		int val; 
		char *name;
	} content;
} ELEM; // dá-nos o tipo dos elementos

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

// ----------- listas e tables ----------------------------------------------------------
typedef struct prog_list {
	INSTR elem;
	struct prog_list *next;
} *PROG_LIST;

typedef struct record {
	char *variavel; 
	int valor;
	struct record *next;
} *RECORD;

RECORD table[HASH_SIZE]; // HAST TABLE DEFINIDA COMO VARIAVEL GLOBAL
//----------------------------------------------------------------------------------------

void run(INSTR x);
ELEM newVar(char *s);
ELEM newInt(int n);
INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z);
PROG_LIST newList(INSTR head, PROG_LIST tail); // criar lista
unsigned int hash(char *variavel); // ir ver onde ta a variavel
RECORD lookup(char *variavel); // procura e retorna a posiçao na lista onde se encontra a string
void insert(char *variavel, int value); // insere variavel/valor na hastable
void init_table(); // limpa table
int getValue(ELEM x);
void AddInstrOnList(INSTR a, PROG_LIST b);

