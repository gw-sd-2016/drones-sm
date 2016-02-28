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
	int position;
	int vol;
	int backup;
	int size;
}var;

int pos = 0;
var* declared_variables[64];

int string_to_int(char* string);
int add_var_dec(var* v);
int create_var(char* id, var_types t, secondary_type st, char* sc, int vo, int b);
int simple_hash();
int is_declared(char* string);
int get_vol(char* id);
int get_position(char* id);
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
	if(!strcmp(v->id, "Curr_State")) return -1;
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
			if((!strcmp(temp->id, v->id) && !strcmp(temp->scope, v->scope)) || (!strcmp(temp->id, v->id) && !strcmp(temp->scope, "GLOBAL"))){
				fprintf(stderr, "There is a duplicate variable declaration of %s within the scope %s\n", v->id, temp->scope);
				//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
				exit(-1);
				return -1;
			}
			dprintf("\nThis was not a conflict\n");
			temp = temp->next;
		}
		dprintf("After while loop Current Declaration ID is: %s\nLooking for ID %s\nScope v: %s\nScope temp: %s\n", temp->id, v->id, v->scope, temp->scope);
		if(!strcmp(temp->id, v->id) && !strcmp(temp->scope, v->scope) || (!strcmp(temp->id, v->id) && !strcmp(temp->scope, "GLOBAL"))){
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

int create_var(char* id, var_types t, secondary_type st, char* sc, int vo, int b){
	var* v = malloc(sizeof(var));
	v->id = id;
	v->type = t;
	v->stype = st;
	v->scope = sc;
	v->position = ++pos;
	v->vol = vo;
	v->backup = b;
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

void print_enum_info(){
	printf("Var Types Enums:\nINT: %d\nREAL: %d\n\n", INTE, REL);
	printf("Secondary Types Enums:\nARRAY: %d\nFUNCTION: %d\nSTATE: %d\n\n", ARRAY, FUNCTION, STATE);
	printf("Variable Scope Enums:\nGLOBAL: %d\nA: %d\nB: %d\nC: %d\nD: %d\nE: %d\n\n", GLOBAL, A, B, C, D, E);
}

void print_list(){
	int i = 0;
	var* tmp;
	for(i = 0; i < 64; i++){
		if(declared_variables[i]){
			tmp = declared_variables[i];
			while(tmp != NULL){
				while(tmp != NULL){
					dprintf("--------------------\n");
					dprintf("Var ID: %s\nVar Scope: %s\nPosition: %d\n", tmp->id, tmp->scope, tmp->position);
					dprintf("--------------------\n");
					tmp = tmp->next;
				}
			}
		}
	}
}

int get_volatile(char* id){
	int string_val;
	string_val = string_to_int(id);
	if(declared_variables[string_val] == NULL){
		dprintf("FAILED - There is no current declaration that has the same hash BUCKET-%d\n\n", string_val);
		return 0;
	}else{
		var* temp = declared_variables[string_val];
		while(temp->next != NULL){
			dprintf("Current Declaration ID is: %s\nLooking for ID %s\n", temp->id, id);
			if(!strcmp(temp->id, id)){
				dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
				//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
				return temp->vol;
			}
			dprintf("\nThis was not a conflict\n");
			temp = temp->next;
		}
		if(!strcmp(temp->id, id) && !strcmp(temp->scope, "GLOBAL")){
			dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
			//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
			return temp->vol;
		}
		return 0;
	}
}

int get_position(char* id){
	int string_val;
	string_val = string_to_int(id);
	if(!strcmp(id, "Curr_State")) return 0;
	if(declared_variables[string_val] == NULL){
		dprintf("FAILED - There is no current declaration that has the same hash BUCKET-%d\n\n", string_val);
		return -1;
	}else{
		var* temp = declared_variables[string_val];
		while(temp->next != NULL){
			dprintf("Current Declaration ID is: %s\nLooking for ID %s\n", temp->id, id);
			if(!strcmp(temp->id, id)){
				dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
				//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
				return temp->position;
			}
			dprintf("\nThis was not a conflict\n");
			temp = temp->next;
		}
		if(!strcmp(temp->id, id) && !strcmp(temp->scope, "GLOBAL")){
			dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
			//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
			return temp->position;
		}
		return -1;
	}
}

int get_backup(char* id){
	int string_val;
	string_val = string_to_int(id);
	if(declared_variables[string_val] == NULL){
		dprintf("FAILED - There is no current declaration that has the same hash BUCKET-%d\n\n", string_val);
		return 1;
	}else{
		var* temp = declared_variables[string_val];
		while(temp->next != NULL){
			dprintf("Current Declaration ID is: %s\nLooking for ID %s\n", temp->id, id);
			if(!strcmp(temp->id, id)){
				dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
				//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
				if(temp->backup == -1) return -1;
				return temp->backup++;
			}
			dprintf("\nThis was not a conflict\n");
			temp = temp->next;
		}
		if(!strcmp(temp->id, id) && !strcmp(temp->scope, "GLOBAL")){
			dprintf("ID (%s) has been found - Position %d\n", id, temp->position);
			//system("rm mainfile.c cfile"); this is dumb, but I intend on having some kind of cleanup when something fails at compelation time, otherwise it can create issues
			if(temp->backup == -1) return -1;
			return temp->backup++;
		}
		return 1;
	}
}
