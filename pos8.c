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

void SCAN(int requests[], int n, int head, int disk_size) {
    int total_movement = 0;
    int sorted[MAX];
    int i, j;
    
    // Sort the requests
    for (i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    sorted[n] = head; // Include the initial head position for sorting
    n++;
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    int head_index;
    for (i = 0; i < n; i++) {
        if (sorted[i] == head) {
            head_index = i;
            break;
        }
    }
    
    printf("\nSCAN Disk Scheduling\n");
    printf("Order of service: %d", head);
    
    // Move towards the end of the disk
    for (i = head_index; i < n; i++) {
        printf(" -> %d", sorted[i]);
    }
    
    // Move to the end of the disk
    printf(" -> %d", disk_size - 1);
    total_movement += (disk_size - 1) - head;
    
    // Move back to the start
    for (i = head_index - 1; i >= 0; i--) {
        printf(" -> %d", sorted[i]);
    }
    total_movement += (disk_size - 1) - sorted[0];
    
    printf("\nTotal head movements: %d\n", total_movement);
}

void CLOOK(int requests[], int n, int head) {
    int total_movement = 0;
    int sorted[MAX];
    int i, j;
    
    // Sort the requests
    for (i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    sorted[n] = head;
    n++;
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    int head_index;
    for (i = 0; i < n; i++) {
        if (sorted[i] == head) {
            head_index = i;
            break;
        }
    }
    
    printf("\nC-LOOK Disk Scheduling\n");
    printf("Order of service: %d", head);
    
    // Move towards the end
    for (i = head_index; i < n; i++) {
        printf(" -> %d", sorted[i]);
    }
    
    // Jump to the beginning of the queue
    total_movement += sorted[n - 1] - head;
    total_movement += sorted[n - 1] - sorted[0];
    
    for (i = 0; i < head_index; i++) {
        printf(" -> %d", sorted[i]);
    }
    
    printf("\nTotal head movements: %d\n", total_movement);
}

int main() {
    int n, head, disk_size;
    int requests[MAX];
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    
    SSTF(requests, n, head);
    SCAN(requests, n, head, disk_size);
    CLOOK(requests, n, head);
    
    return 0;
}

