#include "mystdio.h"
#include <string.h>
#include <unistd.h>

int main()
{
    MyFile* filep=MyFopen("./log.txt", "w");
    if(!filep)
    {
        perror("fopen error");
        return 1;
    }
    int cnt=10;
    while(cnt--)
    {
        char* msg=(char*)"hello linux";
        MyFwrite(filep,msg,strlen(msg));
        MyFFlush(filep);
        printf("buffer: %s\n",filep->outbuffer);
        sleep(1);
    }
    MyFclose(filep);
    return 0;
}