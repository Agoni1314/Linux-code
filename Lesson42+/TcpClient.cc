#include <iostream>
#include <string>
#include <memory>
#include "Socket.hpp"
#include "Common.hpp"
#include "Protocol.hpp"

using namespace SocketModule;

void Usage(std::string proc)
{
    std::cerr << "Usage: " << proc << " server_ip server_port" << std::endl;
}
void GetDataFromStdin(int *x, int *y, char *oper)
{
    std::cout << "Please Enter x:";
    std::cin >> *x;
    std::cout << "Please Enter y:";
    std::cin >> *y;
    std::cout << "Please Enter oper:";
    std::cin >> *oper;
}
// ./tcpclient server_ip server_port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    std::string server_ip = argv[1];
    uint16_t server_port = std::stoi(argv[2]);
    std::share_ptr<Socket> client = std::make_share<TcpSocket>();
    client->BuildTcpClientSocketMethod();

    if (client->Connect(server_ip, server_port) != 0)
    {
        // 失败
        std::cerr << "connect error" << std::endl;
        exit(CONNECT_ERR);
    }
    // 链接服务器成功
    while (true)
    {
        int x, y;
        char oper;
        GetDataFromStdin(&x, &y, &oper);

        std::unique_ptr<Protocol> protocol = std::make_unique<Protocol>();
        std::cout << "-----------encode req string-------------" << std::endl;
        std::cout << req_str << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        // 构建一个请求,可以直接发送的字符串
        std::string req_str = protocol->BuildRequestString(x, y, oper);
        // 发送请求
        client->Send(req_str);
        // 获取应答
        Response resp;
        bool res = protocol->GetResponse(client, resp_buffer, &resp);
        if (res == false)
            break;
        resp.ShowResult
    }
    client->Close();
    return 0;
}