#pragma once

#include <cstdio>
#include <set>
#include <string>
#include "InetAddr.hpp"
#include "Log.hpp"

using namespace LogModule;

class Command
{
public:
    Command()
    {
        _white_list.insert("ls");
        _white_list.insert("pwd");
        _white_list.insert("ls -l");
        _white_list.insert("touch haha.txt");
        _white_list.insert("who");
        _white_list.insert("whoami");
    } // 函数内部不能通过 cmd 修改传入的字符串
    bool IsSafeCommand(const std::string &cmd) const
    { // 函数不会修改当前 Command 对象的成员数据
        return _white_list.find(cmd) != _white_list.end();
    }
    std::string Execute(std::string &cmd, InetAddr &addr)
    {
        if (!IsSafeCommand(cmd))
        {
            std::cout << "command error";
        }
        FILE *fp = popen(cmd.c_str(), "r"); // 启动命令，并读取命令的标准输出
        if (fp == nullptr)
        {
            return "command execute error: " + cmd;
        }
        std::string output;
        char line[1024];
        while (!fgets(line, sizeof(line), fp))
        {
            output += line;
        }
        pclose(fp);
        std::string result = addr.StringAddr() + " execute done, result is:\n" + output;
        LOG(LogLevel::DEBUG) << result;
        return result;
    }

private:
    std::set<std::string> _white_list;
};