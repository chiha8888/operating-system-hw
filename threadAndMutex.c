#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define N 10

sem_t sem;

typedef struct Mu{
    pthread_mutex_t lock;
    int q[100];
    int qfront,qend;
    int finish;
}Mu;

Mu mu;

void *ta(void *param){
    while(mu.finish<N){
        pthread_mutex_lock(&(mu.lock));
        printf("ta in\n");
        if((mu.qend-mu.qfront)==0){
            pthread_mutex_unlock(&(mu.lock));
            printf("ta sleep.\n");
            sem_wait(&sem);
        }
        else
            pthread_mutex_unlock(&(mu.lock));
        pthread_mutex_lock(&(mu.lock));
        printf("student %d finish.\n",mu.q[mu.qfront]);
        mu.qfront++;
        mu.finish++;
        printf("ta out\n");
        pthread_mutex_unlock(&(mu.lock));
    }
    return 0;
}
void *student(void *param){
    int no=*((int *)param);
    int flag=1;
    while(flag){
        sleep(rand()%2);
        pthread_mutex_lock(&(mu.lock));
        printf("student %d in\n",no);
        if((mu.qend-mu.qfront)<4){
            if((mu.qend-mu.qfront)==0){
                mu.q[mu.qend++]=no;
                sem_post(&sem);
            }
            else
                mu.q[mu.qend++]=no;
            flag=0;
        }
        printf("student %d out\n",no);
        pthread_mutex_unlock(&(mu.lock));
    }
    pthread_exit(NULL);
    return 0;
}
int main(){
    pthread_t tid[N+1];
	pthread_mutex_init(&(mu.lock),NULL);
	sem_init(&sem,0,0);
    mu.qfront=0;
    mu.qend=0;
    mu.finish=0;

    pthread_create(&tid[0],NULL,ta,NULL);
    for(int i=1;i<=N;i++){
        int *k=malloc(sizeof(int));
        *k=i;
        pthread_create(&tid[i],NULL,student,k);
    }

    for(int i=1;i<=N;i++)
		pthread_join(tid[i],NULL);
	pthread_join(tid[0],NULL);

	pthread_mutex_destroy(&(mu.lock));
	return 0;
}
