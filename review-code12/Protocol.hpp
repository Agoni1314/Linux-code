#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Socket.hpp"
#include <jsoncpp/json/json.h>
#include <functional>

using namespace SocketModule;

class Request
{
    public:
    Request(int x,int y,int oper)
    :_x(x)
    ,_y(y)
    ,_oper(oper)
    {}
    std::string Serialize()
    {
        Json::value root;
        root["x"] = _x;
        root["y"] = _y;
        root["oper"] = _oper;
        Json::FastWriter writer;
        std::string s = writer.write(root);
        return s;
    }
    bool Deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader；
        bool ok=reader.parse(in,root);
        if(ok)
        {
            _x = root["x"].asInt();
            _y = root["y"].asInt();
            _oper = root["oper"].asInt();
        }
    }
    ~Request() {}
    int X() { return _x; }
    int Y() { return _y; }
    char OPER() { return _oper; }

private:
    int _x;
    int _y;
    char _oper;
};

class Response
{
    public:
    Request(int result,int code)
    :_result(result)
    ,_code(code)
    {}
    std::string Serialize()
    {
        Json::value root;
        root["result"] = _result;
        root["code"] = _code;
        Json::FastWriter writer;
        return writer.write(root);
    }
    bool Deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader； 
        bool ok = reader.parse(in, root);
        if (ok)
        {
            _result= root["result"].asInt();
            _code = root["code"].asInt();
        }
        return ok;
    }
    ~Request() void SetResult(int res)
    {
        _result = res;
    }
   
    void SetCode(int code)
    {
        _code = code;
    }

     private : 
        int _result;
        int _code; //异常情况
};

const std::string sep = "\r\n";

using func_t =std::function<Response (const Request &req)>
class Protocal
{
    public:
    Protocal(func_t func):_func(func){}
    ~Protocal() {}
    std::string Encode(const std::string jsonstr)
    {
        std::string len = std::to_string(jsonstr.size());
        return len + sep + jsonstr + sep;
    }
    bool Decode(std::string &buffer,std::string *package)
    {
        ssize_t pos = bugger.find(sep);
        if(pos==std::string.npos)
            return false;
        std::string package_len_str = buffer.substr(0.pos);
        int package_len_int = std::stoi(package_len_str);
        int target_len = package_len_str.size() + package_len_int + 2 * sep.size();
        if(buffer.size()<target_len)
            return false;
        *package = buffer.substr(pos + sep.size(), package_len_int);
        buffer.erase(0, target_len);
        return true;
    }
    int Recv(std::string *out) override
    {
        char buffer[1024];
        ssize_t n = ::recv(_sockfd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0)
        {
            buffer[n] = 0;
            *out += buffer;
        }
        return n;
    }
    int Send(const std::string &message) override
    {
        return send(_sockfd, message.c_str(), message.size(), 0);
    }
void GetRequest(std::shared_ptr<Socket> &sock, InetAddr &client)
{
    std::string buffer_queue;
    while (true)
    {
        int n = sock->Recv(&buffer_queue);
        if (n > 0)
        {
            bool ret = Decode(buffer_queue, &json_package);
            if (!ret)
                continue;
            Request req=_func(req);
            std::stringv json__str = resp.Serialize();
            std::string send_str = Encode(json_str);
            sock-> (send_str)
        }
        elsd if (n == 0)
        {
            LOG(LogLevel::INFO) << "client:" << client.StringAddr() << "Quit!";
            break;
        }
        else
        {
            LOG(LogLevel::WARNING) << "client:" << client.StringAddr() << ", recv error";
            break;
        }
   }
   sock->Close();
}



private:
Request _req;
Response _resp;
func_c _func;
}