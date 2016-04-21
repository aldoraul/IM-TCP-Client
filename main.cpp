/* CS 423 Project 3
	TCP Client
	Aldo Anaya
*/

#include<cstdlib>
#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<iostream>
//#include"cipher.h"

#define MAXDATASIZE 500

int main(int argc, char *argv[]){

	int sockfd, recv_byte;
	char buf[100];
	struct addrinfo server_struct, *servinfo, *p;
	int return_value;
	char s[INET6_ADDRSTRLEN];
	

	memset(&server_struct, 0, sizeof server_struct);
	server_struct.ai_family = AF_UNSPEC;
	server_struct.ai_socktype = SOCK_STREAM;
	
	if((return_value = getaddrinfo("192.168.10.200", "34567", &server_struct, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(return_value));
		return 1;
		}

	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

	inet_ntop(servinfo->ai_family, &(((struct sockaddr_in*)servinfo->ai_addr)->sin_addr),s,sizeof s);
	printf("Connecting to %s\n", s);

	freeaddrinfo(servinfo);
	
	if((recv_byte = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
		}
	buf[recv_byte] = '\0';
	printf("Get Response \n \t%s", buf);
	close(sockfd);
	return 0;
}	




