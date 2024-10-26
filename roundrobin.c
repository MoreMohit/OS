#include<stdio.h>
#define max 20 // maximum size for array

int main() {
    int i, burstTime[max], remainTime[max], remainProcess, arrivalTime[max], totalExecutionTime = 0, timeQuantum, flag = 0, n;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    printf("Enter the Number of Process(max 20) : ");
    scanf("%d", &n); // n is the number of Process
    remainProcess = n;

    printf("Enter Arrival Time\n");
    for(i = 0; i < n; i++) {
        printf("For P[%d]: ", i + 1);
        scanf("%d", &arrivalTime[i]);
    }

    printf("\nEnter Burst Time\n");
    for(i = 0; i < n; i++) {
        printf("For P[%d]: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainTime[i] = burstTime[i]; // initially assume remain time for any process is equal to its burst time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &timeQuantum);

    printf("\n");
    for(i = 0; remainProcess != 0; ) {
        if(remainTime[i] <= timeQuantum && remainTime[i] > 0) {
            totalExecutionTime += remainTime[i];
            remainTime[i] = 0;
            flag = 1;
        } else if(remainTime[i] > 0) {
            remainTime[i] -= timeQuantum;
            totalExecutionTime += timeQuantum;
        }

        if(flag == 1 && remainTime[i] == 0) {
            int turnaroundTime = totalExecutionTime - arrivalTime[i];
            printf("P[%d] | Waiting Time: %d | Turnaround Time: %d\n", 
                    i + 1, 
                    totalExecutionTime - arrivalTime[i] - burstTime[i], 
                    turnaroundTime);
            totalWaitingTime += totalExecutionTime - arrivalTime[i] - burstTime[i];
            totalTurnaroundTime += turnaroundTime;
            flag = 0;
            remainProcess--;
        }

        if(i == n - 1)
            i = 0;
        else if(arrivalTime[i + 1] <= totalExecutionTime)
            i++;
        else
            i = 0;
    }

    totalWaitingTime = (float)totalWaitingTime / n;
    totalTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nThe Average Waiting Time: %.2f\n", totalWaitingTime);
    printf("The Average Turnaround Time: %.2f\n", totalTurnaroundTime);

    return 0;
}

