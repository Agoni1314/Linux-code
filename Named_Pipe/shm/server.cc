#include<unistd.h>
#include"Shm.hpp"
#include"Fifo.hpp"


int main()
{
    /* Shm shm;
    shm.Create();
    sleep(5);ll
    shm.Attach();
    shm.VirtualAddr();
    sleep(5);
    shm.Destroy(); */
     
    Shm shm(pathname,projid,CREATER);
    sleep(5);
    shm.Attr();

       /*  NamedFifo fifo("/", FILENAME);

        // 文件操作了
        FileOper readerfile(PATH, FILENAME);
        readerfile.OpenForRead();
        



    Shm shm(pathname,projid,CREATER);
   char mem=(char*) shm.VirtualAddr();
   while(true)
   {
       if( readerfile.Wait())
        {
             printf("%s\n",mem);
             //sleep(1);
        }
       
   }
    shm.Size();

    readerfile.Close(); */
    return 0;
}