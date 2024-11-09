#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t e,f,s;
int data[5],in=0,out=0;

void *producer(void *arg)
{
    sem_wait(&e);
    sem_wait(&s);
    data[in]=rand()%100;
    printf("Producer Generated %d \n",data[in]);
    in=(in+1)%5;
    
    sem_post(&f);
    sem_post(&s);
}

void *consumer(void *arg)
{
    int val;
    do{
        sem_wait(&f);
        sem_wait(&s);
        val=data[out];
        printf("Consumer consumed %d \n ",val);
        out=(out+1)%5;
        
        sem_post(&s);
        sem_post(&e);
        sem_getvalue(&e,&val);
        
        
    }while(val!=5);
}

void main()
{
    pthread_t c,p[8];
    
    sem_init(&e,0,5);
    sem_init(&f,0,0);
    sem_init(&s,0,1);
    
    pthread_create(&c,NULL,consumer,NULL);
    
    for(int i=0;i<8;i++)
    {
        pthread_create(&p[i],NULL,producer,NULL);
    }
    sleep(2);
}
