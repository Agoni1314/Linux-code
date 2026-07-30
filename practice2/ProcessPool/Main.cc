#include<iostream>
#include"ProcessPool.hpp"

int main()
{
    ProcessPool pp(gdefaultnum);
    pp.Create();
    //pp.Debug();
       int task_code=0;
    while(true)
    {
        pp.PushTask(task_code++);
        sleep(1);
    }

    sleep(1000);
    return 0;
}