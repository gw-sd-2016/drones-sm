#include <stdarg.h>
#include <time.h>
#include <stddef.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include "structs.h"
#include <stdio.h>
#include <errno.h>


#define PORT_TIME       13              /* "time" (not available on RedHat) */
#define PORT_FTP        1337              /* FTP connection port */
#define SERVER_ADDR     "127.0.0.1"     /* localhost */
#define MAXBUF          1024

void file_restore_global_values(State_GLOBAL_Struct *GLOBAL_S);
void file_update_backup(int update_version, int position, int type, ...);

int main(int argc, char* argv[]){
	int sockfd, n, o, s = 0, state = 0;
	char *address = "127.0.0.1";

	int sockf;
	struct sockaddr_in dest;
	char buffer[MAXBUF];

	/*---Open socket for streaming---*/
	if ( (sockf = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

	/*---Initialize server address/port struct---*/
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT_FTP);
	if ( inet_aton(SERVER_ADDR, &dest.sin_addr.s_addr) == 0 )
	{
		perror(SERVER_ADDR);
		exit(errno);
	}

	/*---Connect to server---*/
	if ( connect(sockf, (struct sockaddr*)&dest, sizeof(dest)) != 0 )
	{
		perror("Connect ");
		exit(errno);
	}

	while ((o = getopt (argc, argv, "h:s:")) != -1) {
		switch(o){
			case 'h':
				address = optarg;
				break;
			case 's':
				s = 1;
				state = atoi(optarg);
				break;
		}
	}

	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof servaddr);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	inet_pton(AF_INET, address, &(servaddr.sin_addr));
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	pthread_t thread;
	void* states[] = {&&state_A,&&state_B,&&state_C,&&state_D,&&state_E,&&state_F,&&state_Recv};

	void* start_ptr = &&state_A;
	State_GLOBAL_Struct GLOBAL_S;
	unsigned char* data = malloc(sizeof(GLOBAL_S));
	GLOBAL_S.test = 0;
	GLOBAL_S.var1 = 99;
	GLOBAL_S.var2 = 0;
	if( access("backup.txt", F_OK) != -1 ) {
		printf("file exists\n");
		printf("BEFORE Value of first: %d\n", GLOBAL_S.test);
		printf("BEFORE Value of first: %d\n", GLOBAL_S.var1);
		printf("BEFORE Value of first: %d\n", GLOBAL_S.var2);
		file_restore_global_values(&GLOBAL_S);
		printf("AFTER Value of first: %d\n", GLOBAL_S.test);
		printf("AFTER Value of first: %d\n", GLOBAL_S.var1);
		printf("AFTER Value of first: %d\n", GLOBAL_S.var2);
	} else {
		printf("file doesn't exist\n");
	}
	if(s){
		void* ptr = states[state];
		goto *ptr;
	}
	else{
		goto *start_ptr;
	}
begin:;
state_A:;
		GLOBAL_S.Curr_State = 0;
		bzero(buffer, MAXBUF);
		recv(sockf, buffer, sizeof(buffer), 0);
		printf("%s", buffer);
		send(sockf, "takeoff", strlen("takeoff"),0);
		usleep(1105);
		GLOBAL_S.Curr_State += 1;
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_B:;
		send(sockf, "up1", strlen("up1"),0);
		GLOBAL_S.Curr_State += 1;
		usleep(1105);
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_C:;
		send(sockf, "down1", strlen("down1"),0);
		GLOBAL_S.Curr_State += 1;
		usleep(1105);
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_D:;
		send(sockf, "up2", strlen("up2"),0);
		GLOBAL_S.Curr_State += 1;
		usleep(1105);
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_E:;
		send(sockf, "flipleft", strlen("flipleft"),0);
		GLOBAL_S.Curr_State += 1;
		usleep(1105);
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_F:;
		send(sockf, "s&l", strlen("s&l"),0);
		GLOBAL_S.Curr_State += 1;
		usleep(1105);
		printf("Next State: %d\n", GLOBAL_S.Curr_State);
		goto state_Recv;

state_Recv:;
		recv(sockf, buffer, sizeof(buffer), 0);
		printf("Recieving, next state %d\n", GLOBAL_S.Curr_State);
		void* ptr = states[GLOBAL_S.Curr_State];
		goto *ptr;

}
void file_restore_global_values(State_GLOBAL_Struct *GLOBAL_S){
	FILE* restore = fopen("backup.txt", "r");
	char * value_char = NULL;
	int pos = 0;
	int value = 0;
	size_t len = 0;
	while ((getline(&value_char, &len, restore)) != -1) {
		if(strcmp(value_char, "\n")){
			value = atoi(value_char);
			memcpy(&GLOBAL_S->Curr_State + pos, &value, sizeof(int));
			//printf("Retrieved: %d at position: %d\n", value, pos);
		}
		pos++;
	}
}
void file_update_backup(int update_versioni, int position, int type, ...){
	FILE* original = fopen("backup.txt", "r");
	FILE* temp = fopen("backup_temp.txt", "w");
	char * value_char = NULL;
	int pos = 0;
	va_list list;
	va_start(list, type);
	size_t len = 0;

	while ((getline(&value_char, &len, original)) != -1) {
		if(pos != position){
			fprintf(temp, "%s", value_char);
		}else {
			if(type == 0){
				fprintf(temp, "%d\n", va_arg(list, int));
				//printf("arg int\n");
			}else if(type == 1){
				fprintf(temp, "%f\n", va_arg(list, double));
				//printf("arg double\n");
				//fprintf(temp, "%s\n", value_char);
			}else if(type == 2){
				fprintf(temp, "%s\n", va_arg(list, char*));
				//printf("arg char*\n");
			}
		}
		pos++;
	}
	va_end(list);
	fclose(original);
	fclose(temp);
	system("cat backup_temp.txt > backup.txt;rm backup_temp.txt");
}
