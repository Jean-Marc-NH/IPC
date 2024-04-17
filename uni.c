#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void die(char* s, int i)
{
    perror(s);
    i = 200;
}


struct msgbuf
{
    long mtype;
    char mtext[128];
};

int main()
{
    for(;;)
    {
            int msqid;
    key_t key;
    struct msgbuf rcvbuffer;

    key = 4321;

    if((msqid = msgget(key, 0606))< 0)
        die("msgget()", 0);

    for(int i=0; i < 101; i++){
        if(msgrcv(msqid, &rcvbuffer, 128, i, IPC_NOWAIT) < 0)
            die("msgrcv", i);
        printf("%s\n", rcvbuffer.mtext);
    }
    }

    exit(1);
}