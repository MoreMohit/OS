#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 10

pthread_mutex_t mutex;
pthread_t tid[100];
sem_t empty,full;
int buffer[BUFFER_SIZE];
int counter;
void *producer(void *arg);
void *consumer(void *arg);
void insert_item(int item);
int remove_item();

void initialize()
{
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);
}

void insert_item(int item)
{
	buffer[counter++] = item;
}

int remove_item()
{
	return buffer[--counter];
}

void *producer(void *arg)
{
	int item,wait_time;
	wait_time = rand() % 5;
	sleep(wait_time);
	item = rand() % 10;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	printf("Producer produced %d\n\n", item);
	insert_item(item);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return NULL;
}

void *consumer(void *arg)
{
	int item,wait_time;
	wait_time  = rand() % 5;
	sleep(wait_time);
	//item = rand() % 10;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	item = remove_item();
	printf("Consumer consumed %d\n\n", item);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	return NULL;
}

int main()
{
	int n1,n2;
	int i;
	printf("Enter number of Producer:");
	scanf("%d", &n1);
	printf("Enter number of Consumer:");
	scanf("%d",&n2);
	initialize();
	for(i=0;i<n1;i++)
	{
		if(pthread_create(&tid[i],NULL,producer,NULL) != 0)
		{
			perror("Failed to create producer thread");
		}
	}
	for(i=0;i<n2;i++)
	{
		if(pthread_create(&tid[n1 + i],NULL,consumer,NULL) != 0)
		{
			perror("Failed to create consumer thread");
		}
	}
	for (i=0;i<n1 + n2; i++)
	{
		pthread_join(tid[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}		
