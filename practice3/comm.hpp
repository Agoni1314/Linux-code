#pragma once
#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h>

#define PATH "."
#define FILENAME "fifo"

class NamedFifo
{
     public:
    NamedFifo(const std::string &path,const std::string &name)
    :_path(path)
    ,_name(name)
    {
        _fifoname=_path+"/"+_name;
        umask(0);
        //新建管道
        int n=mkfifo(_fifoname.c_str(),0666);
        if(n<0)
        {
            std::cerr<<"mkfifo error"<<std::endl;
            return;
        }
        else
        {
            std::cout<<"mkfifo success"<<std::endl;
        }
        
    }
    ~NamedFifo()
    {
        //int n=unlink(FIFO_FILE);
        int n =unlink(_fifoname.c_str());
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
    std::string _path;
    std::string _name;
    std::string _fifoname;
};

class FileOper
{
    public:
    FileOper(const std::string &path,const std::string &name)
    :_path(path)
    ,_name(name)
    ,_fd(-1)
    {

    }
    ~FileOper()
    {

    }
    void OpenFileRead()
    {
        _fd=open(_fifoname.c_str(),O_RDONLY);
        if(_fd<0)
        {
            std::cerr<<"open fifo error"<<std::endl;
            return ;
        }
        std::cout<<"open fifo success"<<std::endl;
    }
    void OpenFileWrite()
    {
        _fd=open(_fifoname.c_str(),O_WRONLY);
        if(_fd<0)
        {
            std::cerr<<"open fifo error"<<std::endl;
            return ;
        }
        std::cout<<"open fifo success"<<std::endl;
        }
        void Write()
        {
            std::string message;
            int cnt=1;
            pid_t id=getpid();
            while(true)
            {
                std::cout<<"Please Enter#";
                std::getline(std::cin,message);
                message +=(",message number:"+std::to_string(cnt++)+"["+std::to_string(id)+"]");
                write(_fd,message.c_str(),message.size());
            }
        }
    void Read()
    {
        while(true)
        {
            char buffer[1024];
            int number=read(_fd,buffer,sizeof(buffer)-1);
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
        }
    }
    void Close()
     {
        if(_fd>0)
        close(_fd);
     }
    private:
    std::string _path;
    std::string _name;
    std::string _fifoname;
    int _fd;
};
