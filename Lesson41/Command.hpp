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
    }

    bool IsSafeCommand(const std::string &cmd) const
    {
        return _white_list.find(cmd) != _white_list.end();
    }

    std::string Execute(const std::string &cmd, InetAddr &addr)
    {
        if (!IsSafeCommand(cmd))
        {
            return "bad command";
        }

        FILE *fp = popen(cmd.c_str(), "r");
        if (fp == nullptr)
        {
            return "command execute error: " + cmd;
        }

        std::string output;
        char line[1024];
        while (fgets(line, sizeof(line), fp) != nullptr)
        {
            output += line;
        }

        pclose(fp);

        std::string result =
            addr.StringAddr() + " execute done, result is:\n" + output;
        LOG(LogLevel::DEBUG) << result;
        return result;
    }

private:
    std::set<std::string> _white_list;
};
