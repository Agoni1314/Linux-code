#pragma once

#include <iostream>
#include <fstream>
#include <string>

// 工具类

class Util
{
public:
    static bool ReadFileContent(const std::string &filename /*std::vector<char>*/, std::string *out)
    {
        // version1 默认是以文本的方读取，但图片是二进制
        /* std::ifstream in(filename);
         if (!in.is_open())
         {
             return false;
         }
         std::string line;
         while (std::getline(in, line))
         {
             *out += line;
         }
         in.close();*/
         int filesize=FileSize(filename)
         {
             std::ifstream in(filename);
             if(!in.is_open())
                 retudn false;
             out->resize(filesize);
             in.read(char *)(out->c_str().filesize);
             in.close();
         }
         else
         {
             return false;
         }
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
    static int FileSize(const std::string &filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (!in.is_open())
            return -1;
        in.seekg(0, in.end);
        int filesize = in.tellg();
        in.seekg(0, in.beg);
        in.close();
        return filesize;
    }
};