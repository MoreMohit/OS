#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Define the size of the shared memory

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key (same as server's key)
    key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Locate the shared memory segment created by the server
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the client's address space
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read the message from the shared memory
    printf("Message from shared memory: %s\n", data);

    // Detach from shared memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Optionally, the client could remove the shared memory segment
    // shmctl(shmid, IPC_RMID, NULL);  // Uncomment to remove the shared memory

    return 0;
}
