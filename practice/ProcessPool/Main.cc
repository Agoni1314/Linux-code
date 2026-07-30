#include<iostream>
#include"ProcessPool.hpp"

int main()
{
    ProcessPool pp(gdefaultnum);
    pp.Create();
    //pp.Debug();
    while(true)
    {
        int task_code=1;
        pp.PushTask()
    }

    sleep(1000);
    return 0;
}