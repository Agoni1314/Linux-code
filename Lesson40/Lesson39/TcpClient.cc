#include <iostream>
#include "Common.hpp"
#include "InetAddr.hpp"


int sockfd = 0;
std::string server_ip;
uint16_t server_port = 0;
pthread_t id;
using namespace ThreadModlue;


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " server_ip server_port" << std::endl;
        return 1;
    }
    std::string server_ip = argv[1];
    uint16_t server_port = std::stoi(argv[2]);

    // 1. 创建socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        std::cerr << "socket error" << std::endl;
        return (SOCKET_ERR);
    }
    while(true)
    {
        //发一句
        std::string line;
        std::cout<<"please tall#";
        std::getline(std::cin,line);
        wirte(sockfd,line.c_str(),line.size());

        //返回一句
        char buffer[1024];
        ssize_t size=read(sockfd,buffer,sizeof(buffer)-1);
        if(size>0)
        {
            buffer[size]=0;
            std::cout << "server echo# " << buffer << std::endl;
        }
        
    }
    close(sockfd);

    return 0;
}