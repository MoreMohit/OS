#include <stdio.h>
#define MAX 20

int is_page_in_frame(int frames[], int frame_size, int page) {
    for (int i = 0; i < frame_size; i++) {
        if (frames[i] == page)
            return 1; // Page is found
    }
    return 0; // Page not found
}
// LRU Page Replacement Algorithm
void lru(int pages[], int n, int frame_size) 
{
    int frames[MAX], recent[MAX] = {0}, page_faults = 0, time = 0, occupied = 0;
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nLRU Page Replacement Algorithm:\n");

    for (int i = 0; i < n; i++) {
        printf("Page %d: ", pages[i]);
        if (!is_page_in_frame(frames, frame_size, pages[i])) {
            if (occupied < frame_size) {
                frames[occupied] = pages[i];
                occupied++;
            } else {
                int lru_index = 0;
                for (int j = 1; j < frame_size; j++) {
                    if (recent[j] < recent[lru_index])
                        lru_index = j;
                }
                frames[lru_index] = pages[i];
            }
            page_faults++;
            printf("Page fault! Frames: ");
        } else {
            printf("No page fault. Frames: ");
        }
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                recent[j] = time++;
                break;
            }
        }
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

int main() {
    int n, frame_size, pages[MAX];
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string (page numbers): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the frame size (minimum 3): ");
    scanf("%d", &frame_size);

    if (frame_size < 3) {
        printf("Frame size should be at least 3!\n");
        return 1;
    }

    lru(pages, n, frame_size);
    return 0;
}
