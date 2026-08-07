#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string>
#include"comm.hpp"
int main()
{
    //write
    /* int fd=open(FIFO_FILE,O_WRONLY);
    if(fd<0)
    {
        std::cerr<<"open fifo error"<<std::endl;
        return 1;
    }
     std::cout<<"open fifo success"<<std::endl; */
     //写入操做
   /*  std::string message;
    int cnt=1;
    pid_t id=getpid();
    while(true)
    {
        std::cout<<"Please Enter#";
        std::getline(std::cin,message);
        message +=(",message number:"+std::to_string(cnt++)+"["+std::to_string(id)+"]");
        write(fd,message.c_str(),message.size());
    }



     close(fd); */

     FileOper writefile(PATH,FILENAME);
     writefile.OpenFileWrite();
     writefile.Write();
     writefile.Close();
    return 0;
}