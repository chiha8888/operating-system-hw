#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "unistd.h"
#include "buffer.h"

void *producer(void *param){
    buffer_item item;
    while(1){
        sleep(rand()%2);
        item=rand()%100+1;
        if(insert_item(item))
            fprintf(stderr,"producer error.\n");
        else
            printf("producer produced %d\n",item);
    }
}

void *consumer(void *param){
    buffer_item item;
    while(1){
        sleep(rand()%2);
        if(remove_item(&item))
            fprintf(stderr,"consumer error.\n");
        else
            printf("consumer consumed %d\n",item);
    }
}

int main(int argc,char *argv[]){
    if(argc!=4){
        fprintf(stderr,"argument wrong!\n");
        return -1;
    }
    if(argv[1]<0||argv[2]<0||argv[3]<0){
        fprintf(stderr,"argument worng!\n");
        return -1;
    }
    int sleep_time=atoi(argv[1]);
    int producer_num=atoi(argv[2]);
    int consumer_num=atoi(argv[3]);

    init();

    pthread_t tidpro[100];
    for(int i=0;i<producer_num;i++)
        pthread_create(&tidpro[i],NULL,producer,NULL);

    pthread_t tidcon[100];
    for(int i=0;i<consumer_num;i++)
        pthread_create(&tidcon[i],NULL,consumer,NULL);

    sleep(sleep_time);
    return 0;
}
