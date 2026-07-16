#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "."
#define FILENAME "fifo"

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

class NamedFifo
{
public:
    NamedFifo(const std::string &path, const std::string &name)
        : _path(path), _name(name)
    {
        _fifoname = _path + "/" + _name;
        umask(0);
        // 新建管道
        int n = mkfifo(_fifoname.c_str(), 0666);
        if (n < 0)
        {
            ERR_EXIT("mkfifo");
        }
        else
        {
            std::cout << "mkfifo success" << std::endl;
        }
    }
    ~NamedFifo()
    {
        // 删除管道文件
        int n = unlink(_fifoname.c_str());
        if (n == 0)
        {
            ERR_EXIT("unlink");
        }
        else
        {
            std::cout << "remove fifo failed" << std::endl;
        }
    }

private:
    std::string _path;
    std::string _name;
    std::string _fifoname;
};

class FileOper
{
public:
    FileOper(const std::string &path, const std::string &name)
        : _path(path), _name(name), _fd(-1)
    {
        _fifoname = _path + "/" + _name;
    }
    void OpenForRead()
    {
        // 打开, write 方没有执行open的时候，read方，就要在open内部进行阻塞
        // 直到有人把管道文件打开了，open才会返回！
        _fd = open(_fifoname.c_str(), O_RDONLY);
        if (_fd < 0)
        {
            ERR_EXIT("open");
        }
        std::cout << "open fifo success" << std::endl;
    }
    void OpenForWrite()
    {
        // write
        _fd = open(_fifoname.c_str(), O_WRONLY);
        if (_fd < 0)
        {
            ERR_EXIT("open");
        }
        std::cout << "open fifo success" << std::endl;
    }
    void Write()
    {
        // 写入操作
        std::string message;
        int cnt = 1;
        pid_t id = getpid();
        while (true)
        {
            std::cout << "Please Enter# ";
            std::getline(std::cin, message);
            message += (", message number: " + std::to_string(cnt++) + ", [" + std::to_string(id) + "]");
            write(_fd, message.c_str(), message.size());
        }
    }
    void Read()
    {
        // 正常的read
        while (true)
        {
            char buffer[1024];
            int number = read(_fd, buffer, sizeof(buffer) - 1);
            if (number > 0)
            {
                buffer[number] = 0;
                std::cout << "Client Say# " << buffer << std::endl;
            }
            else if (number == 0)
            {
                std::cout << "client quit! me too!" << std::endl;
                break;
            }
            else
            {
                std::cerr << "read error" << std::endl;
                break;
            }
        }
    }
    void Close()
    {
        if (_fd > 0)
            close(_fd);
    }
    ~FileOper()
    {
    }

private:
    std::string _path;
    std::string _name;
    std::string _fifoname;
    int _fd;
};