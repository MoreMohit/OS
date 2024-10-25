#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int a[], int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }
}

void display(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\t\t", a[i]);
    }
    printf("\n");
}

int main() {
    int pid, child_id;
    int size, i;

    printf("Enter the number of Integers to Sort::::\t");
    scanf("%d", &size);

    int a[size];
    int pArr[size];
    int cArr[size];

    for (i = 0; i < size; i++) {
        printf("Enter number %d:", (i + 1));
        scanf("%d", &a[i]);
        pArr[i] = a[i];
        cArr[i] = a[i];
    }
    printf("Your Entered Integers for Sorting\n");
    display(a, size);

    pid = getpid();
    printf("Parent process id is %d\n", pid);

    printf("Child process FORKED \n");
    child_id = fork();
    if (child_id < 0) {
        printf("\nChild Process Creation Failed!!!!\n");
        exit(-1);
    } else if (child_id == 0) {
        printf("Child process called....\n");
        printf("id of child process %d \n", getpid());
        printf("Parent of child process is %d \n", getppid());
        printf("Sorting by child process by bubble sort\n");
        bubblesort(cArr, size);
        printf("The sorted List by Child::\n");
        display(cArr, size);

        printf("Sleeping for 10 seconds to demonstrate orphan process...\n");
        sleep(10);

        printf("Child Process Completed ...\n");
        exit(0);  // Child exits
    } else {
        // Commenting out wait() to create a zombie process
        // wait(NULL);

        printf("Parent process is being called\n");
        pid = getpid();
        printf("Pid of parent process %d \n", pid);
        printf("\nParent of parent process is %d \n", getppid());
        printf("Sorting by parent process by selectionSort \n");
        selectionSort(pArr, size);
        printf("The sorted List by Parent::\n");
        display(pArr, size);

        printf("Parent Process Completed ...\n");

        printf("Parent exiting before child to create an orphan process...\n");
        exit(0);  // Parent exits, child becomes an orphan
    }
    return 0;
}
