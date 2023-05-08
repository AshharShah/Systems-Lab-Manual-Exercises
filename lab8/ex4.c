#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    char buffer[5] = {"Hello"};
    printf("Buffer Contents: %s\n", buffer);

    struct sigaction act;
    act.sa_handler = SIG_IGN;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGSEGV, &act, NULL);

    // signal(SIGSEGV, SIG_IGN);

    buffer[5] = '!';
    printf("Buffer Contents: %s\n", buffer); 

    // Check whether program is still running
    printf("Program still running\n");  

    return 0;
}