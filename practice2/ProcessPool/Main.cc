#include<iostream>
#include"ProcessPool.hpp"
#include"Task.hpp"

int main()
{
    ProcessPool pp(gdefaultnum);
    pp.Create();
    //pp.Debug();
    // int task_code=0;
    int cnt=10;
    while(cnt--)
    {
       // pp.Run(task_code++);
       pp.Run();
        sleep(1);
    }
    pp.Stop();
    sleep(1000);
    return 0;
}