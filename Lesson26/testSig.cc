#include<iostream>
#include<unistd.h>
#include<signal.h>

void handlerSig(int sig)
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
