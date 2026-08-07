#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h>
#include"comm.hpp"
int main()
{
   /*  umask(0);
    //新建管道
    int n=mkfifo(FIFO_FILE,0666);
    if(n<0)
    {
        std::cerr<<"mkfifo error"<<std::endl;
        return 1;
    }
     std::cout<<"mkfifo success"<<std::endl; */

     
     //read
     //write没有执行open的时候，就要在open内部进行阻塞，知道有人把管道文件打开后open才会返回
     /* int fd=open(FIFO_FILE,O_RDONLY);
     if(n<0)
     {
        std::cerr<<"open fifo error"<<std::endl;
        return 2;
     }
     std::cout<<"open fifo success"<<std::endl; */
     //正常的读
     /* while(true)
     {
        char buffer[1024];
        int number=read(fd,buffer,sizeof(buffer)-1);
        if(number>0)
        {
            buffer[number]=0;
            std::cout<<"Client Say#"<<buffer<<std::endl;
        }
        else if(number==0)
        {
            std::cout<<"Client quit"<<number<<std::endl;
        }
        else
        {
             std::cout<<"read error"<<std::endl;
        }
     } */
     //删除管道
    /*  n=unlink(FIFO_FILE);
     if(n==0)
     {
         std::cout<<"remove fifo success"<<std::endl;
     }
     else
     {
         std::cout<<"remove fifo failed"<<std::endl;
     } */

     NamedFifo fifo(PATH,FILENAME);
     FileOper readerfile(PATH,FILENAME);
     readerfile.OpenFileRead();
     readerfile.Read();
     readerfile.Close();
    return 0;
}