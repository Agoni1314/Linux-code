#pragma once

#include "Common.hpp"

class InetAddr
{
public:
    InetAddr() : _ip(), _port(0), _addr()
    {
    }
    InetAddr(const struct sockaddr_in addr) : _addr(addr)
    {
        _port = ntohl(addr.sin_port);
    }

private:
    std::string _ip;
    uint16_t _port;
    struct sockaddr_in _addr;
};