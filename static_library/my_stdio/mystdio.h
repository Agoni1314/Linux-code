#pragma once
#include<stdio.h>

#define Max 1024
#define NONE_FLUSH (1<<0)//通过位运算刷新
#define LINE_FLUSH (1<<1)
#define FULL_FLUSH (1<<2)
typedef struct IO_FILE
{
    int fileno;
    int  flag;
    char outbuffer[Max];
    int bufferlen;
    int flush_method;
}MyFile;

MyFile *MyFopen(const char *path, const char *mode);
void MyFclose(MyFile *);//在头文件进行函数声明时，编译器只需要知道参数的数据类型即可
int MyFwrite(MyFile *, void *str, int len);
void MyFFlush(MyFile *);
