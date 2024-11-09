#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//argc->no. of arguments
//argv->array
//./a.out 1 2 3 6 2

int main(int argc,char* argv[]){
// path->a.out(executable path)->reserve
int len=argc-1;

printf("Child Process ID:%d\n",getpid());
printf("Parent Process ID:%d\n",getppid());

printf("\n Array in reverse order:");
for(int i=len;i>0;i--){
printf("%d\t",atoi(argv[i]));//character to integer
}
printf("\n");

return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
// child run
int main(int argc,char*argv[]){
int count=argc-1;
int status;

for(int i=1;i<count;i++){
for(int j=i+1;j<=count;j++){
if(atoi(argv[i])>atoi(argv[j])){
char* temp=argv[i];
argv[i]=argv[j];
argv[j]=temp;
}
}
}

char* args[count+1];
args[0]="./child";

for(int i=1;i<=count;i++){

args[i]=argv[i];

}
args[count+1]=NULL;//NULL terminated string

pid_t pid=fork();

if(pid==0){//replica
execv(args[0],args);//it runs Child.c
printf("Hell0");
perror("execv failed");
exit(EXIT_FAILURE);
}
else if(pid>0){//original
wait(&status);//parent process
printf("Parent Process Completed.\n");
 printf("Parent process id: %d\n", getpid());
}
else{
perror("fork failed");
return EXIT_FAILURE;
}
return 0;
}