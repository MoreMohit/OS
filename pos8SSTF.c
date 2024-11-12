#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void SSTF(int requests[], int n, int head) {
    int total_movement = 0, count = 0;
    int visited[MAX] = {0}; // To keep track of visited requests
    
    printf("\nSSTF Disk Scheduling\n");
    printf("Order of service: %d", head);
    
    while (count < n) {
        int min_distance = 1000000;
        int index = -1;

        // Find the closest request
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(requests[i] - head) < min_distance) {
                min_distance = abs(requests[i] - head);
                index = i;
            }
        }
        
        visited[index] = 1;
        total_movement += min_distance;
        head = requests[index];
        count++;
        
        printf(" -> %d", head);
    }
    
    printf("\nTotal head movements: %d\n", total_movement);
}

int main() {
    int n, head;
    int requests[MAX];
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    SSTF(requests, n, head);
    
    return 0;
}

