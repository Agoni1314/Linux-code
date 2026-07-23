/* #include"ProcessPool.hpp"
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
} */



#include "ProcessPool.hpp"

int main()
{
    // 这个代码，有一个藏得比较深的bug --- TODO
    // 创建进程池对象
    ProcessPool pp(gdefaultnum);

    // 启动进程池
    pp.Start();

    // 自动派发任务
    int cnt = 10;
    while(cnt--)
    {
        pp.Run();
        sleep(1);
    }

    // 回收，结束进程池
    pp.Stop();
    return 0;
}