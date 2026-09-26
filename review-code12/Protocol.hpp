#include <iostream>
#include <string>
#include <memory>
#include "Socket.hpp"

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

    }
    bool Deserialize(std::string &in)
    {

    }
     ~Request()
     private : 
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
    }
    bool Deserialize(std::string &in)
    {
    }
     ~Request()
     private : 
        int _result;
        int _code; //异常情况
};

class Protocal
{
    public:
    Protocal(){}
    ~Protocal() {}
void GetRequest(std::shared_ptr<Socket> &sock, InetAddr &client)
{

}
    private : Request _req;
    Response _resp;
}