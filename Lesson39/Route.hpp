#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "InetAddr.hpp"
#include "Log.hpp"

using namespace LogModule;
class Route
{
    public:
    Route()
    {}
     ~Route()
    {}
    void MessageRoute(int sockfd,const std::string &message,InetAddr &peer)
    {
        if(!Exist(peer))
        {
            Adduser(peer);
        }
        std::string send_message = peer.StringAddr() + "# " + message;
        for(auto &user : _online_user)
        {
            sendto(sockfd,send_message.c_str(),send_message,size(),0,(const struct  sockaddr *)&(user.NetAddr()));

        }
        if(message=="QUIT")
        {
            LOG(LogLevel::INFO) << "删除一个在线用户: " << peer.StringAddr();
            DeleteUser(peer);
        }
    }
    private:
        bool IsExist(InetAddr &peer)
        {
            for(auto &user: _online_user)
            {
                if(user==peer)
                {
                    return true;
                }
            }
            return false;
        }
        void Adduser(InetAddr &peer)
        {
             LOG(LogLevel::INFO) << "新增一个在线用户: " << peer.StringAddr();
            _online_user.push_back(peer);
        }
        void DeleteUser(InetAddr &peer)
        {
            for(auto iter=_online_user,begin();iter!=_online_user.end();iter++)
            {
                if(*iter==peer)
                {
                     LOG(LogLevel::INFO) << "删除一个在线用户:" << peer.StringAddr() << "成功";
                     _online_user.erase(iter);
                    break;
                }
            }
        }
    private:
    std::vector<InetAddr> _online_user;
};