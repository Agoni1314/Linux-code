#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

// ./udpclient server_ip server_port
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
        return 2;
    }

    // 2. 本地的ip和端口是什么？要不要和上面的“文件”关联呢？
    // 问题：client要不要bind？需要bind.
    //       client要不要显式的bind?不要！！首次发送消息，OS会自动给client进行bind，OS知道IP，端口号采用随机端口号的方式
    //   为什么？一个端口号，只能被一个进程bind，为了避免client端口冲突
    //   client端的端口号是几，不重要，只要是唯一的就行！
    // 填写服务器信息
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());
    while(true)
    {
        std::string input;
        std::cout << "Please Enter# ";
        std::getline(std::cin, input);

        int n = sendto(sockfd, input.c_str(), input.size(), 0, (struct sockaddr*)&server, sizeof(server));
        (void)n;

        char buffer[1024];
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int m = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&peer, &len);
        if(m > 0)
        {
            buffer[m] = 0;
            std::cout << buffer << std::endl;
        }
    }


    return 0;
}