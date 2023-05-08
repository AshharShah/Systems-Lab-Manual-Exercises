#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype; // message type
    char mtext[100]; // message text
};

int main() {
    struct message msg;
    int key = 123456;
    int msgid;
    
    // get message queue id
    if ((msgid = msgget(key, 0644)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    // receive message
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    
    printf("Message received: %s\n", msg.mtext);
    
    // delete message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    
    return 0;
}