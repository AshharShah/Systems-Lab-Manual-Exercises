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
    
    
    // create message queue
    if ((msgid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    // set message type and text
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from the message queue writer!");
    
    // send message
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    
    printf("Message sent: %s\n", msg.mtext);
    
    return 0;
}