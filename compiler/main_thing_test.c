#include <pthread.h>
#include "structs.h"
#include "embedded.h"
#include <stdio.h>
int main(int argc, char* argv[]){
	pthread_t thread;
	void* states[] = {&&state_A,&&state_B,&&state_C,};

	if(argc > 1){
		void* ptr = states[atoi(argv[1])];
		goto *ptr;
	}
	State_GLOBAL_Struct *GLOBAL_S = malloc(sizeof(State_GLOBAL_Struct));
	GLOBAL_S->test = 0;
	GLOBAL_S->uwotm8 = 69;
	State_A_Struct A_S;
	A_S.x = -9;
	A_S.i;
	A_S.y;
	A_S.w;
	A_S.G_Struct = GLOBAL_S;
state_A:
	A_S.G_Struct->uwotm8 = 98;
	printf("A_S: %d\n",A_S.G_Struct->uwotm8);
	A_S.G_Struct->uwotm8 = 99;
	printf("Global: %d\n",GLOBAL_S->uwotm8);
	for(A_S.i = 0; A_S.i <= 10; A_S.i++){
		printf("loop 1a x: %d i: %d\n",A_S.x, A_S.i);
	}

	printf("Embeded in the code\n");if(1){printf("Inside if\n");}printf("After if\n");	
		if(A_S.x <= 9){
			printf("if 1a x: %d\n",A_S.x);
		}
	for(A_S.x = 0; A_S.x <= 10; A_S.x++){
		printf("loop 2a x: %d\n",A_S.x);
	}
	goto state_B;


	State_B_Struct B_S;
	B_S.q;
	B_S.x = 0;
	B_S.G_Struct = GLOBAL_S;
state_B:
	A_S.G_Struct->uwotm8 = 9090;
	printf("uwotm8: %d\n",B_S.G_Struct->uwotm8);
	printf("uwotm8: %d\n",GLOBAL_S->uwotm8);
	B_S.q = 9;
	if(B_S.q <= 9){
		printf("if 1b q: %d\n",B_S.q);
	}
	for(B_S.x = 2; B_S.x <= B_S.q; B_S.x++){
		printf("loop 1b x: %d q: %d\n",B_S.x, B_S.q);
	}
	goto state_C;


	State_C_Struct C_S;
	C_S.G_Struct = GLOBAL_S;
state_C:
	goto state_C;



}
