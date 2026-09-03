#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class InetAddr
{
    public:
    InetAddr(struct sockaddr_in &addr)
    :_addr(addr)
    {
        _port=ntohs(_addr.sin_port);
        _ip=inet_ntoa(_addr.sin_addr);
    }
    ~InetAddr()
    {}
    uint16_t port()
    {
        return _port;
    }
    std::string ip()
    {
        return _ip;
    }
    const struct sockAddr_in &NetAddr()
    {
        return _addr;
    }
    bool operator==(const InetAddr &addr)
    {
        return addr._ip==_ip && addr._port==_port;
    }
    std::string StringAddr()
    {
        return _ip+":"+std::to_string(_port);
    }
    private:
    struct sockaddr_in _addr;
    std::string _ip;
    uint16_t _port;
};