#include <iostream>
#include "Common.hpp"
#include "InetAddr.hpp"

void Usage(const std::string &proc)
{
    std::cerr << "Usage: " << proc << " server_ip server_port" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return USAGE_ERR;
    }

    std::string server_ip = argv[1];
    uint16_t server_port = static_cast<uint16_t>(std::stoi(argv[2]));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "socket error" << std::endl;
        return SOCKET_ERR;
    }

    InetAddr server_addr(server_ip, server_port);
    int n = connect(sockfd, server_addr.NetAddrPtr(), server_addr.NetAddrLen());
    if (n < 0)
    {
        std::cerr << "connect error" << std::endl;
        close(sockfd);
        return CONNECT_ERR;
    }

    while (true)
    {
        std::string line;
        std::cout << "Please Enter@ ";
        if (!std::getline(std::cin, line))
        {
            break;
        }

        if (write(sockfd, line.c_str(), line.size()) < 0)
        {
            std::cerr << "write error" << std::endl;
            break;
        }

        char buffer[1024];
        ssize_t size = read(sockfd, buffer, sizeof(buffer) - 1);
        if (size > 0)
        {
            buffer[size] = '\0';
            std::cout << "server echo# " << buffer << std::endl;
        }
        else if (size == 0)
        {
            std::cout << "server closed" << std::endl;
            break;
        }
        else
        {
            std::cerr << "read error" << std::endl;
            break;
        }
    }

    close(sockfd);
    return OK;
}
