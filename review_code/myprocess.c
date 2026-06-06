#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int gval=100;
int main()
{
  printf("父进程开始运行 getppid:%d\n",getppid());
 pid_t id= fork();
 if(id<0)
 {
   printf("fork");
 }
 else if(id == 0)
{
    printf("我是一个子进程 ！, 我的pid: %d, 我的父进程id: %d,gval:%d\n", getpid(), getppid(),gval);
    sleep(5);
    // child
    while(1)
    {
        sleep(1);
        printf("子进程修改变量 : %d->%d", gval, gval+10);
        gval+=10; // 修改
        printf("我是一个子进程 ！, 我的pid: %d, 我的父进程id: %d\n", getpid(), getppid());
    }
}
 else 
 {
   while(1)
   {
     sleep(1);   
     printf("这是父进程，子进程getpid:%d,父进程id:%d,gval:%d\n",getpid(),getppid(),gval);
    }
 }
  return 0;
}



//int main()
//{
// // chdir("/home/common");
//  while(1)
//  {
//    sleep(1);
//    printf("我是一个进程，我的pid: %d,我的父进程pid: %d\n",getpid(),getppid());
//  }
//  return 0;
//}
