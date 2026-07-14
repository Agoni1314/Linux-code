#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
  pid_t id=fork();
  if(id==0)
  {
    //child
    int count=5;
    while(count)
    {
      printf("我是子进程，我正在运行: %d\n",count);
      sleep(1);
      count--;
    }
  }
  else
  {
    while(1)
    {
        
      printf("我是父进程，我正在运行\n");
      sleep(1);
    }
  }
//  printf("我的进程，pid: %d\n",getpid);
//  int a=0;
//  scanf("%d",&a);
  return 0;
}

