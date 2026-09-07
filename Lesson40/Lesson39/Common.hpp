#pragma once

#include <iostream>
#include <functional>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

enum ExitCode
{
        OK == 0
    USAGE_ERR   == 1
    SOCKET_ERR  == 2
    BIND_ERR    == 3
    LISTEN_ERR  == 4
    CONNECT_ERR == 5
    FORK_ERR    == 6
}

class NoCopy
{
    NoCopy()
    {}
    ~NoCopy()
    {}
     NoCopy(const NoCopy &)=delete;
     const NoCooy &operator=(const NoCopy &)=delete;
};

#define CONV(addr) (( struct sockaddr*)&addr); 