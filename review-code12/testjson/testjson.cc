#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

// class person
// {

// };

int main()
{
    Json::Value root;
    root["name"] = "张三";
    root["sex"] = "男";
    root["age"] = 18;

    std::string s = root.toStyledString();
    std::cout << s << std::endl;

    return 0;
}
