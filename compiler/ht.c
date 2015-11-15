#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* asm_out;

typedef struct symbol{
	char* name;
  int  value;
	char type; /* i = integer, r = real ... */
	char stype; /* secondary type for array, function, procedure & we do not use it now */
	int scope;
	struct symbol* next;
} SYM;

/*-------------------------------------------------------------------------------------
 				SYMBOL FUNCTIONS
 ------------------------------------------------------------------------------------*/
SYM* new_sym(){
	SYM* sym;
	sym = (SYM*) malloc(sizeof(SYM));
	sym->next = NULL;
	return sym;
}

void init_sym(SYM* symbol, char* name, int value, char type, char stype, int scope){
  symbol->name = (char*) malloc(sizeof(char) * (strlen(name)));
  strcpy(symbol->name, name);
  symbol->value = value;
  symbol->type = type;
  symbol->stype = stype;
  symbol->scope = scope;
}

void print_symbol(SYM* symbol) {
  if (symbol == NULL) {
    printf("Symbol not allocated\n");
  }
  else {
    printf("Name: %s || Value: %d || Type: %c || SType: %c || Scope: %d \n", symbol->name, symbol->value, symbol->type, symbol->stype, symbol->scope);
  }
}

/*-------------------------------------------------------------------------------------
 				SYMBOL LIST FUNCTIONS
 ------------------------------------------------------------------------------------*/

void add_symbol(SYM **head, SYM* new_sym) {
  /* go to the end of the list */
  SYM* s;
  s = *head;
  if (s==NULL) {
    *head = new_sym;
    return;
  }

  while (s->next != NULL) {
    s = s->next;
  }

  /* attach at the bottom */
  s->next = new_sym;
}

void print_symbol_list(SYM* head) {
  SYM* s;

  s=head;
  if (s == NULL) {
    return;
  }
  while (s->next!= NULL) {
    print_symbol(s);
    s=s->next;
  }
  print_symbol(s);
}


/*-------------------------------------------------------------------------
 					HASH FUNCTIONS
 ---------------------------------------------------------------------------*/

int hasher(char* str){
	char* s;
	int sum = 0;
	for(s = str; *s != '\0'; s++){
		sum += *s;
	}
	return sum % 50;
}

void init_hash(SYM* hash[]) {
  int i;
  for (i = 0; i < 50; i++) {
    hash[i] = NULL;
  }
}

/* return true if there is a symbol with the same value and scope */
int check_find_sym(SYM* hash[], SYM* sym) {
  SYM* head = hash[hasher(sym->name)];
  if (head == NULL) {
    return 0;
  }
  if (strcmp(sym->name,"read")!=0 && strcmp(sym->name,"write")!=0) {
    for (; head->next!=NULL; head=head->next) {
      if (strcmp(head->name,sym->name)==0 && head->scope==sym->scope) {
		    sym->type=head->type;
		    sym->stype=head->stype;
		    return 1;
      }
    }
    if (strcmp(head->name,sym->name)==0 && head->scope==sym->scope) {
      sym->type=head->type;
	    sym->stype=head->stype;
      return 1;
    }
  }
  return 0;
}

int add_symbol_to_hash(SYM* hash[], SYM* sym) {
  if (check_find_sym(hash, sym)){
    return 0;
  }
  else {
    add_symbol(&hash[hasher(sym->name)],sym);
    return 1;
  }
}

void print_hash (SYM* hash[]) {
  int i;
  for (i=0; i<50; i++) {
    printf("*** %d ***\n",i);
    print_symbol_list(hash[i]);
  }

}

/*-------------------------------------------------------------------------
 					STACK FUNCTIONS
 ---------------------------------------------------------------------------*/


void push(SYM **head, SYM* sym) {
  add_symbol(head,sym);
}

SYM* pop (SYM **head) {
  SYM* s = *head;
  SYM* sprev;

  if (*head == NULL) {
    printf("ERROR: stack emtpy\n");
    return NULL;
  }

  if ((*head)->next == NULL) {
    s = *head;
    *head = NULL;
    return(s);
  }

  while (s->next!=NULL) {
    sprev=s;
    s=s->next;
  }

  sprev->next=NULL;
  return(s);
}

//--------------ASSEMBLY GENERATION------------------

void open_asm(const char* filename){
	asm_out = fopen(filename, "w");
}
void gene_decl(SYM* sym) {
  printf("Declaring Sym: %s\n", sym->name);
  fprintf(asm_out,"%s DW\n", sym->name);
}

void gene_mov(char* name, int value) {
  fprintf(asm_out,"MOV %s %d\n", name, value);
}

void gene_while(int condition, int stmt) {
  printf("In gene_while\n");
  fprintf(asm_out, "Label STMT %d\n", stmt);
  fprintf(asm_out, "*** code generation for statement ***\n");
  fprintf(asm_out, "CMP %d 0 \n", condition);
  fprintf(asm_out,"JGT STMT %d\n", stmt);
}

int relop(int type, int a, int b) {
  switch (type) {
  case 1 :
    return a < b;
  case 2:
    return a > b;
  case 3:
    return a <= b;
  case 4:
    return a >= b;
  case 5:
    return a == b;
  case 6:
    return a != b;
  }
}

int sign(int sign, int number) {
  switch (sign) {
  case 1:
    return number;
  case 2:
    return -number;
  }
}

int addop(int type, int a, int b) {
  switch (type) {
  case 1:
    printf("Adding %d to %d\n", a, b);
    return a + b;
  case 2:
    printf("Subing %d to %d\n", a, b);
    return a - b;
  }
}

int mulop(int type, int a, int b) {
  switch (type) {
  case 1:
    return a * b;
  case 2:
    return a / b;
  }
}
