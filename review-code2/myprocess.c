#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int count = 5;
        while(count)
        {
            printf("我是子进程，我正在运行：%d\n", count);
            sleep(1);
            count--;
        }
    }
    else
    {
        while(1)
        {
            printf("我是父进程，我正在运行...\n");
            sleep(1);
        }
    }

//  int a=1;;
//scanf("%d\n",&a);
 // while(1)
 // {
 //   printf("linux\n");
 // }
  return 0;
}
