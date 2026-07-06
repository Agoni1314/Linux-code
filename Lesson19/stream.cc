#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>

int main()
{
    // 库函数
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    const char *s = "hello fwrite\n";
    fwrite(s, strlen(s), 1, stdout);

    // 系统调用
    const char *ss = "hello write\n";
    write(1, ss, strlen(ss));

    //???
    fork();

    //向标准输出进行打印，stdout，cin->1
    //std::cout << "hello cout"<< std::endl; 
    //printf("hello prinf\n");

    ////向标准错误进行打印，stderr, cerr->2, 显示器
    //std::cerr << "hello cerr" <<std::endl;
    //fprintf(stderr, "hello stderr\n");
    return 0;
}
