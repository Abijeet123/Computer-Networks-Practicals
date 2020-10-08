/*
	Author : Abijeet Shyam
	Experiment no : 1
	Objective : Write a program in C, using system calls, to create a text file by taking input from the
	            user for the file name and also for the contents of the file. After the file is created, copy the
		    contents of the created file to another file whose file name should also be provided by the
		    user.

*/

#include<stdio.h>
#include<fcntl.h>
#include "syscall.h"
#include<string.h>
#include<stdlib.h>
#define PERMS 0666

int main(int argc, char *argv[])
{
	int fd,fd1;
	char *c = argv[1],buf[BUFSIZ];
	if (!strcmp(c,"cr")) {
		if(creat(argv[2],PERMS) == -1)
			printf ("cr: can't create file %s\n",argv[2]);
	}

	if (!strcmp(c,"wr")){
		if ((fd = creat(argv[2],PERMS)) == -1)
			printf ("wr: can't create file %s\n",argv[2]);
		int n = strlen(argv[3]);
		if(write(fd, argv[3],n) != n)
			printf("wr: writing error\n");
	}

	if (!strcmp(c,"cp")){
		if((fd = open(argv[2],O_RDONLY,0)) == -1)
			printf("op:couldn't open file %s\n",argv[2]);
		if((fd1 = creat(argv[3],PERMS)) == -1)
			printf("cr:couldn't open file %s\n",argv[3]);

		int n;
		while((n = read(fd,buf,BUFSIZ)) > 0)
			if((write(fd1, buf, n) != n))
				printf("wr:writing error\n");
	}
	return 0;
}
