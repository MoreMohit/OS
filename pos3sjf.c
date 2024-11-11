//sjf 
#include<stdio.h>
#define max 30

void main()
{
	int i,j,n,t,p[max],bt[max],wt[max],tat[max],temp;
	float awt=0,atat=0;
	printf("Enter the number of process");
	scanf("%d",&n);
	printf("Enter the process number");
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	printf("Enter burst time of the process");
	for(i=0;i<n;i++)
	{
		scanf("%d",&bt[i]);
	}
	for (i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(bt[j+1]<bt[j])
			{
				temp=bt[j];
				bt[j]=bt[j+1];
				bt[j+1]=temp;

				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;

			}
		}
	}
	printf("Process\tburst time\twaiting time\tturn around time\n");
	for(i=0;i<n;i++)
	{
		wt[i]=0;
		tat[i]=0;
		for(j=0;j<i;j++)
		{
			wt[i]=wt[i]+bt[j];

		}
		tat[i]=tat[i]+bt[i];
		awt=awt+wt[i];
		atat=atat+tat[i];
 		printf("%d\t %d\t\t %d\t\t %d\n",p[i],bt[i],wt[i],tat[i]);
	}
	awt=awt/n;
	atat=atat/n;
	printf("Average waiting time=%f\n",awt);
	printf("Average turn around time=%f\n",atat);
}

