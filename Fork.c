#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msgbuf
{
    long mtype;
    char mtext[128];
};

void die(char* s)
{
    perror(s);
    exit(1);
}

int main()
{
    int msqid;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    printf("Generador de mensajes aleatorios: \n");
    int id = fork();

    if(id == -1)
    {
        perror("fork");
        exit(1);
    }
 
    if(id == 0) // Hijo
    {
        int aleatorio;

        for(int i =0;i<1000;i++)
        {
            aleatorio = rand() % 101;
            printf("Hijo: %d\n", aleatorio);
            if(aleatorio <= 10)
            {
                int msgflg = IPC_CREAT | 0660;
                key = 1234;
                if(aleatorio%2 ==0){
                    if((msqid = msgget(key, msgflg)) < 0)
                        die("msgget");
                    sbuf.mtype = aleatorio;
                    sprintf(sbuf.mtext, "Hijo: %d", aleatorio);
                    buflen = strlen(sbuf.mtext)+1;

                    if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                    {
                        printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                        die("msgsnd");
                    }
                }else{

                }
            }else{
                int msgflg = IPC_CREAT | 0606;
                key = 4321;
                if((msqid = msgget(key, msgflg)) < 0)
                    die("msgget");
                sbuf.mtype = aleatorio;
                sprintf(sbuf.mtext, "Hijo: %d", aleatorio);
                buflen = strlen(sbuf.mtext)+1;
                if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                {
                    printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                    die("msgsnd");
                }
            }

        }
        exit(0);
    }
    else  // Padre
    {
        int aleatorio;

        for(int i =0;i<1000;i++)
        {                    
            aleatorio = rand() % 101;
            printf("Padre: %d\n", aleatorio);

            if(aleatorio <= 10)
            {
                int msgflg = IPC_CREAT | 0660;
                key = 1234;
                if(aleatorio%2 ==0){
                    if((msqid = msgget(key, msgflg)) < 0)
                        die("msgget");
                    sbuf.mtype = aleatorio;
                    sprintf(sbuf.mtext, "Hijo: %d", aleatorio);
                    buflen = strlen(sbuf.mtext)+1;

                    if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                    {
                        printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                        die("msgsnd");
                    }
                }else{

                }
            }else{
                int msgflg = IPC_CREAT | 0606;
                key = 4321;
                if((msqid = msgget(key, msgflg)) < 0)
                    die("msgget");
                sbuf.mtype = aleatorio;
                sprintf(sbuf.mtext, "Hijo: %d", aleatorio);
                buflen = strlen(sbuf.mtext)+1;
                if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                {
                    printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                    die("msgsnd");
                }
            }

        }
    }
    return(0);
}