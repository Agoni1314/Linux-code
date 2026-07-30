#include"ProcessPool.hpp"
int main()
{
   ProcessPool pp;
   pp.Create();
   //pp.Debug();
   //int task_code=0;
   int cnt=10;
   // while(true)
   while(cnt--)
    {
    
        pp.Run();
        sleep(1);
    }
    pp.Stop();
    return 0;
}