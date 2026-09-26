#include<iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "Log.hpp"
#include "Common.hpp"
#include "InetAddr.hpp"

namespace SocketModule
{
    using namespace LogModule;
    const static int gbacklog = 16;
    class Socket
    {
    public:
        virtual ~Socket() {};
        virtual void SocketOrDie() = 0;
        virtual void BindOrDie(uint16_t port)=0;
        virtual void ListemOrDie(int backlog) = 0;
        virtual std::shared_ptr<Socket> Accept(InetAddr &client) = 0;
        virtual void Close() = 0;

    public:
        void BuildTcpSocketMethod(uint16_t port, int backlog) // 模板方法模式
        {
            SocketOrDie();
            BindOrDie(port);
            ListemOrDie(backlog);
        }
    };

    const static int defaultfd = -1;
    class TcpSocket : public Socket
    {
    public:
        TcpServer() : _sockfd(defaultfd);
        {
        }
    TcpServer(int fd):_sockfd(fd)
    {}
        void SocketOrDie() override
        {
            _sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
            if(_sockfd<0)
            {
                LOG(LogLevel::FATAL) << "socket error";
                exit(SOCKET_ERR);
            }
            LOG(LogLevel::INFO) << "socket success";
        }

       void BindOrDie(uint16_t port) override
        {
            InetAddr local(port);
            int n = ::bind(_sockfd,local.NetAddrPtr(),local.NetAddrLen() );
            if(n<0)
            {
                LOG(LogLevel::FATAL) << "bind error";
                exit(BIND_ERR);
            }
            LOG(LogLevel::INFO) << "bind success";
        }

        void ListemOrDie(int backlog) override
        {
            int n = ::listen(_sockfd,backlog);
            if (n < 0)
            {
                LOG(LogLevel::FATAL) << "Listen error";
                exit(LISTEN_ERR);
            }
            LOG(LogLevel::INFO) << "Listen success";
        }
        }
         std::shared_ptr<Socket> Accept(InetAddr &client) override
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int n = ::accpet(_sockfd,CONV(peer),&len);
            if(n<0)
            {
                LOG(LogLevel::WARNING) << "accept warning ...";
                return nullptr; 
            }
            client->SetAddr(peer);
            return std::make_shared<TcpServer>(fd);
        }
        void Close() //??
        {
            if (_sockfd >= 0)
                ::close(_sockfd);
        }

    private:
        int _sockfd;
    };
}
