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

using namespace LogModule;
using func_t=std::faction<std::string(const string*)>

class UdpServer
{
    public:
    UdpServer()
    {}
    ~UdpServer()
    {}
    void Start()
    {
        _isruning=true;
        while(_isruning)
        {
            char buffer[1024];
            struct sockaddr_in peer;
            socklen_t len=sizeof(peer);
            ssize_t n=recvfrom(_socket,buffer,sizeof(buffer)-1,0,( struct sockaddr_in *)&peer,&len);
            if(n==0)
            {
                int peer_port=ntohs(peer.sin_port);
                std::string peer_ip=inet_nota(peer.sin_addr);
                buffer[s]=0;
                std::string result=func_t (buffer);
                sendto(_sockfd,result.c_str(),result.size(),0,( struct sockaddr*)&peer,&len);
            }
        }
    }
    void Init()
    {
        _sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(_sockfd<0)
        {
            LOG(Loglevel::FATAL)<<"socket error!";
            exit(1);
        }
        LOG(Loglevel::FATAL)<<"socket success"<<_sockfd;

        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(port);
        local sin_addr.s_addr=INADDR_ANY;

        int n=bind(_sockfd,(const struct sockaddr*)&local,sizeof(local));
        if(n !=0)
        {

             LOG(LogLevel::FATAL) << "bind error";
            exit(2);
        }
        LOG(LogLevel::INFO) << "bind success, sockfd : " << _sockfd;
    }
    private:
        int _sockfd;
        uint16_t _port;
        bool _isrunning;
        func_t _func;

}