#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>
#include <cstdio>

int  flag=100;
void showtid(pthread_t &tid)
{
    printf("tid:%lx\n",tid);
}
std::string FormatId(const pthread_t &tid)
{
    char id[64];
    snprintf(id, sizeof(id), "0x%lx", tid);
    return id;
}
// code done, result ok
// code done, result not ok
// code no finish
void *routine(void *args)
{
    std::string name=static_cast<const char*>(args);
    int cnt=5;
    while(true)
    {
        std::cout<<"新进程，我的名字是:"<<name<<std::endl;
        sleep(1);
        cnt--;
    }
    return nullptr;
}
int main()
{
    pthread_t tid;
    int n=pthread_create(&tid,nullptr,routine,(void*)"thread-1");
    (void)n;
    showtid(tid);
    int cnt=5;
    while(true)
    {
        std::cout << "我是main线程: 我的名字是: main thread" << " 我的Id是: " 
            << FormatId(pthread_self()) << ", flag: " << flag << std::endl;
        sleep(1);
        cnt--;
    }
     void *ret = nullptr; // ret也是一个变量！！也有空间哦！

    // 等待的目标线程，如果异常了，整个进程都退出了，包括main线程，所以，join异常，没有意义，看也看不到！
    // jion都是基于：线程健康跑完的情况，不需要处理异常信号，异常信号，是进程要处理的话题！！！
    pthread_join(tid, &ret); // 为什么在join的时候，没有见到异常相关的字段呢？？

    std::cout << "ret is : " << (long long int)ret << std::endl;

    pthread_join(tid,nullptr);
    return 0;
}

















/* #include<unistd.h>

void *threadrun(void *args)
{
    std::string name=(const char*)args;
    while(true)
    {
        std::cout<<"我是新线程:name"<<"pid:"<<getpid()<<std::endl;
        sleep(1);
    }
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,nullptr,threadrun,(void*)"thread-1");
    while(true)
    {
        std::cout<<"我是主线程……"<<"pid:"<<getpid()<<std::endl;
        sleep(1);
    }
    return 0;
} */