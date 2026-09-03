#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"
#include "InetAddr.hpp"

using namespace LogModule;
 const int defaultdf = -1;
 using func_t = std::function<void(int sockfd,const std::string &, InetAddr &)>;
class UdpServer
{
    public:
       UdpServer(uint16_t port, func_t func)
    : _sockfd(defaultdf),
      _port(port),
      _func(func),
      _isrunning(false)
        {
        }
        ~UdpServer()
        {}
       void Start()
        {
            _isrunning = true;

            while (_isrunning)
            {
                char buffer[1024];

                struct sockaddr_in peer{};
                socklen_t len = sizeof(peer);

                // 1. 接收客户端发送的单词
                ssize_t n = recvfrom(
                    _sockfd, buffer,sizeof(buffer) - 1, 0,reinterpret_cast<struct sockaddr *>(&peer), &len );

                if (n < 0)
                {
                    continue;
                }

                // recvfrom接收的是字节，需要手动补字符串结束符
                buffer[n] = '\0';

                // 2. 封装客户端的IP和端口
                InetAddr client(peer);

                // 3. 调用Dict::Translate()
                std::string response = _func(buffer, client);

                // 4. 把翻译结果发送回客户端
                sendto(  _sockfd,response.c_str(), response.size(), 0, reinterpret_cast<struct sockaddr *>(&peer),len  );
            }
        }
        void Init()
        {
            //1.创建套接字
            _sockfd=socket(AF_INET,SOCK_DGRAM,0);
            if(_sockfd<0)
            {
                LOG(LogLevel::FATAL)<<"socket error";
                exit(1);
            }
            LOG(LogLevel::INFO)<<"socket success,sockfd:"<<_sockfd; 
            //2.绑定socket信息，ip和端口
            //2.1 填充sockaddr_in结构体
            struct sockaddr_in  local;
            bzero(&local,sizeof(local));
            local.sin_family=AF_INET;
            //IP信息和端口信息都要发送到网络
            local.sin_port=htons(_port);
            //IP地址转4字节，4字节转成网络序列->in_inet_addr(const char *cp)
            local.sin_addr.s_addr= htonl(INADDR_ANY);;
            int n=bind(_sockfd,(struct sockaddr *)&local,sizeof(local));
            if(n<0)
            {
                LOG(LogLevel::FATAL)<<"bind error";
                exit(2);
            }
             LOG(LogLevel::INFO)<<"socket success,sockfd:"<<_sockfd; 

        }
    private:  
        int _sockfd;
        uint16_t _port;
        func_t _func;
        bool _isrunning;
};