#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "Common.hpp"
#include "Log.hpp"
#include "InetAddr.hpp"

namespace SocketModule
{
    using namespace LogModule;
    const static gbacklog=16;

    class Socket
    {
        public:
        virtual void SocketOrDie()=0;
        virtual void BindOrDie(uint16_t port)=0;
        virtual void ListenOrDie(int backlog)=0;
        virtual std::shared_ptr<socket> Accept(InetAddr *client)=0;
        virtual void Close()=0;

        //TCP 监听 socket 的创建顺序
         void BuildTcpSocketMethod(uint16_t port, int backlog = gbacklog)
        {
            SocketOrDie();
            BindOrDie(port);
            ListenOrDie(backlog);
        }
    };

        const static int defaultfd = -1;
        class TcpSocket : Socket
        {
            public:
            TcpSocket()
            ~TcpSocket()
            :_sockfd(defaultfd)
            {}
             TcpSocket()
             :_sockfd(fd)
             {}
             void SocketOrDie() override
            {
                //前面的 :: 表示到全局作用域寻找函数
                _sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
                if (_sockfd < 0)
                {
                    LOG(LogLevel::FATAL) << "socket error";
                    exit(SOCKET_ERR);
                }
                LOG(LogLevel::INFO) << "socket success";
            }
             void BindOrDie(uint16_t port) override
            {
                InetAddr localaddr(port);
                int n = ::bind(_sockfd, localaddr.NetAddrPtr(), localaddr.NetAddrLen());
                if (n < 0)
                {
                    LOG(LogLevel::FATAL) << "bind error";
                    exit(BIND_ERR);
                }
                LOG(LogLevel::INFO) << "bind success";
            }
            void ListenOrDie(int backlog) override
            {
                int n = ::listen(_sockfd, backlog);
                if (n < 0)
                {
                    LOG(LogLevel::FATAL) << "listen error";
                    exit(LISTEN_ERR);
                }
                LOG(LogLevel::INFO) << "listen success";
            }
            std::shared_ptr<Socket> Accept(InetAddr *client) override
            {
                struct sockaddr_in peer;
                socklen_t len=sizeof(peer);
                int fd=::accept(_sockfd,CONV(peer),&len);
                if(fd < 0)
            {
                LOG(LogLevel::WARNING) << "accept warning ...";
                return nullptr; 
            }
            client->SetAddr(peer);
            return std::make_shared<TcpSocket>(fd);
        }
            void Close() 
            {
                if(_sockfd >= 0)
                    ::close(_sockfd);
            }
                
            private:
            int _sockfd;
        };
};