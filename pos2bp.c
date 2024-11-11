#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int i,n,j,arr[10];

void getarr()
{
	printf("Enter number of array elements:");
	scanf("%d",&n);
	printf("Enter array elements:");
	for(i=0;i<n;i++)
	scanf("%d",&arr[i]);
}

int partition (int a[],int start,int end)
{
	int pivot = a[end];
	int i = (start - 1);
	for(int j=start;j<=end - 1;j++)
	{
		if(a[j]<pivot)
		{
			i++;
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	int t = a[i+1];
	a[i+1] =a[end];
	a[end] = t;
	return (i+1);
}

void quick (int a[],int start,int end)
{
	if(start<end)
	{
		int p = partition (a, start,end);
		quick(a, start,p-1);
		quick(a,p+1,end);
	}
}

int main(int argc,char *argv[])
{
	pid_t  pid;
	char *carr[12] = {NULL};
	getarr();
	printf("\nAfter sorting array elements are :");
	quick(arr,0,n-1);
	for(int j=0;j<n;j++)
	{
		printf("%d",arr[j]);
	}
	printf("\n");
	char *newenviron[] = {NULL};
	for(i=0;i<n;i++)
	{
		char c[sizeof(int)];
		snprintf(c,sizeof(int),"%d",arr[i]);
		carr[i]= malloc(sizeof(c));
		strcpy(carr[i],	c);
	}
	if(argc != 2)
	{
		fprintf(stderr,"Usage: %s <file-ttoexec>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	execve(argv[1],carr,newenviron);
	perror("execve");
}
