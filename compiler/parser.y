%{
#include "defines.h"
#include "var_tracker.c"

/*FILE *cfile = fopen("CFILE.c", "w");
fprintf(cfile, "Hello world\n");
close(cfile);*/

char* scope = "GLOBAL";      // 0 means the global scope
var_types v_type = -1;
extern int yylineno;
static FILE* cfile;// = fopen("cfile.c", "w+");
static FILE* mainfile;
static FILE* enumfile;
%}

%union{
	int integer;
	double real;
	char* string;
	char character;
};
%start program
%token <integer> INT // union structure for storing integer
%token <real> REALNO // union structure for storing real number
%token <string> ID   // union structure for storing identifier's name
%token <string> FOR_EXPRESSION INSERT_C
%token <string> FUNC RELOP PRINTF QUOTE INCLUDE
%token PROGRAM INTEGER REAL VAR
%token BEGINT END STATE_DEC IF FOR THEN ELSE DO  
%token ROPAR RCPAR ROBRK RCBRK DOT SEMICOLON COMMA COLON TRANSITION
%token ASSIGNOP AND OR STRING BANG IF_EXPRESSION
%token <integer> MULOP ADDOP
%type <character> type // union structure for storing type by single character
%type <integer> /*expression simple_expression factor term sign*/ statement
%%

identifier_list: vars_decl
| identifier_list COMMA {fprintf(cfile, ", ");}vars_decl
;

vars_decl: var_decl
|vars_decl COMMA {fprintf(cfile, ", ");} var_decl
;

var_decl: ID {create_var($1, v_type, NOSTYPE, scope); fprintf(cfile, "%s", $1);} assign
|
;

declarations:declarations type {
	if(v_type == 0){    
		fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(cfile, "char ", v_type);
	}
} identifier_list SEMICOLON{fprintf(cfile, ";\n");}
|type {
	if(v_type == 0){    
		fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(cfile, "char ", v_type);
	}

} identifier_list SEMICOLON{fprintf(cfile, ";\n");}
|
;

type: INTEGER {v_type = INTE; eprintf("its an INTEGER %d\n", v_type);}
|REAL{v_type = REL; eprintf("its a DOUBLE\n");}
|STRING{v_type = STR; eprintf("its a STRING\n");}
;

program: {fprintf(mainfile, "#include \"secondary.h\"\n#include \"function_declares.h\"\n");} includes
       BEGINT {fprintf(mainfile, "int main(int argc, char* argv[]){\nvoid* states[] = {");} states END {fprintf(mainfile, "};\n\n");eprintf("Parsed compound statements\n");}
;

includes: include
|includes include
;

include: INCLUDE {eprintf("INCLUDE %s\n", $1); fprintf(mainfile, "%s\n", $1);}

states: state {eprintf("Single State detected\n");}
|states state {eprintf("Multiple States Detected\n");}
;

state: STATE_DEC ID{scope = $2;}ROBRK declarations{fprintf(cfile,"state_%s:\n",$2);fprintf(mainfile,"&&state_%s,",$2);} optional_statements TRANSITION trans_state SEMICOLON RCBRK{
	fprintf(cfile, "\n\n");
};

trans_state:ID {fprintf(cfile, "goto state_%s;\n",$1);}
;

optional_statements: optional_statements statement_list
|statement_list
|{eprintf("Nothing here (optional_statements)\n");}
;

statement_list: statement
|statement_list SEMICOLON statement
;

statement: operations {eprintf("operations found %d\n",yylineno);}
|FOR ROPAR FOR_EXPRESSION{fprintf(cfile,"for(%s){\n", $3);}
RCPAR ROBRK optional_statements RCBRK {fprintf(cfile,"}\n");eprintf("FOR Statement done %d\n", yylineno);}
|IF ROPAR {fprintf(cfile,"if(");}comparison_list RCPAR ROBRK {fprintf(cfile, "){\n");} 
optional_statements RCBRK{fprintf(cfile,"}\n"); eprintf("IF Statement discovered\n");}
|PRINTF {eprintf("print found\n"); fprintf(cfile, "printf(");} ROPAR printf RCPAR SEMICOLON {fprintf(cfile,");\n");}
|INSERT_C {eprintf("embeded C code\n");
	char* string = $1 + 9;
	string[strlen(string) - 1] = '\0';
	fprintf(cfile, "%s\n", string);}
