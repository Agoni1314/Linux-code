#include "mystdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static MyFile *BuyFile(int fd, int flag)
{
    MyFile *f=(MyFile*)malloc(sizeof(MyFile));
    if(f==0) return NULL;;
    f->fileno=fd;
    f->flag=flag;
    f->bufferlen=0;
    f->flush_method=LINE_FLUSH;
     memset(f->outbuffer, 0, sizeof(f->outbuffer));
     return f;
}
MyFile *MyFopen(const char *path, const char *mode)
{
    int fd=-1;
    int flag=0;
    if(strcmp(mode,"w")==0)
    {
        flag=O_CREAT | O_WRONLY | O_TRUNC;
        fd=open(path,flag,0666);
    }
    else if(strcmp(mode,"a")==0)
    {
        flag=O_CREAT | O_WRONLY | O_APPEND;
        fd=open(path,flag,0666);
    }
    else if(strcmp(mode,"r")==0)
    {
        flag=O_RDWR;
        fd=open(path,flag);
    }
    else
    {
        //
    }
    if(fd<0) return NULL;
    return BuyFile(fd,flag);
}
void MyFclose(MyFile *file)
{
    if(file->fileno<0) return ;
    MyFFlush(file);
    close(file->fileno);
    free(file);
}
int MyFwrite(MyFile *file, void *str, int len)
{
    memcpy(file->bufferlen+file->outbuffer,str,len);//ptr 是用户调用 MyFwrite 时传进来的数据指针拷贝到文件流开辟的用户态缓冲区数组
    file->bufferlen+=len;
    if((file->flush_method & LINE_FLUSH) && file->outbuffer[file->bufferlen-1]=='\n')
    {
        MyFFlush(file);
    }
    return 0;
}
void MyFFlush(MyFile *file)
{
    if(file->bufferlen <= 0) return;
    int ret=write(file->fileno,file->outbuffer,file->bufferlen);
    (void) ret;
    fsync(file->fileno);
    file->bufferlen=0;
}