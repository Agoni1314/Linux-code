
#include<memory>
#include"TcpServer.hpp"

using namespace SocketModule;
int main()
{

    if (argc != 2)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    std::unique_ptr<Protocol> protocol = std::make_unique<Protocol>(); //构建一个服务器对象

    std::unique_ptr<TcpServer> tsvr = std::make_unique<TcpServer>(std::stoi(argv[1]),
                                                                  [&protocol](std::shared_ptr<Socket> &sock, InetAddr &client)
                                                                  {
                                                                      protocol->GetRequest(sock, client);
                                                                  });
    tsvr->Start();
    return 0;
}