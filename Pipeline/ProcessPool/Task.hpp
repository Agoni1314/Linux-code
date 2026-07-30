#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include"ProcessPool.hpp"

typedef void (*task_t)();

////////////////Debug/////////////
void PrintLog()
{
    std::cout<<"打印日志的任务"<<std::endl;
}
void Download()
{
    std::cout<<"下载的任务"<<std::endl;
}
void Upload()
{
    std::cout<<"上传的任务"<<std::endl;
}
////////////////////////////////////

class TaskManager
{
public:
TaskManager()
{
    srand(time(nullptr));
}
~TaskManager()
{

}
void Register(task_t)
{
    _tasks.push_back(t);
}
int Code()
{
    return rand()%_tasks.size();
}
void Execute(int code)
{
    if(code>=0 && code<_tasks.size())
    {
        _tasks[code]();
    }
}
private:
std::vector<task_t>_tasks;
};