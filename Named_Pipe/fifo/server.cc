
#include"comm.hpp"

int main()
{
   /*  umask(0);
    //创建管道
    int n=mkfifo(FIFO_FILE,O_CREAT | 0666);
    if(n !=0)
    {
        std::cerr<<"mkdir fifo error"<<std::endl;
        return 1;
    } */
    
   /*  //打开,write方没有执行open的时候，read方就要在open内部进行阻塞，直到有人把管道文件打开后open才会返回
    int fd=open(FIFO_FILE,O_RDONLY);
    if(fd<0)
    {
        std::cerr<<"open fifo error"<<std::endl;
        return 2;
    }
    else
    {
          std::cerr<<"open fifo success"<<std::endl;
    }

    //read
    while(true)
    {
        char buffer[1024];
        int number=read(fd,buffer,sizeof(buffer)-1);
        if(number>0)
        {
            buffer[number]=0;
            std::cout<<"Clinet Say……"<<buffer<<std::endl;
        }
        else if(number==0)
        {
            std::cout<<"Client quit"<<std::endl;
            break;
        }
        else
        {
            std::cout<<"read"<<std::endl;
            break;
        }
    }

    //删除管道
    /* n=unlink(FIFO_FILE);
    if(n==0)
    {
        std::cout<<"remove fifo success"<<std::endl;
    }
    else
    {
        std::cout<<"remove fifo failed"<<std::endl;
    } */ 



    //创建管道文件
    NamedFifo fifo(PATH,FILENAME);
    //文件操做
    FileOpen readerfile(PATH,FILENAME);
    readerfile.OpenForRead();
    readerfile.Read();
    readerfile.Close();
    return 0;
}