;

printf:QUOTE COMMA {eprintf("quote\n");fprintf(cfile,"%s,",$1);} vars
|QUOTE {eprintf("quote\n");fprintf(cfile,"%s",$1);}
;

vars: var
|vars COMMA {fprintf(cfile, ", ");} var
;

var:ID {fprintf(cfile, "%s", $1);} assign
   
assign: ASSIGNOP {fprintf(cfile, " = ");} math
|
;

operations: ID ASSIGNOP {eprintf("ID ASSIGNOP math pre line num %d\n", yylineno);fprintf(cfile,"%s = ", $1);}
math SEMICOLON{fprintf(cfile,";\n"); eprintf("ID ASSIGNOP math post\n");}
;

math: item 
|math ADDOP{fprintf(cfile, " %s ", $2);}item
;

item:ID {fprintf(cfile,"%s",$1);}
|REALNO {eprintf("ADDING IN REALNO %d\n",yylineno);fprintf(cfile,"%f",$1);}
|INT {fprintf(cfile,"%d",$1);}
|FUNC {eprintf("STATEMENT ID FUNCTION\n"); fprintf(cfile,"%s",$1);}
;

comparison_list: comparison {eprintf("Single comparison\n");}
|comparison_list AND {fprintf(cfile, " && ");}comparison {eprintf("And found\n");}
|comparison_list OR {fprintf(cfile, " || ");}comparison {eprintf("Or found\n");}
;

comparison: ID RELOP INT {fprintf(cfile,"%s %s %d",$1,$2,$3);eprintf("ID REL INT\n");}
|ID RELOP ID {fprintf(cfile,"%s %s %s",$1,$2,$3);eprintf("ID REL ID\n");}
|ID RELOP FUNC {fprintf(cfile,"%s %s %s",$1,$2,$3);eprintf("ID REL FUNC\n");}
;




/*
expression: {eprintf("HELLOSLFLDKSJFLSKJFLKSDJF\n");} 
|simple_expression { $$ = $1; }
|simple_expression RELOP simple_expression { eprintf("Simple Expresion relop\n"); }
;

simple_expression: term { $$ = $1; }
|sign term { $$ = $2; }
|simple_expression ADDOP term
;

term: factor { $$ = $1; }
|term MULOP factor { $$ = mulop($2, $1, $3);}
;

factor: ID {
	char* str =  $1;
}
|INT {  eprintf("Got %d\n", $1);
	$$ = $1; }
|ROPAR expression RCPAR { $$ = $2; }
;


sign:ADDOP { $$ = $1; }
;
*/

%%
yyerror(char *s){
	fprintf(stderr, "error: %s at line #%d\n", s, yylineno);
}

int main(int argc, char* argv[]) {
	extern FILE* yyin;
	cfile = fopen("cfile.c", "w+");
	mainfile = fopen("mainfile.c", "w+");
	enumfile = fopen("enumfile.c", "w+");
	//FILE* fp = fopen("cfile.c", "w+");
	//fprintf(fp,"#include <stdio.h>\n#include <stdlib.h>\n\nint main(){\nprintf(\"IM PRINTING\\n\");\n}\n");
	//fclose(fp);
	++argv; --argc;
	//yyin = fopen(argv[0], "r");
	char input[255];
	sprintf(input, "python formatter.py %s", argv[0]);
	system(input);
	yyin = fopen("new_yapl.txt", "r");
	fprintf(cfile, "if(argc > 1){\nvoid* ptr = states[atoi(argv[1])];\ngoto *ptr;\n}\n");
	yyparse();
	fprintf(cfile, "\n}");
	fclose(mainfile);
	fclose(cfile);
	system("cat cfile.c >> mainfile.c; gcc mainfile.c -o test");
	csystem("./test");
	return 0;
}
