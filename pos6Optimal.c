#include <stdio.h>
#include <limits.h>
#define MAX_PAGES 20

typedef struct {
    char data[MAX_PAGES]; 
    int end;              
} queue;

void enqueue(queue *q, char data);
void optimal(char string[], int frameSize, int count);

int main() {
    int frameSize, count;
    char string[50];
    
    printf("Enter the page reference string (end with newline): ");
    count = 0;
    do {
        scanf("%c", &string[count]);
        count++;
    } while (string[count - 1] != '\n');
    count--;
    
    printf("\nEnter the size of the frame (minimum 3): ");
    scanf("%d", &frameSize);
    if (frameSize < 3) {
        printf("Frame size must be at least 3.\n");
        return 1;
    }
    
    printf("\nRunning Optimal page replacement algorithm...\n");
    optimal(string, frameSize, count);
    
    return 0;
}

void enqueue(queue *q, char data) {
    q->data[q->end] = data;
    q->end++;
}

void optimal(char string[], int frameSize, int count) {
    queue q;
    int pageFaults = 0;
    q.end = 0;
    printf("\nData Requested\tFrame contents\t    Page Fault\n==============================================");
    
    for (int i = 0; i < count; i++) {
        printf("\n\n\t%c", string[i]);
        int flag = 0;
        
        for (int j = 0; j < q.end; j++) {
            if (string[i] == q.data[j]) {
                flag = 1;
                break;
            }
        }
        
        if (flag == 0) {
            pageFaults++;
            if (q.end < frameSize) {
                enqueue(&q, string[i]);
            } else {
                int replaceIndex = -1, farthest = -1;
                for (int j = 0; j < q.end; j++) {
                    int found = 0;
                    for (int k = i + 1; k < count; k++) {
                        if (q.data[j] == string[k]) {
                            found = 1;
                            if (k > farthest) {
                                farthest = k;
                                replaceIndex = j;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        replaceIndex = j;
                        break;
                    }
                }
                q.data[replaceIndex] = string[i];
            }
            printf("\t  ");
            for (int j = 0; j < q.end; j++) {
                printf("%c   ", q.data[j]);
            }
            printf("\t\tY");
        } else {
            printf("\t  ");
            for (int j = 0; j < q.end; j++) {
                printf("%c   ", q.data[j]);
            }
            printf("\t\tN");
        }
    }
    
    printf("\n\n==============================================\n");
    printf("\nTotal no. of Page Faults: %d\n\n", pageFaults);
}

