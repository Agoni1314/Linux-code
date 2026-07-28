#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<functional>
#include<sys/types.h>
#include <sys/wait.h>


int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        sleep(2);
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        int a = 10;
        a /= 0;
        printf("hello bit\n");

        exit(1);
    }
    int status = 0;
    waitpid(id, &status, 0);
    printf("signal: %d, exit code: %d, core dump: %d\n",
           (status & 0x7F), (status >> 8) & 0xFF, (status >> 7) & 0x1);
}

// int main()
// {
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
//     int a = 10;
//     a /= 0;
//     // raise(2);
//     printf("hello bit\n");
//     printf("hello bit\n");
//     printf("hello bit\n");
// }

// void PrintPending(sigset_t &pending)
// {
//     printf("我是一个进程(%d), pending: ", getpid());
//     for (int signo = 31; signo >= 1; signo--)
//     {
//         if (sigismember(&pending, signo))
//         {
//             std::cout << "1";
//         }
//         else
//         {
//             std::cout << "0";
//         }
//     }
//     std::cout << std::endl;
// }

// void handler(int sig)
// {
//     std::cout << "#######################" << std::endl;
//     std::cout << "递达" << sig << "信号!" << std::endl;
//     sigset_t pending;
//     int m = sigpending(&pending);
//     PrintPending(pending); // 0000 0010(处理完，2号才回被设置为0)，0000 0000(执行handler方法之前，2对应的pending已经被清理了)
//     std::cout << "#######################" << std::endl;
// }

// int main()
// {
//     signal(SIGINT, handler);
//     // 1. 屏蔽2号信号
//     sigset_t block, oblock;
//     sigemptyset(&block);
//     sigemptyset(&oblock);

//     sigaddset(&block, SIGINT); // 已经对2号信号进行屏蔽了吗？没有！
//     // for(int i = 1; i<32; i++)
//     //     sigaddset(&block, i);

//     int n = sigprocmask(SIG_SETMASK, &block, &oblock);
//     (void)n;

//     // 4. 重复获取打印过程
//     int cnt = 0;
//     while (true)
//     {
//         // 2. 获取pending信号集合
//         sigset_t pending;
//         int m = sigpending(&pending);

//         // 3. 打印
//         PrintPending(pending);
//         if (cnt == 10)
//         {
//             // 5. 恢复对2号信号的block情况
//             std::cout << "解除对2号的屏蔽" << std::endl;
//             sigprocmask(SIG_SETMASK, &oblock, nullptr);
//         }

//         sleep(1);
//         cnt++;
//     }

//     return 0;
// }

// void handler(int sig)
// {
//     std::cout << "hello sig: " << sig << std::endl;
//     signal(2, SIG_DFL); // 2 默认动作是终止
//     std::cout << "恢复处理动作" << std::endl;
// }

// int main()
// {
//     signal(2, handler); // 自定义捕捉
//     signal(2, SIG_IGN); //忽略信号

//     sigset_t set;

//     while(true)
//     {
//         sleep(1);
//         std::cout << "." << std::endl;
//     }
//     return 0;
// }


/* struct task_struct
{
    pid_t id;
    int count; // 时间片
};

std::vector<task_struct> task_list;


void Sche()
{
    std::cout<<"我是继进程调度"<<std::endl;
}
void MemManger()
{
    std::cout << "我是周期性的内存管理，正在检查有没有内存问题" << std::endl;
}
void Fflush()
{
    std::cout << "我是刷新程序，我在定期刷新内存数据，到磁盘" << std::endl;
}

using func_t=std::function<void()>;
std::vector<func_t>funcs;
void handlerSig(int sig)
{
   for(auto f: funcs)
   f();
    int n=alarm(1);
    
}
 
int main()
{
    funcs.push_back(Sche);
    funcs.push_back(MemManger);
    funcs.push_back(Fflush);
    signal(SIGALRM, handlerSig);
    alarm(1); 
    while(true)//os做法
    {
        pause();
    }
  
    return 0;
}   */

/* void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig <<"pid:"<<getpid()<<std::endl;
    int n=alarm(1);
    std::cout <<"n:"<<n<<std::endl;
}
 
int main()
{
    signal(SIGALRM, handlerSig);
    alarm(1); 
    while(true)
    {
        pause();
    }
  
    return 0;
}   */

/* void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig <<"pid:"<<getpid()<<std::endl;
    alarm(1);
}
 
int main()
{
    signal(SIGALRM, handlerSig);
    alarm(1); 

  
    while (true)
    {
       std::cout<<"."<<"pid:"<<getpid()<<std::endl;
       sleep(1);

    }
           return 0;
}   */


/* void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig << std::endl;
}
 
int main()
{
    signal(SIGALRM, handlerSig);
    alarm(1); 

  
    while (true)
    {
       std::cout<<"."<<std::endl;
       sleep(1);
       return 0;
    }
}   */


 /* int cnt = 0;
void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig <<"cnt:"<<cnt<< std::endl;
    exit(13);
}
 
int main()
{
    signal(SIGALRM, handlerSig);
    alarm(1); // 设定1S闹钟，1s以后，当前进程会受到一个信号

  
    while (true)
    {
       cnt++;
    }
}   */


/* void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig << std::endl;
    exit(13);
}

int main()
{
    for (int i = 1; i < 32; i++)
        signal(i, handlerSig);

    alarm(1); // 设定1S闹钟，1s以后，当前进程会受到一个信号

    int cnt = 0;
    while (true)
    {
        std::cout << "count: " << cnt++ << std::endl;//效率不高
    }
}   */





/* void handlerSig(int sig)
{
    std::cout<<"获得一个信号"<<sig<<std::endl;
    exit(13);
}
int main()
{
    for(int i = 1; i < 32; i++)
   signal(SIGINT,handlerSig);

// for(int i = 1; i < 32; i++)
    // {
    //     sleep(1);
    //     if(i == 9 || i == 19)
    //         continue;
    //     // raise(i);

    // }

    int cnt = 0;
    while(true)
    {
        std::cout << "hello world " << cnt++ << std::endl;
        sleep(1);
        int a = 10;
        // a /= 0; // 除0错误
        int *p = nullptr;
        *p = 100; // 野指针
        // abort();
        sleep(1);
    }
}
 */