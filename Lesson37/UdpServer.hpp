#pragma once

 #include<iostream>
 #include<string>
  #include<strings.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include<netinet/in.h>
 #include<arpa/inet.h>

 #include"Log.hpp"

using namespace LogModule;
 const int defaultdf = -1;
class UdpServer
{
    public:
        UdpServer(std::string &ip，uint16_t port)
        ：_sockfd(defaultdf)
        _ip(ip)
        _port(port)
        {}
        ~UdpServer();
        void Start()
        {
            _isrunning = true;
            while(_isrunning)
            {
                char buffer[1024]
            }
        }
        void Init()
        {
            //1.创建套接字
            _sockfd=socket(AF_INET,SOCK_DGRAM,0);
            if(_sockfd<0)
            {
                LOG(Loglevel::FATAL)<<"socket error";
                exit(1);
            }
            LOG(Loglevel::INFO)<<"socket success,sockfd:"<<_sockfd; 
            //2.绑定socket信息，ip和端口
            //2.1 填充sockaddr_in结构体
            struct sockaddr_in  local;
            bzero(&local,sizeof(local));
            local.sin_family=AF_INET;
            //IP信息和端口信息都要发送到网络
            local.sin_port=htons(_port);
            //IP地址转4字节，4字节转成网络序列->in_inet_addr(const char *cp)
            local.sin_adr.s_addr=inet_addr(_ip.c_str());
            int n=bind(_sockfd,(struct sockaddr *)&local,sizeof(local));
            if(n<0)
            {
                LOG(Loglevel::FATAL)<<"bind error";
                exit(2);
            }
             LOG(Loglevel::INFO)<<"socket success,sockfd:"<<_sockfd; 

        }
    private:  
        int _sockefd;
        uint16_t port;
        std::string _ip;
};