#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){
    int cfd[2];
    int pfd[2];

    if(pipe(cfd) == -1 || pipe(pfd) == -1){
        printf("Pipe Error\n");
        exit(1);
    }

    int cpid = fork();

    if(cpid == 0){
        char msgToSend[] = "Hello";
        char msgRcvd[BUFSIZ];
        printf("CHILD: Writing: %s, to Parent!\n", msgToSend);
        write(cfd[1], msgToSend, strlen(msgToSend));
        read(pfd[0], msgRcvd, BUFSIZ);
        printf("CHILD: Read: %s, from Parent!\n", msgRcvd);
    }
    else{
        char msgToSend[] = "Bye";
        char msgRcvd[BUFSIZ];

        read(cfd[0], msgRcvd, BUFSIZ);
        printf("PARENT: Read: %s, from Child!\n", msgRcvd);

        printf("PARENT: Writing: %s, to Child!\n", msgToSend);
        write(pfd[1], msgToSend, strlen(msgToSend));
    }
    return 0;
}