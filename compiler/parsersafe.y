%{
#include "ht.c"

/*FILE *cfile = fopen("CFILE.c", "w");
fprintf(cfile, "Hello world\n");
close(cfile);*/

SYM* hash[50];      // hash[] is an array which contains all the symbols by their pointers
SYM* temp = NULL;   // temp is pointer to symbol, and with the SYM struct, it could be the head of a linked list
                    // and this linked list is to store the identider_list's symbols or temperary symbols which
                    // the production rule hasn't finish.
int scope = 0;      // 0 means the global scope

%}

%union{
	int integer;
	double real;
	char* string;
	char character;
};

%start compound_statement
%token <integer> INT // union structure for storing integer
%token <real> REALNO // union structure for storing real number
%token <string> ID   // union structure for storing identifier's name
%token PROGRAM INTEGER REAL VAR
%token BEGINT END IF THEN ELSE WHILE DO  
%token ROPAR RCPAR ROBRK RCBRK DOT SEMICOLON COMMA COLON
%token ASSIGNOP 
%token <integer> RELOP MULOP ADDOP
%type <character> type // union structure for storing type by single character
%type <integer> expression simple_expression factor term sign statement
%%

identifier_list: ID {

	char* str = $1;
	SYM* sym = new_sym();
	init_sym(sym, str, 0, 'u', 'u', -1); // 'u' means undefine, -1 means it's not global variable
	push(&temp,sym);      // push has the same functionality as add_symbol()
                        // push and pop are used for the 'temp' pointer with the linked list
                        // add_symbol() is used on the hash[] array
}
| identifier_list COMMA ID {
	// adds it to a temporary list
	// defer the adding but store the names somewhere
	SYM* sym = new_sym();
	init_sym(sym, $3, 0, 'u','u',-1);
	add_symbol(&temp,sym);  
}
;

declarations:declarations type identifier_list SEMICOLON {
	// go through the list and update all 
	// access the temporary storage and add ID to hash with type
	// go through the ID list
	SYM* s;
	while (temp!=NULL) {
		s = pop(&temp);
		s->type=$2;
		s->scope=scope; 
		if (!add_symbol_to_hash(hash,s)){
		      printf("Redeclaration of a variable within the same block\n");
		}
	gene_decl(s);
	}
}
|{printf("NO declarations\n");}
;

type: INTEGER {$$ = 'i';}
|REAL{$$ = 'r';}
;

compound_statement: BEGINT declarations optional_statements END {printf("Parsed compound statements\n");}
;

optional_statements:
|statement_list
;

statement_list: statement
|statement_list SEMICOLON statement
;

statement: ID ASSIGNOP expression{
	/* make a new symbol with the current variable */
	printf("ID ASSIGNOP expression\n");
	SYM* s=new_sym();
	/* set scope to currents scope and check if something like this exists in the table*/
	init_sym(s, $1, 0, 'u', 'u', scope);
	/* if there is no variable in the current scope with that name*/
	if (!check_find_sym(hash,s)) {
	/* if the variables is not already global, check the global list*/
		if (s->scope!=0) {
			s->scope=0;
			if (!check_find_sym(hash,s)) {
				printf("Usage Of Undeclared Variable.");
			}
		}
		else {
			printf("Usage Of Undeclared Variable.");
		}
	}
	s->value = $3;
	printf("%s goes to %d\n", s->name, s->value); 
	printf("Value of %s: %d\n", s->name, s->value);
	gene_mov(s->name, $3);
}
|WHILE ROPAR expression RCPAR ROBRK statement SEMICOLON RCBRK{ printf("WHILE expression DO statement\n"); gene_while($3, $6); }
;

expression: simple_expression { $$ = $1; }
|simple_expression RELOP simple_expression { printf("Simple Expresion relop\n"); $$ = relop($2, $1, $3); }
;

simple_expression: term { $$ = $1; }
|sign term { $$ = sign($1, $2); }
|simple_expression ADDOP term { $$ = addop($2, $1, $3);}
;

term: factor { $$ = $1; }
|term MULOP factor { $$ = mulop($2, $1, $3);}
;

factor: ID {
	char* str =  $1;
	SYM* head = hash[hasher(str)];
	$$ = head->value;
	gene_mov(head->name, $$);
}
|INT {  printf("Got %d\n", $1);
	$$ = $1; }
|ROPAR expression RCPAR { $$ = $2; }
;


sign:ADDOP { $$ = $1; }
;

%%
yyerror(char *s){
	fprintf(stderr, "error: %s\n", s);
}

int main(int argc, char* argv[]) {
	extern FILE* yyin;
	++argv; --argc;
	yyin = fopen(argv[0], "r");
	init_hash(hash);  // initiliaze the hash array of pointers to NULL
	open_asm("asm_out.txt");
	yyparse();
	print_hash(hash); // print the hash array we build
	return 0;
}
