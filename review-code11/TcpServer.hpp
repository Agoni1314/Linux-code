#pragma once

#include "Common.hpp"
#include "Log.hpp"
#include "InetAddr.hpp"
#include <cerrno>
#include <memory>
#include <pthread.h>
#include <signal.h>

using namespace LogModule;
const static int defaultsockfd = -1;
const static int backlog = 8;
using func_t = std::function<std::string(std::string &, InetAddr &)>;

class TcpServer : public NoCopy
{
    public:
        TcpServer(uint16_t port, func_t func)
            : _port(port),
              _func(std::move(func)), // func 已经是构造函数内部的局部对象。把它移动到 _func 中，通常可以避免一次不必要的复制
              _listensockfd(defaultsockfd),
              _isrunning(false)
        {} 
        void Init()
        {
            signal(SIGPIPE, SIG_IGN);
            _listensockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (_listensockfd < 0)
            {
                LOG(LogLevel::FATAL) << "socket error";
                exit(SOCKET_ERR);
            }
            int opt = 1;
            setsockopt(_listensockfd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));
            InetAddr local(_port);
            int n = bind(_listensockfd,local.NetAddrPtr(),local.NetAddrLen());
            if (n < 0)
            {
                LOG(LogLevel::FATAL) << "bind error";
                exit(BIND_ERR);
            }
            n = listen(_listensockfd, backlog);
            if (n < 0)
            {
                LOG(LogLevel::FATAL) << "listen error";
                exit(LISTEN_ERR);
            }

            LOG(LogLevel::INFO) << "tcp server init success, listen fd: " << _listensockfd;
        }
        void Run()
        {
            _isrunning = true;
            while(_isrunning)
            {
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sockfd = accept(_listensockfd,CONV(peer),&len);
                if (sockfd < 0)
                {
                    if (errno == EINTR)
                    {
                        continue;
                    }

                    LOG(LogLevel::WARNING) << "accept error";
                    continue;
                }
                InetAddr addr(peer);
                LOG(LogLevel::INFO) << "accept success, peer: " << addr.StringAddr();

                ThreadData *data = new ThreadData(sockfd, addr, this);
                pthread_t tid;
                int ret = pthread_create(&tid, nullptr, Routine, data);
                if (ret != 0)
                {
                    LOG(LogLevel::WARNING) << "pthread_create error";
                    close(sockfd);
                    delete data;
                }
            }
        }
        ~TcpServer()
        {
            if (_listensockfd >= 0)
            {
                close(_listensockfd);
            }
        }
        private:
            class ThreadData
            {
            public:
                ThreadData(int fd, const InetAddr &peer, TcpServer *server)
                    : sockfd(fd), addr(peer), tsvr(server)
                {
                }

                int sockfd;
                InetAddr addr;
                TcpServer *tsvr;
            };
            static bool SendAll(int sockfd,const std::string &data)
            {
                size_t total = 0;
                while(total<data.size())
                {
                    ssize_t n = write(sockfd, data.c_str() + total, data.size() - total);
                    if (n < 0 && errno == EINTR)
                    {
                        continue;
                    }
                    if (n <= 0)
                    {
                        return false;
                    }
                    total += static_cast<size_t>(n);
                }
                return true;
            }

    private:
        uint16_t _port;
        func_t _func;
        int _listensockfd;
        bool _isrunning;
};
