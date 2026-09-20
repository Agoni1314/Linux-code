#include <iostream>
#include <memory>
#include "Command.hpp"
#include "TcpServer.hpp"

void Usage(std::string proc)
{
    std::cerr << "Usage: " << proc << " server_ip server_port" << std::endl;
}
int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        Usage(argv[2]);
        return USAGE_ERR;
    }
    uint16_t port = static_cast<uint16_t>(std::stoi(argv[1]));
    Enable_Console_Log_Strategy();
    Command command;
    auto handler = [&command](const std::string &request, InetAddr &client)
    {
        return command.Excute(request, client);
    };

    std::unique_ptr<TcpServer> server =std::make_unique<TcpServer>(port, handler);
    server->Init();
    server->Run();
    return 0;
}