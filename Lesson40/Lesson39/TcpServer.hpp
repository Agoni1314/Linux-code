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
using namespace ThreadPoolModule;
 const int defaultdf = -1;
 const static int backlog = 8;
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
                _func(_sockfd, buffer, client);
            }
        }
        void Init()
        {
            //1.创建套接字
            _Listensockfd=socket(AF_INET,SOCK_DGRAM,0);
            if(_Listemsockfd<0)
            {
                LOG(LogLevel::FATAL)<<"socket error";
                exit(1);
            }
            LOG(LogLevel::INFO)<<"socket success,sockfd:"<<_sockfd; 
          
            int n=bind(_sockfd,(struct sockaddr *)&local,sizeof(local));
            if(n<0)
            {
                LOG(LogLevel::FATAL)<<"bind error";
                exit(2);
            }
             LOG(LogLevel::INFO)<<"socket success,sockfd:"<<_sockfd; 
             n=listen(_Listensockfd,backlog);//共用 n，是因为程序已经检查完 bind() 的结果，后面不再需要保存它
             if (n < 0)
            {
                LOG(LogLevel::FATAL) << "listen error";
                exit(LISTEN_ERR);
            }
            LOG(LogLevel::INFO) << "listen success: " << _listensockfd;
        }
    private:  
        int _sockfd;
        uint16_t _port;
        func_t _func;
        bool _isrunning;
};