#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define n 5
int arr[n];

void printarray(int arr[])
{
	for(int i=0;i<n;i++)
		printf("%d", arr[i]);
	printf("\n");
}

void bsort(int arr[],int size)
{
	int i,j,temp;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size-i-1;j++)
		{
			if (arr[j]>arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printarray(arr);
}

void accept(int arr[])
{
	printf("\nEnter array elements:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
}

int main(int argc, char *argv[])
{
	int pid;
	char *args[n+1];
	char sortedarray[n+1][12];
	accept(arr);
	bsort(arr,n);
	pid = fork();
	if(pid<0)
	{
		return 1;
	}
	if(pid == 0)
	{
		printf("Child process:\n");
		for(int i=0;i<n;i++)
		{
			sprintf(sortedarray[i], "%d",arr[i]);
			args[i] = sortedarray[i];
		}
		args[n] = NULL;
		execve("./2bchild.out", args, NULL);
		perror("execve");
		return 1;
	}
	else if(pid>0)
	{
		wait(NULL);
		printf("Parent process:\n");
	}
	return 0;
}										

