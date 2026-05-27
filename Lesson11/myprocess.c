#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int gavl=100;
int main()
{
//  while(1)
//  {
//    sleep(1);
//    printf("linux 进程,我的pid%d,我的父进程id%d\n",getpid(), getppid());
// }


//  printf("父进程开始运行，pid: %d\n",getpid());
//  fork();
//  printf("进程开始运行，pid: %d\n",getpid());


  printf("父进程开始运行，pid: %d\n",getpid());
 pid_t id= fork();
 if(id<0)
 {
   perror("fork");
   return 1;
 }
 else if(id ==0)
 {

    printf("子进程,我的pid:%d,我的父进程id:%d,gavl: %d\n",getpid(), getppid(),gavl);
        sleep(5);
   while(1)
   {
     sleep(1);
        printf("子进程修改变量：%d->%d,gavl,gavl+10");
        gavl+=10;
    printf("子进程,我的pid:%d,我的父进程id:%d\n",getpid(), getppid());
   }
 }
 else
 {
   while(1)
   {
      
    sleep(1);
    printf("父进程,我的pid:%d,我的父进程id:%d,gavl: %d\n",getpid(), getppid(), gavl);
   }
    
 }
  printf("进程开始运行，pid: %d\n",getpid());
}

