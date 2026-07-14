#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("我的程序要运行了!\n");

    if(fork() == 0)
    {
      printf("I  am child,my pid is:%d\n",getpid());
        sleep(1);
        //child
        //execl("/usr/bin/ls", "/usr/bin/ls", "-ln", "-a", NULL);
        execl("./other", "other", NULL);
        exit(1);
    }

    waitpid(-1, NULL, 0);
    printf("我的程序运行完毕了\n");
    //return 0;
}
