#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sort(arr, n);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[n + 2];
        args[0] = (char *)"./child";  // The executable for the child process
        for (int i = 0; i < n; i++) {
            args[i + 1] = (char *)malloc(12 * sizeof(char));  // Allocate space for each integer argument
            snprintf(args[i + 1], 12, "%d", arr[i]);  // Convert integer to string
        }
        args[n + 1] = NULL;

        execve("./child.out", args, NULL);
        perror("execve failed");

        // Free allocated memory
        for (int i = 1; i <= n; i++) {
            free(args[i]);
        }
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("fork failed");
    }

    return 0;
}
