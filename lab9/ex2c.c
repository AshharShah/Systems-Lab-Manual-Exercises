#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    char msgToSend[] = "Bye";
    char msgRcvd[BUFSIZ];

    int pfd;
    int cfd; 

    // if(mkfifo("parentFifo", 0666) == -1){
    //     printf("Error Creating Parent Pipe\n");
    //     exit(1);
    // }

    // if(mkfifo("childFifo", 0666) == -1){
    //     printf("Error Creating Child Pipe\n");
    //     exit(1);
    // }

    pfd = open("parentFifo", O_RDONLY);
    cfd = open("childFifo", O_WRONLY);


    read(pfd, msgRcvd, BUFSIZ);
    printf("CHILD: Read: %s, from Parent!\n", msgRcvd);

    printf("CHILD: Writing: %s, to Parent!\n", msgToSend);
    write(cfd, msgToSend, strlen(msgToSend));

    close(pfd);
    close(cfd);
}