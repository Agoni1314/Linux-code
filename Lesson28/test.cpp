#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

// void WaitAll(int num)
// {
//     while (true)
//     {
//         pid_t n = waitpid(-1, nullptr, WNOHANG); // 阻塞了！
//         if (n == 0)
//         {
//             break;
//         }
//         else if (n < 0)
//         {
//             std::cout << "waitpid error " << std::endl;
//             break;
//         }
//     }
//     // while (true)
//     // {
//     //     pid_t n = waitpid(-1, nullptr, WNOHANG); // waitpid默认是阻塞的！
//     //     if (n == 0)
//     //     {
//     //         break;
//     //     }
//     //     else if (n < 0)
//     //     {
//     //         std::cout << "waitpid error " << std::endl;
//     //         break;
//     //     }
//     // }

//     std::cout << "father get a signal: " << num << std::endl;
// }

int main()
{
    // 父进程
    signal(SIGCHLD, SIG_IGN); // 父进程
    for (int i = 0; i < 10; i++)
    {
        pid_t id = fork(); // 如果我们有10个子进程呢？？6退出了，4个没退
        if (id == 0)
        {
            sleep(3);
            std::cout << "I am child, exit" << std::endl;
            exit(3);
            // if(i <= 6) exit(3);
            // else pause();
        }
    }

    while (true)
    {
        std::cout << "I am fater, exit" << std::endl;
        sleep(1);
    }

    return 0;
}

// volatile int flag = 0;

// void handler(int signu)
// {
//     std::cout << "更改全局变量, " << flag << "-> 1" << std::endl;
//     flag = 1;
// }

// int main()
// {
//     signal(2, handler);

//     while(!flag);
//     std::cout << "process quit normal!" << std::endl;
//     return 0;
// }

// void handler(int signum)
// {
//     std::cout << "hello signal: " << signum << std::endl;
//     while(true)
//     {
//         //不断获取pending表！
//         sigset_t pending;
//         sigpending(&pending);
//         for(int i = 31; i >= 1; i--)
//         {
//             if(sigismember(&pending, i))
//                 std::cout << "1";
//             else
//                 std::cout << "0";
//         }
//         std::cout << std::endl;
//         sleep(1);
//     }
//     exit(0);
// }

// int main()
// {
//     struct sigaction act, oact;
//     act.sa_handler = handler;
//     sigemptyset(&act.sa_mask);
//     sigaddset(&act.sa_mask, 3);
//     sigaddset(&act.sa_mask, 4);
//     act.sa_flags = 0;

//     sigaction(SIGINT, &act, &oact); // 对2号信号进行了捕捉, 2,3,4都屏蔽

//     while(true)
//     {
//         std::cout << "hello world: " << getpid() << std::endl;
//         sleep(1);
//     }
//     return 0;
// }