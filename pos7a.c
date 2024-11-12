1. Aricever
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int res,n;
        char buffer[100];
	res=open("fifo1",O_RDONLY);
	n=read(res,buffer,100);
	printf("Reader process %d started\n",getpid());
	printf("Data received by receiver %d is: %s\n",getpid(), buffer);
}

2.Ascender

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int res,n;
	res=open("fifo1",O_WRONLY);
	write(res,"Message",7);
	printf("Sender Process %d sent the data\n",getpid());
}

3. Amkififo

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>        
int main()
{
	int res;
	res = mkfifo("fifo1",0777); //creates a named pipe with the name fifo1
	printf("named pipe created\n");
}

//Run program
gcc -o pos7a1 pos7a1.c
gcc -o pos7a2 pos7a2.c
gcc -o pos7a3 pos7a3.c

terminal 1     terminal 2
./pos7a1	./pos7a3 > output.txt
./pos7a2	cat output.txt

