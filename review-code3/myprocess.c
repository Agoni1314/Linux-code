#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
  pid_t id=fork();
  if(id==0)
  {while(1)
    {            
    printf("我是子进程，子进程pid: %d,父进程ppid：%d\n",getpid(),getppid());
    sleep(1);
    }
  }
  else 
  {
    int cnt = 5;
while (cnt)
{
    printf("我是父进程， pid: %d, ppid: %d\n", getpid(), getppid());
    cnt--;
    sleep(1);
}
  }
  return 0;
}

