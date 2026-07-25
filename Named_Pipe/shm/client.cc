#include"Shm.hpp"
#include"Fifo.hpp"
int main()
{
    //client就只是获取到共享内存并映射到自己的空间
   /*  Shm shm;
    shm.Get();
    sleep(5);
    shm.Get(); 
    sleep(1);
    return 0; */

    
    FileOpen writerfile(PATH,FILENAME);
     writerfile.OpenForWrite();
    



     Shm shm(pathname,projid,USER);
    char *mem=(char*)shm.VirtualAddr();
    int index=0;
    for(char c='A';c<='Z';c++,index+=2)
    {
        mem[index]=c;
        sleep(1);
        mem[index+1]=c;
        sleep(1);
        mem[index+2]=0;

         writerfile.Wakeup();
    }
    shm.Size();

         writerfile.Close();
}