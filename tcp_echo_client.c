#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define check(c) if(c < 0)

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if(argc < 3)
	{
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	check(sockfd) error("ERROR opening socket");
	server	= gethostbyname(argv[1]);

	if(server == NULL)
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);	
	}

	bzero((char *) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

	serv_addr.sin_port = htons(portno);

	if(connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
	
	printf("Enter message : ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(sockfd,buffer,strlen(buffer));

	check(n)	error("ERROR writing to socket");

	n = read(sockfd,buffer,255);
	check(n)
		error("ERROR reading from socket");

	printf("%s\n",buffer);
	return 0;

}
