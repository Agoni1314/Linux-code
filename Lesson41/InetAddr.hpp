#pragma once

#include "Common.hpp"

class InetAddr
{
public:
    InetAddr() : _addr{}, _port(0), _ip()
    {
    }

    explicit InetAddr(const struct sockaddr_in &addr) : _addr(addr)
    {
        _port = ntohs(_addr.sin_port);

        char ip_buffer[INET_ADDRSTRLEN] = {0};
        if (inet_ntop(AF_INET, &_addr.sin_addr, ip_buffer, sizeof(ip_buffer)) != nullptr)
        {
            _ip = ip_buffer;
        }
    }

    InetAddr(const std::string &ip, uint16_t port)
        : _addr{}, _port(port), _ip(ip)
    {
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr);
    }

    explicit InetAddr(uint16_t port)
        : _addr{}, _port(port), _ip("0.0.0.0")
    {
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        _addr.sin_port = htons(_port);
    }
    void SetAddr(struct sockaddr_in &addr)
    {
        _addr=addr;
        _port=htons(_addr,sin_port);
        char ipbuffer[64];
        inet_ntop( inet_ntop(AF_INET, &_addr.sin_addr, ipbuffer, sizeof(_addr)));
        _ip = ipbuffer;
    }
    uint16_t Port() const
    {
        return _port;
    }

    const std::string &Ip() const
    {
        return _ip;
    }

    const struct sockaddr_in &NetAddr() const
    {
        return _addr;
    }

    const struct sockaddr *NetAddrPtr() const
    {
        return reinterpret_cast<const struct sockaddr *>(&_addr);
    }

    socklen_t NetAddrLen() const
    {
        return sizeof(_addr);
    }

    bool operator==(const InetAddr &addr) const
    {
        return _ip == addr._ip && _port == addr._port;
    }

    std::string StringAddr() const
    {
        return _ip + ":" + std::to_string(_port);
    }

private:
    struct sockaddr_in _addr;
    uint16_t _port;
    std::string _ip;
};
