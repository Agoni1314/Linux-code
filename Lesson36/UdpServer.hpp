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
        {}
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
            local.sin_port=;
            local.sin_adr.s_addr=;
            int n=bind(_sockfd,)
        }
    private:  
        int _sockefd;
        uint16_t port;
        std::string _ip;
};