#pragma once

#include <iostream>
#include <fstream>
#include <string>

// 工具类

class Util
{
public:
    static bool ReadFileContent(const std::string &filename, std::string *out)
    {
        // version1
        std::ifstream in(filename);
        if (!in.is_open())
        {
            return false;
        }
        std::string line;
        while (std::getline(in, line))
        {
            *out += line;
        }
        in.close();
        return true;
    }
    static bool ReadOneLine(std::string &bigstr, std::string *out, const std::string &sep /*\r\n*/)
    {
        auto pos = bigstr.find(sep);
        if (pos == std::string::npos)
            return false;

        *out = bigstr.substr(0, pos);
        bigstr.erase(0, pos + sep.size());
        return true;
    }
    
};