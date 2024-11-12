//1. Amkififo
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>        
int main() {
    int res;
    res = mkfifo("fifo1", 0777); // Creates a named pipe with the name fifo1
    printf("Named pipe created\n");
}

//Run program
gcc -o pos7a1 pos7a1.c
gcc -o pos7a2 pos7a2.c
gcc -o pos7a3 pos7a3.c

terminal 1     terminal 2
./pos7a1	./pos7a3 > output.txt
./pos7a2	cat output.txt
