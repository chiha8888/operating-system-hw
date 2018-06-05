#include "sss"
#include "semaphore.h"

sem_t empty;
sem_t full;
sem_t mutex;
int in,out;

int insert_item(buffer_item item){

    if(sem_trywait(&empty)==-1)
        return -1;
    if(sem_trywait(&mutex)==-1)
        return -1;
    buffer[in]=item;
    in=(in+1)%BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);
    return 0;
}

int remove_item(buffer_item *item){
    if(sem_trywait(&full)==-1)
        return -1;
    if(sem_trywait(&mutex)==-1)
        return -1;
    *item=buffer[out];
    out=(out+1)%BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&empty);
    return 0;
}

void init(){
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    in=0;
    out=0;
}
