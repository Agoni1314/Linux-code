#include <iostream>
#include <memory>
#include <sstream>
#include "TcpServer.hpp"
#include "Socket.hpp"
#include "Util.hpp"
#include "Log.hpp"

using namespace SocketModule;

const std::string gspace = " ";
const std::string glinespace = "\r\n";
const std::string glinesep = ": ";
const std::string webroot = "./wwwroot";
const std::string homepage = "/index.html";

class HttpRequest
{
public:
    HttpRequest()
    {
    }
    std::string Serialize()
    {
        return std::string();
    }
    void ParSeReqLine(std::string &reqline)
    {
        std::stringstream ss(reqline);
        ss >> _method >> _uri >> _version;
    }
    bool Deserialize(std::string &reqstr)
    {
        // 提取请求行然后反序列化
        std::string reqline;
        bool res = Util::ReadOneLine(reqstr, &reqline, glinespace);
        LOG(LogLevel::DEBUG) << "reqline";

        ParSeReqLine(reqline);
        LOG(LogLevel::DEBUG) << "_method" << _method;
        LOG(LogLevel::DEBUG) << "_uri" << _uri;
        LOG(LogLevel::DEBUG) << "_version" << _version;
        if (_uri == "/")
        {
            _uri = webroot + _uri + homepage;
        }
        else
        {
            _uri = webroot + _uri;
        }
        return true;
    }
    std::string Uri() { return _uri; }
    ~HttpRequest()
    {
    }

private:
    std::string _method;
    std::string _uri;
    std::string _version;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;
};

class Httpresponse
{
    friend class Http;

public:
    Httpresponse() : _blankline(glinespace)
    {
    }
    ~Httpresponse()
    {
    }
    std::string Serialize()
    {
        std::string ststus_line = _version + gspace + std::to_string(_code) + _desc + glinespace;
        std::string resp_header;
        for (auto &header : _headers)
        {
            std::string line = header.first + glinesep + header.second + glinespace;
            resp_header += line;
        }
        return ststus_line + resp_header + _blankline + _text;
    }
    bool Deserialize(std::string &reqstr)
    {
        return true;
    }

private:
    int _code;
    std::string _desc;
    std::string _version;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;
};

class Http
{
public:
    Http(uint16_t port) : tsvrp(std::make_unique<TcpServer>(port))
    {
    }
    ~Http()
    {
    }
    void HandlerHttpRquest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
        std::string httpreqstr;
        int n = sock->Recv(&httpreqstr);
        if (n > 0)
        {
            HttpRequest req;
            req.Deserialize(httpreqstr);
            std::string filename = req.Uri();
            Httpresponse resp;
            resp._version = "HTTP/1.1";
            resp._code = 200;
            resp._desc = "OK";
            LOG(LogLevel::DEBUG) << "用户请求" << filename;
            bool res = Util::ReadFileContent(filename, &(resp._text));
            (void)res;
            std::string response_str = resp.Serialize();
            sock->Send(response_str);
        }

// #ifndef DEBUG
// #define DEBUG
#ifdef BEBUG
        std::string httpreqstr;
        sock->Recv(&httpreqstr); // 浏览器给我发过来的是一个大的http字符串
        std::cout << httpreqstr;

        // 直接应答
        Httpresponse resp;
        resp._version = "HTTP/1.1";
        resp._code = 200;
        resp._desc = "OK";
        std::string filename = webroot + homepage;
        bool res = Util::ReadFileContent(filename, &(resp_text));
        std::string response_str = resp.Serialize();
        sock->Send(response_str);
#endif
    }
    void Start()
    {
        tsvrp->Start([this](std::shared_ptr<Socket> &sock, InetAddr &client)
                     { this->HandlerHttpRquest(sock, client); });
    }

private:
    std::unique_ptr<TcpServer> tsvrp;
};
