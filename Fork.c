#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

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

void sigchld_handler(int sig);
int signalON;

int main()
{
    int msqid;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    signalON = 0;
    signal(SIGINT, sigchld_handler);

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


        printf("Hpid: %d\n", getpid());
        while(1){
            if (signalON){
                for(int i =0;i<1000;i++)
        {
            aleatorio = rand() % 100 + 1;
            printf("Hijo: %d\n", aleatorio);
            if(aleatorio <= 10)
            {
                int msgflg = IPC_CREAT | 0660;
                key = 1234;
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
            else{
                pause();
            }
        }
        exit(0);
    }
    else  // Padre
    {
        int aleatorio;

        printf("Child pid: %d\n", getpid());
        while(1){
            if (signalON){
                for(int i =0;i<1000;i++)
        {                    
            aleatorio = rand() % 100 +1;
            printf("Padre: %d\n", aleatorio);

            if(aleatorio <= 10)
            {
                int msgflg = IPC_CREAT | 0660;
                key = 1234;
                    if((msqid = msgget(key, msgflg)) < 0)
                        die("msgget");
                    sbuf.mtype = aleatorio;
                    sprintf(sbuf.mtext, "Padre: %d", aleatorio);
                    buflen = strlen(sbuf.mtext)+1;

                    if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                    {
                        printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                        die("msgsnd");
                    }
            }else{
                int msgflg = IPC_CREAT | 0606;
                key = 4321;
                if((msqid = msgget(key, msgflg)) < 0)
                    die("msgget");
                sbuf.mtype = aleatorio;
                sprintf(sbuf.mtext, "Padre: %d", aleatorio);
                buflen = strlen(sbuf.mtext)+1;
                if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
                {
                    printf("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
                    die("msgsnd");
                }
            }

        }
            }
            else{
                pause();
            }
        }
    }
    return(0);
}

void sigchld_handler(int sig){
    signalON = 1;
}