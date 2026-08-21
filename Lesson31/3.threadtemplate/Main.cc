#include"Thread.hpp"
#include<unistd.h>

void Count(int cnt)
{
    while(cnt--)
    {
        std::cout<<"新线程"<<std::endl;
        sleep(1);
    }
}
int main()
{
    int cnt=10;
    Thread<int> t(Count,cnt);
    t.Start();
    t.Join();








   /*  Thread t([]()
{
     while(true)
        {
            std::cout<<"新线程"<<std::endl;
            sleep(1);
        }
})
    t.Detach();
    t.Start();
    sleep(5);
    t.Stop(5);
    sleep(5);
    t.Join();
 */
    return 0;
}