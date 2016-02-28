%{
#include "defines.h"
#include "var_tracker.c"
#include <stddef.h>

char* scope = "GLOBAL";
var_types v_type = -1;
int num_embedded = 0;
int num_states = 0;
int global = 1;
int volatil = 0;
int backup_created = 0; // to determine if the char array has been created yet
int temp_backup = 0; //for error checking purposes
int update_all = 0;
extern int yylineno;
static FILE* cfile;
static FILE* mainfile;
static FILE* embedded;
static FILE* struct_file;
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
%token <string> FUNC RELOP PRINTF QUOTE INCLUDE PPMM
%token PROGRAM NOBACKUP VOLATILE INTEGER REAL VAR GLOBALD START_STATE
%token BEGINT END STATE_DEC IF FOR THEN ELSE DO  
%token ROPAR RCPAR ROBRK RCBRK DOT SEMICOLON COMMA COLON TRANSITION
%token ASSIGNOP AND OR STRING BANG IF_EXPRESSION
%token <integer> MULOP ADDOP
%type <character> type // union structure for storing type by single character
%%

G_identifier_list: G_vars_decl
| G_identifier_list COMMA {fprintf(struct_file, ", ");/*TODO*/fprintf(cfile, ", ");} G_vars_decl
;

G_vars_decl: G_var_decl
|G_vars_decl COMMA {fprintf(struct_file,", ");/*TODO*/fprintf(cfile, ";\n");} G_var_decl
;

G_var_decl: ID {create_var($1, v_type, NOSTYPE, scope, volatil, backup_created); print_list(); fprintf(struct_file, "%s", $1); printf("-----------\nPos of %s: %d\n-----------\n",$1, get_position($1));/*TODO*/fprintf(cfile, "%s_S.%s", scope, $1);} assign_var
|
;

identifier_list: vars_decl
| identifier_list COMMA {fprintf(struct_file, ", ");/*TODO*/fprintf(cfile, ", ");}vars_decl
;

vars_decl: var_decl
|vars_decl COMMA {fprintf(struct_file,", ");/*TODO*/fprintf(cfile, ";\n");} var_decl
;

var_decl: ID {create_var($1, v_type, NOSTYPE, scope, 0, -1); print_list(); fprintf(struct_file, "%s", $1); printf("-----------\nPos of %s: %d\n-----------\n",$1, get_position($1));/*TODO*/fprintf(cfile, "%s_S.%s", scope, $1);} assign_var
|
;

assign_var: ASSIGNOP {/*fprintf(struct_file, " = ");*//*TODO*/fprintf(cfile, " = ");} math_var
|
;

math_var: item_var 
|math_var ADDOP{/*fprintf(struct_file, " %s ", $2);*//*TODO*/fprintf(cfile, " %s ", $2);}item_var
;

item_var:ID {/*fprintf(struct_file,"%s",$1);*//*TODO*/fprintf(cfile,"%s",$1);}
|REALNO {eprintf("ADDING IN REALNO %d\n",yylineno);/*fprintf(struct_file,"%f",$1);*//*TODO*/fprintf(cfile,"%f",$1);}
|INT {/*fprintf(struct_file,"%d",$1);*//*TODO*/fprintf(cfile,"%d",$1);}
|FUNC {eprintf("STATEMENT ID FUNCTION\n");/*fprintf(struct_file,"%s",$1);*//*TODO*/fprintf(cfile,"%s",$1);}
;

declarations:declarations type {
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}
} identifier_list SEMICOLON{fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|type {
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}

} identifier_list SEMICOLON{fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|
;

G_declarations:G_declarations type {
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}
} G_identifier_list SEMICOLON{fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|type {
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}

} G_identifier_list SEMICOLON{fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|G_declarations VOLATILE type {
	volatil = 1;
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}
	

} G_identifier_list SEMICOLON{volatil = 0; fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
| VOLATILE type {
	volatil = 1;
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}


} G_identifier_list SEMICOLON{volatil = 0; fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|G_declarations NOBACKUP type {
	backup_created = -1;
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}
	

} G_identifier_list SEMICOLON{backup_created = 0; fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
| NOBACKUP type {
	backup_created = -1;
	if(v_type == 0){    
		fprintf(struct_file, "int ");
		//fprintf(cfile, "int ", v_type);
	}if(v_type == 1){    
		fprintf(struct_file, "double ");
		//fprintf(cfile, "double ", v_type);
	}if(v_type == 2){    
		fprintf(struct_file, "char ");
		//fprintf(cfile, "char ", v_type);
	}


} G_identifier_list SEMICOLON{backup_created = 0; fprintf(struct_file,";\n");fprintf(cfile, ";\n");}
|
;

type: INTEGER {v_type = INTE; eprintf("its an INTEGER %d\n", v_type);}
|REAL{v_type = REL; eprintf("its a DOUBLE\n");}
|STRING{v_type = STR; eprintf("its a STRING\n");}
;

program: {
	fprintf(mainfile, "#include <time.h>\n#include <stddef.h>\n#include <netinet/in.h>\n#include <inttypes.h>\n#include <unistd.h>\n#include <sys/socket.h>\n#include <sys/types.h>\n#include <stdlib.h>\n#include <netdb.h>\n#include <string.h>\n#include <pthread.h>\n#include \"structs.h\"\n");} 
	includes 
	start_state {
		fprintf(struct_file, "typedef struct __state_%s{int Curr_State;\n", scope);
		fprintf(cfile, "State_%s_Struct %s_S;\nunsigned char* data = malloc(sizeof(GLOBAL_S));\n", scope, scope);
		eprintf("GLOBAL Declarations Start\n");
	} 
	G_declarations {
		eprintf("GLOBAL Declarations End\n");
		fprintf(embedded,"//%s\ndsflksdfs\n","\%d");
		fprintf(cfile, "if( access(\"backup.txt\", F_OK) != -1 ) {\n    printf(\"file exists\\n\");\nprintf(\"BEFORE Value of first: %s\\n\", GLOBAL_S.test);\nprintf(\"BEFORE Value of first: %s\\n\", GLOBAL_S.var1);\nprintf(\"BEFORE Value of first: %s\\n\", GLOBAL_S.var2);\nrestore_global_values(&GLOBAL_S);\nprintf(\"AFTER Value of first: %s\\n\", GLOBAL_S.test);\nprintf(\"AFTER Value of first: %s\\n\", GLOBAL_S.var1);\nprintf(\"AFTER Value of first: %s\\n\", GLOBAL_S.var2);\n} else {\n    printf(\"file doesn't exist\\n\");\n}\n","\%d","\%d","\%d","\%d","\%d","\%d");
		fprintf(cfile, "if(s){\nvoid* ptr = states[state];\ngoto *ptr;\n}\nelse{\ngoto *start_ptr;\n}\nbegin:;\n");
		fprintf(struct_file,"\n} State_%s_Struct;\n\n", scope);
	}
	BEGINT {fprintf(mainfile, "void restore_global_values(State_GLOBAL_Struct *GLOBAL_S);\n\nint main(int argc, char* argv[]){\nint sockfd, n, o, s = 0, state = 0;\nchar *address = \"127.0.0.1\";\nwhile ((o = getopt (argc, argv, \"h:s:\")) != -1) {\nswitch(o){\ncase 'h':\naddress = optarg;\nbreak;\ncase 's':\ns = 1;\nstate = atoi(optarg);\nbreak;\n}\n}\nstruct sockaddr_in servaddr;\nsockfd=socket(AF_INET,SOCK_STREAM,0);\nbzero(&servaddr,sizeof servaddr);\nservaddr.sin_family=AF_INET;\nservaddr.sin_port=htons(22000);\ninet_pton(AF_INET, address, &(servaddr.sin_addr));\nconnect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));\npthread_t thread;\nvoid* states[] = {");} 
	states 
	END {fprintf(mainfile, "};\n\n");eprintf("Parsed compound statements\n");}
;

start_state: START_STATE ID {fprintf(cfile, "void* start_ptr = &&state_%s;\n", $2);}
|{fprintf(cfile, "void* start_ptr = states[0];\n");}
;

includes: include
|includes include
;

include: INCLUDE {eprintf("INCLUDE %s\n", $1); fprintf(mainfile, "%s\n", $1);}

states: state {eprintf("Single State detected\n");}
|states state {eprintf("Multiple States Detected\n");}
;

state: STATE_DEC ID{scope = $2; fprintf(struct_file, "typedef struct __state_%s{State_GLOBAL_Struct G_Struct;\n", $2);fprintf(cfile, "state_%s:;\nState_%s_Struct %s_S;\n",$2,$2, $2);}
		ROBRK 
		declarations{fprintf(struct_file,"\n} State_%s_Struct;\n\n",$2);}
		optional_statements{/*
			if(update_all) fprintf(cfile,"\n%s_S.G_Struct = GLOBAL_S;\nGLOBAL_S.Curr_State = %d;\nmemcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));\nwrite(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));\n",$2,num_states);
			num_states++;
			fprintf(mainfile,"&&state_%s,",$2);*/
		}
		RCBRK{fprintf(cfile, "\n\n"); update_all = 0;}
;

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
/*|FOR ROPAR FOR_EXPRESSION{fprintf(cfile,"for(%s){\n", $3);}
RCPAR ROBRK optional_statements RCBRK {fprintf(cfile,"}\n");eprintf("FOR Statement done %d\n", yylineno);}*/
|{
if(update_all) fprintf(cfile,"\n%s_S.G_Struct = GLOBAL_S;\nGLOBAL_S.Curr_State = %d;\nmemcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));\nwrite(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));\n",scope,num_states);
num_states++;
fprintf(mainfile,"&&state_%s,",scope);
}
transition_statement
|FOR ROPAR ID ASSIGNOP {fprintf(cfile,"for(%s_S.%s = ", scope, $3);}item SEMICOLON ID RELOP {fprintf(cfile,"; %s_S.%s %s ", scope, $8, $9);} item SEMICOLON ID PPMM {fprintf(cfile,"; %s_S.%s%s){\n",scope,$13,$14);}
RCPAR ROBRK optional_statements RCBRK {fprintf(cfile,"}\n");eprintf("FOR Statement done %d\n", yylineno);}
|IF ROPAR {fprintf(cfile,"if(");}comparison_list RCPAR ROBRK {fprintf(cfile, "){\n");} 
optional_statements RCBRK{fprintf(cfile,"}\n"); eprintf("IF Statement discovered\n");}
|PRINTF {eprintf("print found\n"); fprintf(cfile, "printf(");} ROPAR printf RCPAR SEMICOLON {fprintf(cfile,");\n");}
|INSERT_C {eprintf("embeded C code\n");
	char* string = $1 + 9;
	string[strlen(string) - 1] = '\0';
	/*fprintf(cfile, "\npthread_create(thread, NULL, %s_Embedded_%d, &%s_S );\n%s\n", scope, num_embedded, scope, string);
	fprintf(embedded, "int %s_Embedded_%d(void* Stru){\nState_%s_Struct *%s_S = malloc(sizeof(State_%s_Struct));\n", scope, num_embedded, scope, scope, scope);
	fprintf(embedded, "*%s_S = (State_%s_Struct*) Stru;\n", scope, scope);
	fprintf(embedded, "\n%s\n}\n", string);*/
	fprintf(cfile, "\n%s\n", string);
	num_embedded++;
}
;

transition_statement: TRANSITION trans_state SEMICOLON
;

printf:QUOTE COMMA {eprintf("quote\n");fprintf(cfile,"%s,",$1);} vars_print
|QUOTE {eprintf("quote\n");fprintf(cfile,"%s",$1);}
;

vars_print: var_print
|vars_print COMMA {fprintf(cfile, ", ");} var_print
;

var_print:ID {fprintf(cfile, "%s_S.%s", scope, $1);} assign

/*
vars: var
|vars COMMA {fprintf(cfile, ", ");} var
;

var:ID {fprintf(cfile, "%s_S.%s", scope, $1);} assign
*/   
assign: ASSIGNOP {fprintf(cfile, " = ");} math
|
;

operations: ID 
			ASSIGNOP {eprintf("ID ASSIGNOP math pre line num %d\n", yylineno);
				int posi = get_position($1);
				if(posi < 0){
					fprintf(cfile,"%s_S.%s = ", scope, $1);
				} else{ 
					fprintf(cfile,"GLOBAL_S.%s = ", $1);
					update_all = 1;
				}
			}
			math 
			SEMICOLON{
				fprintf(cfile,";\n");
				int posi = get_position($1);
				eprintf("-----------------------------------VAR %s POSI %d - %d------------------------------------\n", $1, get_position($1), posi);
				temp_backup = get_backup($1);
				if(posi >= 0 && get_volatile($1) && temp_backup != -1){
					if(!temp_backup){
						fprintf(cfile, "char* data_%s = malloc(sizeof(GLOBAL_S.%s) + sizeof(int));\n",$1,$1);
					}
					fprintf(cfile, "memset(data_%s, %d, 1);\n",$1,posi);
					fprintf(cfile, "memcpy(&data_%s[1], &GLOBAL_S.%s, sizeof(int));\n",$1,$1);
					fprintf(cfile, "write(sockfd, &data_%s, (sizeof(GLOBAL_S.%s) + sizeof(int)));\n",$1,$1);
				}
				eprintf("ID ASSIGNOP math post\n");
				
			}
|operations ID 
			ASSIGNOP {eprintf("ID ASSIGNOP math pre line num %d\n", yylineno);
				int posi = get_position($2);
				if(posi < 0){
					fprintf(cfile,"%s_S.%s = ", scope, $2);
				} else{ 
					fprintf(cfile,"GLOBAL_S.%s = ", $2);
					update_all = 1;
				}
			}
			math 
			SEMICOLON{
				fprintf(cfile,";\n");
				int posi = get_position($2);
				eprintf("-----------------------------------VAR %s POSI %d - %d------------------------------------\n", $2, get_position($2), posi);
				temp_backup = get_backup($2);
				if(posi >= 0 && get_volatile($2) && temp_backup != -1){
					if(!temp_backup){
						fprintf(cfile, "char* data_%s = malloc(sizeof(GLOBAL_S.%s) + sizeof(int));\n",$2,$2);
					}
					fprintf(cfile, "memset(data_%s, %d, 1);\n",$2,posi);
					fprintf(cfile, "memcpy(&data_%s[1], &GLOBAL_S.%s, sizeof(int));\n",$2,$2);
					fprintf(cfile, "write(sockfd, &data_%s, (sizeof(GLOBAL_S.%s) + sizeof(int)));\n",$2,$2);
				}
				eprintf("ID ASSIGNOP math post\n");
				
			}

;

math: item 
|math ADDOP{fprintf(cfile, " %s ", $2);}item
;

item:ID {fprintf(cfile,"%s_S.%s", scope, $1);}
|REALNO {eprintf("ADDING IN REALNO %d\n",yylineno);fprintf(cfile,"%f",$1);}
|INT {fprintf(cfile,"%d",$1);}
|FUNC {eprintf("STATEMENT ID FUNCTION\n"); fprintf(cfile,"%s",$1);}
;

comparison_list: comparison {eprintf("Single comparison\n");}
|comparison_list AND {fprintf(cfile, " && ");}comparison {eprintf("And found\n");}
|comparison_list OR {fprintf(cfile, " || ");}comparison {eprintf("Or found\n");}
;

comparison: ID RELOP INT {fprintf(cfile,"%s_S.%s %s %d",scope,$1,$2,$3);eprintf("ID REL INT\n");}
|ID RELOP ID {fprintf(cfile,"%s_S.%s %s %s_S.%s",scope,$1,$2,scope,$3);eprintf("ID REL ID\n");}
|ID RELOP FUNC {fprintf(cfile,"%s_S.%s %s %s",scope,$1,$2,$3);eprintf("ID REL FUNC\n");}
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
	struct_file = fopen("structs.h", "w+");
	embedded = fopen("embedded.h", "w+");
	++argv; --argc;
	char input[255];
	sprintf(input, "python formatter.py %s", argv[0]);
	system(input);
	yyin = fopen("new_yapl.txt", "r");
	//fprintf(cfile, "if(argc > 1){\nvoid* ptr = states[atoi(argv[1])];\ngoto *ptr;\n}\n");
	yyparse();
	fprintf(cfile, "\n}\n\nvoid restore_global_values(State_GLOBAL_Struct *GLOBAL_S){\nFILE* restore = fopen(\"backup.txt\", \"r\");\nchar * value_char = NULL;\nint pos = 0;\nint value = 0;\nsize_t len = 0;\nwhile ((getline(&value_char, &len, restore)) != -1) {\nif(strcmp(value_char, \"\\n\")){\nvalue = atoi(value_char);\nmemcpy(&GLOBAL_S->Curr_State + pos, &value, sizeof(int));\n//printf(\"Retrieved: %s at position: %s\\n\", value, pos);\n}\npos++;\n}\n}\n","\%d","\%d");
	fclose(mainfile);
	fclose(cfile);
	fclose(struct_file);
	system("cat cfile.c >> mainfile.c; gcc mainfile.c -o program -lpthread");
	csystem("./program");
	return 0;
}
