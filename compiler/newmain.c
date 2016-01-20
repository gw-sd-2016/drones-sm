//TODO ADD THESE TO THE PARSER
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
//TODO ADD THESE TO THE PARSER
#include <pthread.h>
#include "structs.h"
#include "embedded.h"
#include <stdio.h>
int main(int argc, char* argv[]){

	int sockfd, n;
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof servaddr);

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);

	inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	pthread_t thread;
	void* states[] = {&&state_A,&&state_B,&&state_C,};

	if(argc > 1){
		void* ptr = states[atoi(argv[1])];
		goto *ptr;
	}

	State_GLOBAL_Struct GLOBAL_S;
	GLOBAL_S.test = 0;
	GLOBAL_S.uwotm8 = 69;
	State_A_Struct A_S;
	A_S.x = -9;
	A_S.i;
	A_S.y;
	A_S.w;
	A_S.G_Struct = GLOBAL_S;
	unsigned char* data = malloc(sizeof(GLOBAL_S));
state_A:
	GLOBAL_S.uwotm8 = 696969;
	GLOBAL_S.Curr_State = 0;
	memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
	write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
	read(sockfd, recvline, sizeof(State_GLOBAL_Struct));
	printf("Received: %d\n",GLOBAL_S.uwotm8);
	printf("x: %d\n",A_S.x);
	printf("State: %d\n",GLOBAL_S.Curr_State);
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
	GLOBAL_S.Curr_State = 1;
	printf("State: %d\n",GLOBAL_S.Curr_State);
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
	GLOBAL_S.Curr_State = 2;
	printf("State: %d\n",GLOBAL_S.Curr_State);
	//	goto state_C;



}
