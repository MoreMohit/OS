#include <stdio.h>
#include <limits.h> // for INT_MAX
#define max 20 // maximum size for array

int main() {
    int i, j, n, arrivalTime[max], burstTime[max], remainTime[max], totalExecutionTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int remainProcess;

    printf("Enter the Number of Processes (max 20): ");
    scanf("%d", &n);
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
        remainTime[i] = burstTime[i]; // initially assume remaining time is equal to burst time
    }

    // Track the current time
    int currentTime = 0;
    
    // Process scheduling loop
    while (remainProcess > 0) {
        int shortestIndex = -1;
        int shortestTime = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainTime[i] > 0 && remainTime[i] < shortestTime) {
                shortestTime = remainTime[i];
                shortestIndex = i;
            }
        }

        if (shortestIndex != -1) {
            // Execute the shortest job for 1 time unit
            remainTime[shortestIndex]--;
            totalExecutionTime++;
            currentTime++;

            // If the process is completed
            if (remainTime[shortestIndex] == 0) {
                int turnaroundTime = currentTime - arrivalTime[shortestIndex];
                int waitingTime = turnaroundTime - burstTime[shortestIndex];
                
                printf("P[%d] | Waiting Time: %d | Turnaround Time: %d\n", 
                        shortestIndex + 1, waitingTime, turnaroundTime);
                
                totalWaitingTime += waitingTime;
                totalTurnaroundTime += turnaroundTime;
                remainProcess--;
            }
        } else {
            // No process is ready to execute, move time forward
            currentTime++;
        }
    }

    // Calculate averages
    totalWaitingTime = (float)totalWaitingTime / n;
    totalTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nThe Average Waiting Time: %.2f\n", totalWaitingTime);
    printf("The Average Turnaround Time: %.2f\n", totalTurnaroundTime);

    return 0;
}

