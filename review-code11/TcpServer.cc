#include <iostream>
#include <memory>
#include "Command.hpp"
#include "TcpServer.hpp"
#include "Dict.hpp"

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

    Dict d;
    std::unique_ptr<TcpServer> tsvr = std::make_unique<TcpServer>(port,
                                                                  std::bind(&Command::Execute, &cmd, std::placeholders::_1, std::placeholders::_2));
    //std::unique_ptr<TcpServer> tsvr = std::make_unique<TcpServer>(port, [&d](const std::string &word, InetAddr &addr){return d.Translate(word, addr); });
    tsvr->Init();
    tsvr->Run();
    return 0;
}