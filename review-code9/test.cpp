#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

 void WaitAll(int num)
{
     while(true)
    {
       // int n= waitpid(-1,nullptr,0);//阻塞了
       int n= waitpid(-1,nullptr,WNOHANG); 
        if(n==0)
        {
            break;
        }
        else if(n<0)
        {
            std::cout<<"waitpid error"<<num<<std::endl;
            break;
        }
    }
   /*  while(true)
    {
        int n= waitpid(-1,nullptr,WNOHANG);//非阻塞轮询
        if(n==0)
        {
            break;
        }
        else if(n<0)
        {
            std::cout<<"waitpid error"<<num<<std::endl;
            break;
        }
    } */
     std::cout<<"fater get a signal:"<<num<<std::endl;
}
int main()
{
    //signal(SIGCHLD,WaitAll);
    signal(SIGCHLD,SIG_IGN);
    for(int i=0;i<10;i++)
    {
        pid_t id =fork();
        if(id==0)
        {
            sleep(3);
            std::cout<<"I am child,exit"<<std::endl;
          /*  if (i<=6) exit(3);
           else pause(); */
           exit(3);
        }
    }
    while(true)
    {
        std::cout<<"I am father,exit"<<std::endl;
        sleep(1);
    }
    return 0;
} 



/*  void Say(int num)
{
    std::cout<<"fater get a signal:"<<num<<std::endl;
} 
int main()
{
    //父进程
    pid_t id=fork();
    if(id==0)
    {
        std::cout<<"I am child,exit"<<std::endl;
        sleep(3);
        exit(3);
    }
    waitpid(id,nullptr,0);
    std::cout<<"I am fater, exit"<<std::endl;
    return 0;
} */



/* volatile int flag=0; //保证内存空间的可见性
void handler(int signu)
{
    std::cout<<"更新全局变量，"<<flag<<"->"<<std::endl;
    flag=1;
}
int main()
{
    signal(2,handler);
    while(!flag)
    {
        std::cout<<"process quit normal"<<std::endl;
    }
    return 0;
} */



/* void handler (int signum)
{
    std::cout<<"hello signal:"<<signum<<std::endl;
    while(true)
    {
        sigset_t pending;
        sigpending(&pending);
        for(int i=31;i>=1;i--)
        {
            if(sigismember(&pending,i))
            std::cout<<"1";
            else
            {
                std::cout<<"0";
            }
        }
        std::cout<<std::endl;
        sleep(1);
    }
    exit(0);
}
int main()
{
    struct sigaction act, oact;
    act.sa_handler=handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,3);
    sigaddset(&act.sa_mask,4);
    act.sa_flags=0;
    sigaction(SIGINT,&act,&oact);
    while(true)
    {
        std::cout<<"hello world:"<<getpid()<<std::endl; //对2号信号捕捉时，对234都屏蔽
        sleep(1);
    }
    return 0;
} */