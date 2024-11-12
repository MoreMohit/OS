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
	char *shm, *s;
	
	if((shmid = shmget(key, MAXSIZE, 0666)) < 0)
		die("shmget");
		
	if((shm = shmat(shmid, NULL, 0)) == (char *) -1)
		die("shmat");
		
	printf("Message from server: %s", shm);	
	
	*shm = '*';
	shmdt(shm);
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}	
