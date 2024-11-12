#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define MAXSIZE 27

void die(char *s)
{
	perror(s);
	exit(1);
}

int main()
{
	int shmid;
	key_t key = 5678;
	char *shm;
	
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
		
	if((shm = shmat(shmid, NULL, 0)) == (char *) -1)
		die("shmat");
		
	printf("Enter a Message to write to shared memory: ");
	fgets(shm,MAXSIZE,stdin);
	
	printf("Waiting for client...\n");
	while (*shm != '*')
		sleep(1);
	
	shmdt(shm);
	return 0;
}		
