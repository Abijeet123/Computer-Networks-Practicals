/*
	Author : Abijeet Shyam
	Roll no : 18BTechIT32
	Date	: 30-11-20
	Program : Echo server using tcp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int sockfd, newsockfd, portno, clilen, n;

	if(argc < 2)
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)	error("ERROR opening socket");

	 printf("Socket created successfully\n");

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)	error("ERROR on binding"); 
	printf("Binding sucessfull\n");

	listen(sockfd,2);
	printf("Listening....");
	clilen	= sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd < 0)	error("ERROR on accept");
	printf("Connection accepted\n");
	bzero(buffer,256);
	
	n = read(newsockfd,buffer,255);

	if(n < 0)
		error("ERROR reading from socket");

	printf("Here's the messags %s\n",buffer);
	
	char sent_message[] = "echoed back: ";
	
	n = write(newsockfd,buffer,sizeof(buffer));

	if(n < 0)
		error("ERROR writing to socket"); 



  
	return 0;
}
