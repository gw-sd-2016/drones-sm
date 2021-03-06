#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
/*#define DEBUG
#define EDEBUG

#ifdef EDEBUG
# define eprintf(x...) printf(x)
#else
# define eprintf(x...) ; 
#endif

#ifdef DEBUG
# define dprintf(x...) printf(x)
#else
# define dprintf(x...) ; 
#endif
*/


typedef enum var_types{
	INTE,
	REL,
	STR,
	NOTYPE = -1,
} var_types;

typedef enum secondary_type{
	ARRAY,
	FUNCTION,
	STATE,
	NOSTYPE = -1,
} secondary_type;

typedef enum variable_scope{
	GLOBAL,
	A,
	B,
	C,
	D,
	E,
} variable_scope;

typedef struct variable{
	char* id;
	var_types type;
	secondary_type stype;
	char* scope; //Temporarily Global is
	struct variable* next;
}var;

var* declared_variables[64];

int string_to_int(char* string);
int add_var_dec(var* v);
int create_var(char* id, var_types t, secondary_type st, char* sc);
int simple_hash();
int is_declared(char* string);
void print_enum_info();

/*--------------------------------------------------------------------------------------------------------------------------------------------*/

int string_to_int(char* string){
	int i = 0, string_val = 0;
	
	while(string[i] != '\0'){
		string_val += (string[i] ^ i);
		i++;
	}

	dprintf("String value: %d\n", string_val);
	return (string_val % 64);
}

int add_var_dec(var* v){
	int string_val;
	dprintf("Declaring variable\n");
	dprintf("Var ID: %s\nVar Type: %d\nVar SType: %d\nVar Scope: %s\n\n",v->id, v->type, v->stype, v->scope);
	dprintf("Getting string value:\n");
	string_val = string_to_int(v->id);
	dprintf("String value is: %d\n",string_val);
	if(declared_variables[string_val] == NULL){
		dprintf("There is no current declaration that has the same hash BUCKET-%d\n\n", string_val);
		declared_variables[string_val] = v;
	}else{
		dprintf("There is a possible conflict BUCKET-%d\n", string_val);
		var* temp = declared_variables[string_val];
		while(temp->next != NULL){
			dprintf("Current Declaration ID is: %s\nLooking for ID %s\n", temp->id, v->id);
			if(!strcmp(temp->id, v->id)){
				fprintf(stderr, "There is a duplicate variable declaration of %s within the scope %s\n", v->id, temp->scope);
			    //system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
                exit(-1);
				return -1;
			}
			dprintf("\nThis was not a conflict\n");
			temp = temp->next;
		}
		dprintf("After while loop Current Declaration ID is: %s\nLooking for ID %s\nScope v: %s\nScope temp: %s\n", temp->id, v->id, v->scope, temp->scope);
		if(!strcmp(temp->id, v->id) && !strcmp(temp->scope, v->scope)){
			fprintf(stderr, "There is a duplicate variable declaration of %s within the scope %s\n", v->id, v->scope);
			//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
			exit(-1);
            return -1;
		}
		dprintf("Setting temp next to v\n");
		temp->next = v;
		dprintf("There was no conflict\n\n");
	}
	dprintf("DONE WITH ADD\n");
}

int create_var(char* id, var_types t, secondary_type st, char* sc){
	var* v = malloc(sizeof(var));
	v->id = id;
	v->type = t;
	v->stype = st;
	v->scope = sc;
	dprintf("about to print scope\n");
	dprintf("Var SCOPE: %s\n", v->id);
	v->next = NULL;
	add_var_dec(v);
	var* tmp = malloc(sizeof(var));
	int i = 0;
	for(i = 0; i < 64; i++){
		if(declared_variables[i]){
			dprintf("-----------------------------\nBucket: %d\n",i);
			tmp = declared_variables[i];
			while(tmp != NULL){
				dprintf("Var ID: %s\nVar Scope: %s\n", tmp->id, tmp->scope);
				tmp = tmp->next;
			}
			dprintf("-----------------------------\n");
		}
	}
}

int is_declared(char* string){
    return 1;
}

void print_enum_info(){
	printf("Var Types Enums:\nINT: %d\nREAL: %d\n\n", INTE, REL);
	printf("Secondary Types Enums:\nARRAY: %d\nFUNCTION: %d\nSTATE: %d\n\n", ARRAY, FUNCTION, STATE);
	printf("Variable Scope Enums:\nGLOBAL: %d\nA: %d\nB: %d\nC: %d\nD: %d\nE: %d\n\n", GLOBAL, A, B, C, D, E);
}

