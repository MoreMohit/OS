#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
	printf("Descending array");
	for(int j=argc-1;j>=0;j--)
	{
		printf("%s",argv[j]);
	}printf("\n");
	exit(EXIT_SUCCESS);
}	
	
