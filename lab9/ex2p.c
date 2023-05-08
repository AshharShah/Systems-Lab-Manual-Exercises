#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    char msgToSend[] = "Hello";
    char msgRcvd[BUFSIZ];

    int pfd;
    int cfd; 

    if(mkfifo("parentFifo", 0666) == -1){
        printf("Error Creating Parent Pipe\n");
        exit(1);
    }

    if(mkfifo("childFifo", 0666) == -1){
        printf("Error Creating Child Pipe\n");
        exit(1);
    }

    pfd = open("parentFifo", O_WRONLY);
    cfd = open("childFifo", O_RDONLY);

    printf("PARENT: Writing: %s, to Child!\n", msgToSend);
    write(pfd, msgToSend, strlen(msgToSend));

    read(cfd, msgRcvd, BUFSIZ);
    printf("PARENT: Read: %s, from Child!\n", msgRcvd);

    close(cfd);
    close(pfd);
}