#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Log.hpp"
#include "Common.hpp"
#include "InetAddr.hpp"

namespace SocketModule
{
    using namespace LogModule;

    const static int gbacklog = 16;
    const static int defaultfd = -1;

    class Socket
    {
    public:
        virtual ~Socket() = default;
        virtual void SocketOrDie() = 0;
        virtual void BindOrDie(uint16_t port) = 0;
        virtual void ListemOrDie(int backlog) = 0;
        virtual std::shared_ptr<Socket> Accept(InetAddr &client) = 0;
        virtual void Close() = 0;
        virtual int Recv(std::string *out) = 0;
        virtual int Send(const std::string &message) = 0;
        virtual int Connect(const std::string &server_ip, uint16_t port) = 0;

        void BuildTcpSocketMethod(uint16_t port, int backlog = gbacklog)
        {
            SocketOrDie();
            BindOrDie(port);
            ListemOrDie(backlog);
        }

        void BuildTcpClientSocketMethod()
        {
            SocketOrDie();
        }
    };

    class TcpSocket : public Socket
    {
    public:
        TcpSocket() : _sockfd(defaultfd)
        {
        }

        explicit TcpSocket(int fd) : _sockfd(fd)
        {
        }

        ~TcpSocket() override
        {
            Close();
        }

        void SocketOrDie() override
        {
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
            InetAddr local(port);
            int n = ::bind(_sockfd, local.NetAddrPtr(), local.NetAddrLen());
            if (n < 0)
            {
                LOG(LogLevel::FATAL) << "bind error";
                exit(BIND_ERR);
            }
            LOG(LogLevel::INFO) << "bind success";
        }

        void ListemOrDie(int backlog) override
        {
            int n = ::listen(_sockfd, backlog);
            if (n < 0)
            {
                LOG(LogLevel::FATAL) << "listen error";
                exit(LISTEN_ERR);
            }
            LOG(LogLevel::INFO) << "listen success";
        }

        std::shared_ptr<Socket> Accept(InetAddr &client) override
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int fd = ::accept(
                _sockfd,
                reinterpret_cast<struct sockaddr *>(&peer),
                &len);

            if (fd < 0)
            {
                LOG(LogLevel::WARNING) << "accept warning ...";
                return nullptr;
            }

            client.SetAddr(peer);
            return std::make_shared<TcpSocket>(fd);
        }

        int Recv(std::string *out) override
        {
            char buffer[1024];
            ssize_t n = ::recv(_sockfd, buffer, sizeof(buffer), 0);
            if (n > 0)
            {
                out->assign(buffer, static_cast<size_t>(n));
            }
            return static_cast<int>(n);
        }

        int Send(const std::string &message) override
        {
            return static_cast<int>(
                ::send(_sockfd, message.data(), message.size(), 0));
        }

        int Connect(const std::string &server_ip, uint16_t port) override
        {
            InetAddr server(server_ip, port);
            return ::connect(
                _sockfd,
                server.NetAddrPtr(),
                server.NetAddrLen());
        }

        void Close() override
        {
            if (_sockfd >= 0)
            {
                ::close(_sockfd);
                _sockfd = defaultfd;
            }
        }

    private:
        int _sockfd;
    };
}
