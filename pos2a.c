#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int a[10],n,i,j,temp;

void getarray()
{
	printf("Enter size of array:");
	scanf("%d",&n);
	printf("Enter array of elements:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
}
void bsort()
{
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j+1]<a[j])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
void selectsort()
{
	int smallest;
	for(i=0;i<n-1;i++)
	{
		smallest = i;
		for(j=i+1;j<n;j++)
		{
			if(a[smallest]>a[j])
			{
				smallest = j;
			}
		}
		temp = a[smallest];
		a[smallest] = a[i];
		a[i] = temp;
	}
}
void display()
{
	for(i=0;i<n;i++)
	printf("%d",a[i]);
}
int main()
{
	getarray();
	pid_t pid;
	printf("\nForking......\n");
	pid = fork();
	if(pid == 0)
	{
		printf("\nChild process is Execution \n");
		printf("Child ProcessID: %d\n",getpid());
		bsort();
		display();
		printf("\nChild terminated\n");
		sleep(2);//orphan process
	}
	else if(pid<0)
	printf("ERROR!!");
	else
	{
		//wait(NULL);//to create zombie process
		printf("\nParent process is Execution \n");
		printf("Parent ProcessID: %d\n",getpid());
		selectsort();
		display();
		printf("\nParent terminated\n");
		printf("Parent existing before child to create an orphan process..\n");
	}
}												
