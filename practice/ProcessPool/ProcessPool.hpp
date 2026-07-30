#ifndef __PROCESS_POOL_HPP__
#define __PROCESS_POOL_HPP__

#include<iostream>
#include<vector>
#include<cstdio>
#include<unistd.h>
class Channel
{
    public:
        Channel(int fd,pid_t id)
        :_wfd(fd)
        ,_subid(id)
        {
             _name = "channel-" + std::to_string(_wfd) + "-" + std::to_string(_subid);
        }
        ~Channel(){}
        int Fd()
        {
            return _wfd;
        }
        pid_t Subid()
        {
            return _subid;
        }
        std::string Name()
        {
            return _name;
        }
    private:
        int _wfd;
        pid_t _subid;
        std::string _name;
};

class ChannelManage
{
    public:
    ChannelManage(){}
    ~ChannelManage(){}
      void Insert(int wfd,pid_t subid)
    {
        /* Channel c(wfd,subid);
        _channels.push_back(std::move(c)); */
        _channels.emplace_back(wfd,subid);
    }
    void PrintChannel()
    {
        for(auto &channel:_channels)
        {
            std::cout<<channel.Name()<<std::endl;
        }
    }
    private:
    std::vector<Channel> _channels;
};

const int gdefaultnum=5;
class ProcessPool
{
    public:
    ProcessPool(int num):_porcess_num(num)
    {}
    ~ProcessPool(){}
    bool Create()
    {
         for(int i=0;i<_porcess_num;i++)//只有父进程才会执行for循环
        {
           //1.创建管道
            int pipefd[2]={};
            int n=pipe(pipefd);
            if(n<0)
            return false;

        //2.创建子进程
        pid_t subid=fork();
        if(subid<0) return false;
        else if(subid==0)
        {
            //child
            //关闭不需要的文件描述符
            close(pipefd[1]);
            work(pipefd[0]);
            close(pipefd[0]);
            exit(0);
        }
        else
        {
            //father
            //关闭不需要的文件描述符
             close(pipefd[0]);
             _cm.Insert(pipefd[1],subid);
        }
        } 
         return true;
    }
    void work(int rfd)
    {
        while(true)
        {
           /*  std::cout<<"我是子进程，我的rfd是："<<rfd<<std::endl;
            sleep(1); */
            int code=0;
            ssize_t n=read(rfd,&code,sizeof(code));
            if(n>0)
            {
                if(n !=sizeof(code))
                {
                    continue;
                }
                std::cout<<"子进程收到一个任务码"<<code<<std::endl;
            }
            else if(n==0)
            {
                    std::cout<<"子进程退出"<<std::endl;
                    break;
            }
            else
            {
                    std::cout<<"读取错误"<<std::endl;
                    break;
            }
        }
    }
  
    void Debug()
    {
        _cm.PrintChannel();
    }
    void PushTask(int taskcode)
    {
        
    }
    private:
    ChannelManage _cm;
    int _porcess_num;
};




















#endif