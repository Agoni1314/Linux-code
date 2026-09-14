#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

int main()
{
    Json::value root;
    root["name"]="张三";
    root["sex"]="男"
    root["age"]=18;

    Json::StreamWriterBuilder sbuilder;
    std::unique_ptr<Json::StreamWrite>writer(sbuilder.newStreamWriter());
    std::stringstream ss;
    writer->writer(root,&ss);
    std::string s=ss.str();
    std::cout<<s<<std::endl;
    /*Json::StyledWriter Writer;
    std::string s =Write.write(root);
    std::cout << s << std::endl;*/
    return 0;
}