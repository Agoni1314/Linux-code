#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
  pid_t id =fork();
  if(id==0)
  {
    //child
    while(1)
    {
      printf("我是子进程，pid: %d,ppid: %d\n",getpid(),getppid());
     sleep(1);
    }
  }
  else 
  {
      //father
      int cnt=5;
      //while(cnt)
      while(1)
      { 
      printf("我是父进程，pid: %d,ppid: %d\n",getpid(),getppid());
      cnt--;
      sleep(1);
      }
  }
  return 0;
}
