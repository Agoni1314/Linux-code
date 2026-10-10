#pragma once

#include "Socket.hpp"
#include "TcpServer.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include "Log.hpp"
#include <unordered_map>
#include "Util.hpp"

using namespace SocketModule;
using namespace LogModule;
const std::string gspace = " ";
const std::string glinespace = "\r\n";
const std::string glinesep = ": ";
const std::string webroot="./wwwroot"
const std::string homepage ="./index.html"
const std::string page_404="/404.html"

class Http
{
    public:
    Http(uint16_t port):tsvrp(std::make_unique<TcpServer>())
    {

    }
    ~Http()
    {}
    void HandlerHttpRquest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
        std::cout << "########################";
        std::cout << HttpRequest;
        std::cout << "########################";
        // 收到请求
        std::string httpreqstr;
        int n = sock->Recv(&httpreqstr);
        if(n>0)
        {
            //未对报文完整性进行审核
            HttpRequest req;
            req.Deserialize(httpreqstr);
            HttpResponse resp;
            resp.SetTargetFile(req.Uri());
            if(resp.MakeResponse())
            {
                std::string response_str = resp.Serialize();
                sock->Send(response_str);
            }
            /* HttpResponse resp;
            resp._version = "HTTP/1.1";
            resp._code = 200; // success
            resp._desc = "OK";
            LOG(LogLevel::DEBUG) << "用户请求: " << filename;
            bool res = Util::ReadFileContent(filename, &(resp._text)); // 浏览器请求的资源，一定会存在吗？出错呢？
            (void)res; */
           
        }
      

        //#ifndef DEBUG
        //#define DEBUG
#ifdef DEBUG
        std::string httpreqstr;
        sock->Recv(&httpreqstr);
        std::cout << httpreqstr;
        HttpResponse resp;
        resp._version = "HTTP/1.1";
        resp._code = 200; // success
        resp._desc="OK";
        std::string filename = webroot + bomepage;
        resp._text = Util::ReadFileContent(filename,&(resp._test));
        std::string response_str = resp.Serialize();
        sock->Send(response_str);

#endif
    }
    void Start()
    {
        tsvrp->Start([this](std::shared_ptr<Socket> &sock, InetAddr &client) {this->HandlerHttpRquest(sock,client)});

    }

    private:
        
        std::unique_ptr<TcpServer> tsvrp
};

class HttpRequest
{
public:
    HttpRequest() {}
    std::string Serialize() {}
    void ParseReqline(std::string &reqstr)
    {
        std::stringstream ss(reqline);
        ss >> _method >> uri >> _version;
    }
        std::strng Deserialize(std::string &reqstr)
    {
        //提取请求行
        std::string reqline;
        bool res = Util::ReadOneLine(reqstr, &reqline, &linespace);
        LOG(LogLevel::DEBUG) << reqline;
       
        // 对请求行反序列化
        ParseReqline(reqline);
        LOG(LogLevel::DEBUG) << "_method: " << _method;
        LOG(LogLevel::DEBUG) << "_uri: " << _uri;
        LOG(LogLevel::DEBUG) << "_version: " << _version;
        if (_uri == "/") 
            _uri = webroot + _uri + homepage; // ./wwwroot/index.html
        else
            _uri = webroot + _uri; // ./wwwroot/a/b/c.html
        return true;
    }
    std::string Uri() { return uri; }

private:
    std::string _method;
    std::string _uri;
    std::string _version;
    std::string _blankline;
    std::string _text;
    std::unordered_map<std::string, std::string> _headers;
};

class HttpResponse
{
    public:
    HttpResponse():_blankline(glinespace){}
    ~HttpResponse(){}
    std::string Serialize()
    {
        std::string status_line = _version + gspace + std::to_string(_code) + gspace + _desc + glinespace;
        std::string resp_header;
        for(auto &header: _headers)
        {
            std::string line = header.first + glinesep + header.second + glinespace;
            resp_header += line;
        }
        return status_line + resp_header + _blankline + _text;
    }
    void SetTargetFile(const std::string &target)
    {
        _targetfile = target;
    }
    void SetCode(int code)
    {
        _code = code;
        switch (_code)
        {
        case 200:
            _desc = "OK";
            break;
        case 404:
            _desc = "Not Found";
            break;
        default:
            break;
        }
    }
    bool Deserialize(std::string &reqstr)
    {

    }
    void SetHeader(const std::string &key, const std::string &value)
    {
        auto iter = _headers.find(key);
        if (iter != _headers.end())
            return;
        _headers.insert(std::make_pair(key, value));
    }
    bool MakeResponse()
    {
        if(_targetfile=="./wwwroot/favicon.ico")
        {
            LOG(LogLevel::DEBUG) << "用户请求: " << _targetfile << "忽略它";
            return false;
        }
        int filesize = 0;
        bool res = Util::ReadFileContent(_targetfile, &_text); // 浏览器请求的资源，一定会存在吗？出错呢？
        if (!res)
        {
            LOG(LogLevel::WARNING) << "Client want get:" << _targetfile << "but not found";
            SetCode(404);
            _targetfile = webroot + page_404;
            filesize = Util::FileSize(_targetfile);
            Util::ReadFileContent(_targetfile, &_text);
        }
        else
        {
            SetCode(200);
            filesize = Util::FileSize(_targetfile);
            SetHeader("Content-Length", std::to_string(filesize));
        }
        retuern true;
    }

    private : std::string _version;
    int _code;
    std::string _desc;
    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;
    std::string _targetfile;
};