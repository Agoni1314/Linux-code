#include<iostream>
#include<string>
#include<pthread.h>

int count=1;
std::string Addr(int &c)
{
    char addr{64};
    snprintf(addr,sizeof(addr),"%p",&c);
    return addr;
}
void *routine1(void *args)
{
    (void)args;
    while(true)
    {
        std::cout<<"thread - 1,count="<<count<<"我来修改,"<<"&count:"<<Addr(count)<<std::endl;
        count++;
        sleep(1);
    }
}
void *routine2(void *args)
{
    (void)args;
    while(true)
    {
        std::cout<<"thread - 2,count"<<count<<"&count:"<<Addr(count)<<std::endl;
        sleep(1);
    }
}
int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,nullptr,routine1,nullptr);
    pthread_create(&tid2,nullptr,routine2,nullptr);
    pthread_join(tid1,nullptr);
    thread_join(tid2,nullptr);
    return 0;
}