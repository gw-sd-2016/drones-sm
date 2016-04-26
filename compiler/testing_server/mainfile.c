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
void* states[] = {&&state_A,&&state_B,&&state_C,};

void* start_ptr = &&state_A;
State_GLOBAL_Struct GLOBAL_S;
unsigned char* data = malloc(sizeof(GLOBAL_S));
GLOBAL_S.Prev_State = 0;
GLOBAL_S.test = 9;
if( access("backup.txt", F_OK) != -1 ) {
    printf("file exists\n");
//printf("BEFORE Value of first: %d\n", GLOBAL_S.test);
//printf("BEFORE Value of first: %d\n", GLOBAL_S.var1);
//printf("BEFORE Value of first: %d\n", GLOBAL_S.var2);
file_restore_global_values(&GLOBAL_S);
void* ptr;
if(!GLOBAL_S.Curr_State) ptr = states[GLOBAL_S.Curr_State];
else ptr = states[GLOBAL_S.Curr_State + 0];
goto *ptr;
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

GLOBAL_S.Curr_State = 0;
send(drone_sockfd, "takeoff", strlen("takeoff"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
file_update_backup(9, 0, 0, GLOBAL_S.Curr_State);
goto state_B;


state_B:;
State_B_Struct B_S;

GLOBAL_S.Curr_State = 1;
GLOBAL_S.Prev_State = 0;
send(drone_sockfd, "up", strlen("up"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
send(drone_sockfd, "stop", strlen("stop"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
sleep(3);
send(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct), 0);
usleep(1105);
file_update_backup(9, 0, 0, GLOBAL_S.Curr_State);
goto state_C;


state_C:;
State_C_Struct C_S;

GLOBAL_S.Curr_State = 2;
GLOBAL_S.Prev_State = 1;
send(drone_sockfd, "down", strlen("down"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
send(drone_sockfd, "stop", strlen("stop"),0);
recv(drone_sockfd, drone_buffer, sizeof(drone_buffer), 0);
usleep(1105);
sleep(3);
send(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct), 0);
usleep(1105);
file_update_backup(9, 0, 0, GLOBAL_S.Curr_State);
goto state_B;



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
