#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void die(char* s)
{
    perror(s);
    exit(1);
}


struct msgbuf
{
    long mtype;
    char mtext[128];
};

int main()
{
    int msqid;
    key_t key;
    struct msgbuf rcvbuffer;

    key = 1234;

    if((msqid = msgget(key, 0666))< 0)
        die("msgget()");

    for(int i=0; i < 101; i++){
        if(msgrcv(msqid, &rcvbuffer, 128, i, IPC_NOWAIT) < 0)
            die("msgrcv");
        printf("%s\n", rcvbuffer.mtext);
    }

    exit(1);
}