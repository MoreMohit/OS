#include <stdio.h>

int n, m, alloc[10][10], max[10][10], avail[10], need[10][10], finish[10];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

int isSafe() {
    int work[10], safeSequence[10], count = 0;
    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) break;
                
                if (j == m) {
                    for (int k = 0; k < m; k++) work[k] += alloc[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++) printf("P%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    calculateNeed();
    isSafe();
    
    return 0;
}

