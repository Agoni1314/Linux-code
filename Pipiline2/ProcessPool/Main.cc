#include"ProcessPool.hpp"
int main()
{
   ProcessPool pp;
   pp.Create();
   //pp.Debug();
   int task_code=0;
    while(true)
    {
        //选一个信道
        pp.PushTask(task_code++);
        sleep(1);
    }
   sleep(1000);
    return 0;
}