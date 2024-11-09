#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>

sem_t r,w;
int count=0;

void *reader(void *arg)
{
    sem_wait(&r);
    count++;
    
    if(count==1)
    {
        sem_wait(&w);
    }
    sem_post(&r);
    printf("reader is reading :\n");
    sem_wait(&r);
    count--;
    
    if(count==0)
    {
        sem_post(&w);
    }
    sem_post(&r);
    
    
}

void *writer(void *arg)
{
    sem_wait(&w);
     printf("writer is writting :\n");
     sem_post(&w);

}

int main()
{
    
    pthread_t read[3],write[3];
    
    sem_init(&r,0,1);
    sem_init(&w,0,1);
    
    for(int i=0;i<3;i++)
    {
        pthread_create(&read[i],NULL,reader,NULL);
        pthread_create(&write[i],NULL,writer,NULL);
    }
    
     for(int i=0;i<3;i++)
    {
        pthread_join(read[i],NULL);
        pthread_join(write[i],NULL);
    }
    return 0;
}