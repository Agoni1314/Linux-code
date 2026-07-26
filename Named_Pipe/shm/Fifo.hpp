#ifndef FIFO_HPP
#define FIFO_HPP


#include <iostream>
#include <cstdio>
#include <string>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "."
//#define FIFO_FILE "fifo"
#define FILENAME "fifo"

class NamedFifo
{
public:
     NamedFifo(const std::string &path,const std::string &name)
     :_path(path)
     ,_name(name)
     ,_fd(-1)
     {
         _fifoname=_path+"/"+_name;
            umask(0);
        //创建管道
        int n=mkfifo(_fifoname.c_str(), 0666);
        if(n !=0)
        {
            std::cerr<<"mkdir fifo error"<<std::endl;
        }
        else
        {
            std::cerr<<"mkdir fifo success"<<std::endl;
        }
     }
     ~ NamedFifo()
     {
        int n=unlink(_fifoname.c_str());
        if(n==0)
        {
            std::cout<<"remove fifo success"<<std::endl;
        }
        else
        {
            std::cout<<"remove fifo failed"<<std::endl;
        }
     }

private:
    std::string _name;
    std::string _path;
    std::string _fifoname;
    int _fd;
};

class FileOpen
{
    public:
    FileOpen(const std::string &path,const std::string &name)
     :_path(path)
     ,_name(name)
     ,_fd(-1)
    {
        _fifoname=_path+"/"+_name;
    }
    void OpenForRead()
    {
         _fd=open(_fifoname.c_str(),O_RDONLY);
        if(_fd<0)
        {
            std::cerr<<"open fifo error"<<std::endl;
            return ;
        }
        std::cout<<"open fifo success"<<std::endl;
    }
    void OpenForWrite()
    {
         _fd=open(_fifoname.c_str(),O_WRONLY);
        if(_fd<0)
        {
            std::cerr<<"open fifo error"<<std::endl;
            return ;
        }
        std::cout<<"open fifo success"<<std::endl;
    }
    void Wakeup()
    {
        /*  std::string message;
        int cnt = 1;
        pid_t id = getpid();
        while(true)
        {
            std::cout << "Please Enter…… ";
            std::getline(std::cin, message);
            message += (", message number: " + std::to_string(cnt++) + ", [" + std::to_string(id) + "]");
            write(_fd, message.c_str(), message.size());
        } */

        char c='c';
        int n =write(_fd,&c,1);
        printf("尝试唤醒:%d\n",n);
    }
    bool Wait()
    {
        char c;
         int number=read(_fd,&c,1);
         if(number>0)
         {
            printf("醒来：%d\n",number);
            return true;
         } 
         
        
    }
    void Close()
    {
        if(_fd>0)
        close(_fd);
    }
    ~FileOpen()
    {
        
    }

    private:
    std::string _name;
    std::string _path;
    std::string _fifoname;
    int  _fd;
};

#endif