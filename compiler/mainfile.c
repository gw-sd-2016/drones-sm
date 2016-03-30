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
#include <errno.h>
#define PORT_TIME 13
#define PORT_FTP 1337
#define SERVER_ADDR "127.0.0.1"
#define MAXBUF 1024
#include <stdio.h>
void file_restore_global_values(State_GLOBAL_Struct *GLOBAL_S);
void file_update_backup(int update_version, int position, int type, ...);

int main(int argc, char* argv[]){
    int drone_sockfd;
    struct sockaddr_in drone_dest;
    char drone_buffer[MAXBUF];

    /*---Open socket for streaming---*/
    if ( (drone_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("Socket");
        exit(errno);
    }

    /*---Initialize server address/port struct---*/
    bzero(&drone_dest, sizeof(drone_dest));
    drone_dest.sin_family = AF_INET;
    drone_dest.sin_port = htons(PORT_FTP);
    if ( inet_aton(SERVER_ADDR, &drone_dest.sin_addr.s_addr) == 0 )
    {
        perror(SERVER_ADDR);
        exit(errno);
    }

    /*---Connect to server---*/
    if ( connect(drone_sockfd, (struct sockaddr*)&drone_dest, sizeof(drone_dest)) != 0 )
    {
        perror("Connect ");
        exit(errno);
    }

    /*---Get "Hello?"---*/
    bzero(drone_buffer, MAXBUF);
	recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
    printf("%s", drone_buffer);
int sockfd, n, o, s = 0, state = 0;
char *address = "127.0.0.1";
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
void* states[] = {&&state_A,&&state_A,&&state_B,&&state_C,};

void* start_ptr = &&state_A;
State_GLOBAL_Struct GLOBAL_S;
unsigned char* data = malloc(sizeof(GLOBAL_S));
GLOBAL_S.test = 0;
GLOBAL_S.var1 = 99;
GLOBAL_S.var2 = 0;
if( access("backup.txt", F_OK) != -1 ) {
    printf("file exists\n");
//printf("BEFORE Value of first: %d\n", GLOBAL_S.test);
//printf("BEFORE Value of first: %d\n", GLOBAL_S.var1);
//printf("BEFORE Value of first: %d\n", GLOBAL_S.var2);
file_restore_global_values(&GLOBAL_S);
//printf("AFTER Value of first: %d\n", GLOBAL_S.test);
//printf("AFTER Value of first: %d\n", GLOBAL_S.var1);
//printf("AFTER Value of first: %d\n", GLOBAL_S.var2);
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
State_A_Struct A_S;
A_S.x = 9;
A_S.i;
A_S.y;
A_S.w;
A_S.x = 10;
A_S.i = 1;
GLOBAL_S.var1 = 999;
char* data_var1 = malloc(sizeof(GLOBAL_S.var1) + sizeof(int));
memset(data_var1, 2, 1);
memcpy(&data_var1[1], &GLOBAL_S.var1, sizeof(int));
send(sockfd, &data_var1, sizeof(data_var1), 0);
GLOBAL_S.test = 1;
char* data_test = malloc(sizeof(GLOBAL_S.test) + sizeof(int));
memset(data_test, 1, 1);
memcpy(&data_test[1], &GLOBAL_S.test, sizeof(int));
send(sockfd, &data_test, sizeof(data_test), 0);
GLOBAL_S.var1 = 9;
memset(data_var1, 2, 1);
memcpy(&data_var1[1], &GLOBAL_S.var1, sizeof(int));
send(sockfd, &data_var1, sizeof(data_var1), 0);
GLOBAL_S.var2 = 9;
printf("x: %d\n",A_S.x);
GLOBAL_S.test = 1;
memset(data_test, 1, 1);
memcpy(&data_test[1], &GLOBAL_S.test, sizeof(int));
send(sockfd, &data_test, sizeof(data_test), 0);
for(A_S.i = 0; A_S.i <= 10; A_S.i++){
printf("loop 1a x: %d i: %d\n",A_S.x, A_S.i);
}
if(A_S.x <= 9){

GLOBAL_S.Curr_State = 0;
send(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct), 0);
goto state_C;
printf("if 1a x: %d\n",A_S.x);
}
for(A_S.x = 0; A_S.x <= 10; A_S.x++){
printf("loop 2a x: %d\n",A_S.x);
}
send(drone_sockfd, "up", strlen("up"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
send(drone_sockfd, "down", strlen("down"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
send(drone_sockfd, "clockwise", strlen("clockwise"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
send(drone_sockfd, "flipleft", strlen("flipleft"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);

GLOBAL_S.Curr_State = 1;
send(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct), 0);
goto state_C;


state_B:;
State_B_Struct B_S;
B_S.q;
B_S.x = 0;
B_S.q = 9;
if(B_S.q <= 9){
printf("if 1b q: %d\n",B_S.q);
}
for(B_S.x = 2; B_S.x <= B_S.q; B_S.x++){
printf("loop 1b x: %d q: %d\n",B_S.x, B_S.q);
}
goto state_A;


state_C:;
State_C_Struct C_S;
goto state_C;



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
