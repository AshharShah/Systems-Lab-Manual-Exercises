#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>

#define KEY 12345678 // a unique key for the semaphore set
#define SEM_NUM 1    // number of semaphores in the set
#define SEM_VAL 1    // initial value of the semaphore

int main() {
    int semid, pid;
    struct sembuf wait_op = {0, -1, 0}; // semaphore wait operation (decrement)
    struct sembuf signal_op = {0, 1, 0}; // semaphore signal operation (increment)
    
    // create a new semaphore set or get an existing one
    if ((semid = semget(KEY, SEM_NUM, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }
    
    // initialize the semaphore value (to 1)
    if (semctl(semid, 0, SETVAL, SEM_VAL) == -1) {
        perror("semctl");
        exit(1);
    }
    
    // fork a child process
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    
    // parent process
    if (pid > 0) {
        printf("Parent process (PID=%d) is entering the critical section.\n", getpid());
        
        // wait for the semaphore to become available
        if (semop(semid, &wait_op, 1) == -1) {
            perror("semop");
            exit(1);
        }
        
        // critical section
        printf("Parent process (PID=%d) is in the critical section.\n", getpid());
        sleep(5); // simulate some work in the critical section
        
        // signal the semaphore to release it
        if (semop(semid, &signal_op, 1) == -1) {
            perror("semop");
            exit(1);
        }
        
        printf("Parent process (PID=%d) is leaving the critical section.\n", getpid());
        wait(NULL);
    }
    
    // child process
    else {
        printf("Child process (PID=%d) is entering the critical section.\n", getpid());
        
        // wait for the semaphore to become available
        if (semop(semid, &wait_op, 1) == -1) {
            perror("semop");
            exit(1);
        }
        
        // critical section
        printf("Child process (PID=%d) is in the critical section.\n", getpid());
        sleep(3); // simulate some work in the critical section
        
        // signal the semaphore to release it
        if (semop(semid, &signal_op, 1) == -1) {
            perror("semop");
            exit(1);
        }
        
        printf("Child process (PID=%d) is leaving the critical section.\n", getpid());
    }
    
    return 0;
}