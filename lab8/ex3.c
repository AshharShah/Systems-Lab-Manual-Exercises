#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// defind a signals handler, what the signals should do
void signal_handler(int sig){
    printf("Signal %d recieved\n", sig);
}

int main(int argc, char* argv[]){

    sigset_t sigset;
    // create an empty signal set
    sigemptyset(&sigset);
    // add ctrl-c and ctrl-z signals to set
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTSTP);
    // block the signals
    sigprocmask(SIG_BLOCK, &sigset, NULL);


    struct sigaction act;
    // set up the signal handler functions
    act.sa_handler = signal_handler;
    act.sa_flags = 0;
    // make an empty set
    sigemptyset(&act.sa_mask);
    // add signals to empty set
    sigaddset(&act.sa_mask, SIGINT);
    sigaddset(&act.sa_mask, SIGTSTP);
    // map signals to function
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);

    printf("Blocking CTRL-C and CTRL-Z signals\n");
    while(1){
        printf("Working...\n");
        sleep(1);
    }
    return 0;
}