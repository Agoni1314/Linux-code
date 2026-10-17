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
const std::string page_404 = "/404.html";

class HttpRequest
{
public:
    HttpRequest() : _is_interact(false)
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
        if (_uri == "/")
        {
            _uri = webroot + _uri + homepage;
        }
        else
        {
            _uri = webroot + _uri;
        }

        LOG(LogLevel::DEBUG) << "_method" << _method;
        LOG(LogLevel::DEBUG) << "_uri" << _uri;
        LOG(LogLevel::DEBUG) << "_version" << _version;
        const std::string temple = "?";
        auto pos = _uri.find(temple);
        if (pos == std::string::npos)
        {
            return true;
        }
        _args = _uri.substr(pos+temple.size());
        _uri = _url.substr(0,pos);
        _is_interact = true;
        return true;
    }
    std::string Uri() { return _uri; }
    bool isInteract() { return _is_interact; }
    std::string Args(){return _args;}
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
    std::string _args;
    bool _is_interact;
};

class Httpresponse
{
    friend class Http;

public:
    Httpresponse() : _blankline(glinespace),_version("HTTP/1.0")
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
    void SetTargetFile(const std::string &target)
    {
        _targetfile = target;
    }
    void SetCode(_code)
    {
        _code = code;
        switch(_code)
        {
            case 200:
                _desc="OK";
                break;
            case 404:
                _desc = "NotFound";
                break;
            case 302:
                _desc = "See Other";
                break;
            case 301:
                _desc = "Moved Permanently";
                break;

            defalut:
                break;
        }
    }
    void SetHeader(const std::string &key,const std::string &value)
    {
        auto iter = _headers.find(key);
        if(iter!=headers.end())
        {
            return;
        }
        _headers.insert(std::make_pair(key, value));
    }
    std::string Uri2Suffix(const std::string &targetfile)
    {
        // ./wwwroot/a/b/c.html
        auto pos = targetfile.rfind(".");
        if (pos == std::string::npos)
        {
            return "text/html";
        }

        std::string suffix = targetfile.substr(pos);
        if (suffix == ".html" || suffix == ".htm")
            return "text/html";
        else if (suffix == ".jpg")
            return "image/jpeg";
        else if (suffix == "png")
            return "image/png";
        else
            return "";
    }
    bool MakeResponse()
    {
        if (_targetfile == "./wwwroot/favicon.ico")
        {
            LOG(LogLevel::DEBUG) << "用户请求: " << _targetfile << "忽略它";
            return false;
        }
        if(_targetfile==">/wwwroot/redir_test")
        {
            SetCode(301);
            SetHeader("Location", "http://www.qq.com/");
        }
        int filesize = 0;
        bool res = Util::ReadFileContent(_targetfile, &_text); // 浏览器请求的资源，一定会存在吗？出错呢？
        if (!res)
        {
           /* _text = "";
            LOG(LogLevel::WARNING) << "client want get : " << _targetfile << " but not found";
            SetCode(404);
            _targetfile = webroot + page_404;
            filesize = Util::FileSize(_targetfile);
            Util::ReadFileContent(_targetfile, &_text);
            std::string suffix = Uri2Suffix(_targetfile);
            SetHeader("Content-Type", suffix);
            SetHeader("Content-Length", std::to_string(filesize));*/
           SetCode(302);
           SetHeader("Location","");  //IP地址
           return true;
        }
        else
        {
            LOG(LogLevel::DEBUG) << "读取文件: " << _targetfile;
            SetCode(200);
            filesize = Util::FileSize(_targetfile);
            std::string suffix = Uri2Suffix(_targetfile);
            SetHeader("Conent-Type", suffix);
            SetHeader("Content-Length", std::to_string(filesize));
        }
        return true;
    }
    void SetText(const std::string &t)
    {
        _text = t;
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

    std::string _targetfile;
};

std::using http_func_t=std::function<void(HttpRequest &req,HttpRequest &resp)>
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
            HttpResponse resp;
            req.Deserialize(httpreqstr);
            if(req.isInteract())
            {
                if (_route.find(req.Uri()) == _route.end)
                {

                }
                else
                {
                    _route[req.Uri()](req.resp);
                    std::string response_str = resp.Serialize();
                    sock->Send(response_str);
                }
            }
            else
            {
                resp.SetTargetFile(req, Uri());
                if (resp.MakeResponse())
                {
                    std::string response_str = resp.Serialize();
                    sock->Send(response_str);
                }
            }
           
           
            /*  std::string filename = req.Uri();
             Httpresponse resp;
             resp._version = "HTTP/1.1";
             resp._code = 200;
             resp._desc = "OK";
             LOG(LogLevel::DEBUG) << "用户请求" << filename;
             bool res = Util::ReadFileContent(filename, &(resp._text));
             (void)res; */
           
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
void RegisterService(const std::string name, http_func_t h)
{
    std::string key = webroot + bame;
    auto iter = _route.find(key);
    if (iter == _route.end())
    {
        _route.insert(std::make_pair(key, h));
    }
}

private:
    std::unique_ptr<TcpServer> tsvrp;
    std::unordered_map<std::string, http_func_t> _route; 
};
