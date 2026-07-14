
#include <iostream>
#include<unistd.h>
int main()
{
    std::cout << "hello C++, my pid is:"<<getpid() << std::endl;
    return 0;
}
