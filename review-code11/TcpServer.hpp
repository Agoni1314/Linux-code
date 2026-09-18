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
            :_port(port), _func(std::move(func)), _listensockfd(defaultsockfd), _isrunning(false)
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
            InetAddr loacl(_port);
            int n = bind(_listensockfd,loacl.,local.);
        }

    private:
        uint16_t _port;
        func_t _func;
        int _listensockfd;
        bool _isrunning;
};
