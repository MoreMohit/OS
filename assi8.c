#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void SSTF();
void SCAN();
void CLOOK();

int main() {
    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1: SSTF\n2: SCAN\n3: CLOOK\n4: EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: SSTF(); break;
            case 2: SCAN(); break;
            case 3: CLOOK(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    } while (1);
    return 0;
}

void SSTF() {
    int requests[MAX_REQUESTS], n, initial, totalHeadMovement = 0;

    printf("Enter number of Requests: ");
    scanf("%d", &n);
    printf("Enter Requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &initial);

    for (int count = 0; count < n; count++) {
        int minDistance = __INT_MAX__, index = -1;
        for (int i = 0; i < n; i++) {
            int distance = abs(requests[i] - initial);
            if (distance < minDistance) {
                minDistance = distance;
                index = i;
            }
        }
        totalHeadMovement += minDistance;
        initial = requests[index];
        requests[index] = __INT_MAX__; // Mark as visited
    }
    printf("Total head movement is %d\n", totalHeadMovement);
}

void SCAN() {
    int requests[MAX_REQUESTS], n, initial, size, totalHeadMovement = 0, direction;

    printf("Enter number of Requests: ");
    scanf("%d", &n);
    printf("Enter Requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position and disk size: ");
    scanf("%d %d", &initial, &size);
    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }

    int index;
    for (index = 0; index < n; index++) if (initial < requests[index]) break;

    if (direction == 1) {
        for (int i = index; i < n; i++) {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];
        }
        totalHeadMovement += abs(size - 1 - initial);
        initial = size - 1;
        for (int i = n - 1; i >= index; i--) {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];
        }
        totalHeadMovement += abs(0 - initial);
        initial = 0;
        for (int i = index; i < n; i++) {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];
        }
    }
    printf("Total head movement is %d\n", totalHeadMovement);
}

void CLOOK() {
    int requests[MAX_REQUESTS], n, initial, totalHeadMovement = 0;

    printf("Enter number of Requests: ");
    scanf("%d", &n);
    printf("Enter Requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &initial);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }

    int index;
    for (index = 0; index < n; index++) if (initial < requests[index]) break;

    for (int i = index; i < n; i++) {
        totalHeadMovement += abs(requests[i] - initial);
        initial = requests[i];
    }
    if (index > 0) {
        totalHeadMovement += abs(requests[0] - initial);
        initial = requests[0];
        for (int i = 0; i < index; i++) {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];
        }
    }
    printf("Total head movement is %d\n", totalHeadMovement);
}
