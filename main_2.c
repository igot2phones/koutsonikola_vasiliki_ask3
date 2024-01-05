#include <stdio.h>
#include <stdlib.h> //gia to atoi
#include <unistd.h>
#include <pthread.h>
//#define clients 4 deprecated gia to 2o erwthma

int Mail_Queue = 0;

void *addmailqueue();

int main(int argc, char *argv[]){
    printf("Mail Queue initialy: %d\n",Mail_Queue);
    int clients = atoi(argv[2]); //pernaw to posa clients exei dwsei o xrhsths apo thn grammh entolwn (run argument)
    pthread_t first_thread[clients];
    int err_handler;
    int posa_akoma = atoi(argv[1]); //pernaw to poso pou exei dwsei o xrhsths apo thn grammh entolwn (run argument)
    for (int i = 0; i < clients; i++){
    err_handler = pthread_create(&first_thread[i], NULL, addmailqueue, (void *)&posa_akoma); //dhmiourgia thread
        if (err_handler){ //an to err_handler einai diaforetiko tou 0 tote exoume error
            printf("Error: %d\n", err_handler);
            exit(-1);
        }
    }
    for (int i = 0; i < clients; i++){
        pthread_join(first_thread[i], NULL); //perimenei na teleiwsei to thread
    }
    printf("Mail Queue Now: %d\n",Mail_Queue);
    return 0;
}

void *addmailqueue(void *arg){
    int posa_akoma = *((int *)arg); //metatroph tou void se int
    for (int i = 0; i < posa_akoma; i++)
    {
        Mail_Queue++;
    }
    
}