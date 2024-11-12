#include <stdio.h>
#define MAX 100

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
    
    CLOOK(requests, n, head);
    
    return 0;
}

