#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct data
{
  char str[100];
  int flag;
};

void main()
{ 
  key_t key=ftok("abc.txt",'a');
  int shmid=shmget(key,1024,0777|IPC_CREAT);
  struct data*d=shmat(shmid,NULL,0);
  d->flag=0;
  printf("\n enter data");
  gets(d->str);
  d->flag=1;
  while(d->flag!=-1)
  {
    printf("\nwaitting");
    sleep(2);
  }
  shmdt(d);
  
}

//***************************************************************************************************

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct data
{
  char str[100];
  int flag;
};

void main()
{ 
  key_t key=ftok("abc.txt",'a');
  int shmid=shmget(key,1024,0777|IPC_CREAT);
  struct data*d=shmat(shmid,NULL,0);
  d->flag=0;
  while(d->flag!=1)
  {
     printf("\nwaitting");
    sleep(2);
  }
  printf("\n data is accepted :");
 printf("%s",d->str);
  d->flag=-1;
  shmdt(d);
  shmctl(shmid,IPC_RMID,NULL);
  }