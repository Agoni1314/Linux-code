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
    return 0;
}