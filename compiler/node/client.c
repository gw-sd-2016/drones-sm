#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

#define PORT_TIME       13              /* "time" (not available on RedHat) */
#define PORT_FTP        1337              /* FTP connection port */
#define SERVER_ADDR     "127.0.0.1"     /* localhost */
#define MAXBUF          1024

int main(){
	int sockfd;
	struct sockaddr_in dest;
	char buffer[MAXBUF];

	/*---Open socket for streaming---*/
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
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
	if ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) != 0 )
	{
		perror("Connect ");
		exit(errno);
	}

	/*---Get "Hello?"---*/
	bzero(buffer, MAXBUF);
	recv(sockfd, buffer, sizeof(buffer), 0);
	printf("%s", buffer);
	send(sockfd, "takeoff", strlen("takeoff"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "left", strlen("left"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "right", strlen("right"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "up", strlen("up"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "down", strlen("down"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	/*
	send(sockfd, "forward", strlen("forward"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "back", strlen("back"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "flipleft", strlen("flipleft"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "clockwise", strlen("clockwise"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);
	send(sockfd, "counterclockwise", strlen("counterclockwise"),0);
	send(sockfd, "s&l", strlen("s&l"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	usleep(1105);*/
/*---Clean up---*/
	/*
	   recv(sockfd, buffer, sizeof(buffer), 0);
	   send(sockfd, "up1", strlen("up1"),0);
	   recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "down1", strlen("down1"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "up2", strlen("up2"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "down2", strlen("down2"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "s&l", strlen("s&l"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "s&l", strlen("flipleft"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "clockwise", strlen("clockwise"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "counterclockwise", strlen("counterclockwise"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	send(sockfd, "up1", strlen("up1"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "down1", strlen("down1"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "up2", strlen("up2"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "down2", strlen("down2"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "s&l", strlen("s&l"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "s&l", strlen("flipleft"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "clockwise", strlen("clockwise"),0);
	recv(sockfd, buffer, sizeof(buffer), 0);
	//	sleep(1);
	send(sockfd, "counterclockwise", strlen("counterclockwise"),0);
	 */
	close(sockfd);
	return 0;
}

