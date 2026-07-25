#pragma once

#include <cstdio>
#include <cstdlib>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<unistd.h>
#include<string>
#include"Fifo.hpp"

const int gdefaultid =-1;
const int gsize=4096;
const std::string pathname=".";
const int projid=0x66;
const int gmode = 0666;
#define CREATER "creater"
#define USER "USER"


class Shm
{
public:
    Shm(const std::string &pathname,int projid,const std::string &usertype) 
    : _shmid(gdefaultid), 
    _size(gsize),
    _start_mem(nullptr),
    _usertype(usertype)
    {
         _key = ftok(pathname.c_str(), projid);
        if (_key < 0)
        {
            ERR_EXIT("ftok");
        }
            if(_usertype==CREATER)
            Create();
        else if(_usertype==USER)
            Get();
        else {}
            Attach();
    }
    ~Shm()
    {
        if(_usertype==CREATER)
        Destory();
    }
  void *VirtualAddr()
    {
        printf("VirtualAddr: %p\n",_start_mem);
        return _start_mem;
    }  
    int Size()
    {
        return _size;
    }
   
    
   
    
    private:
        // 创建的一定要是是一个全新的共享内存
        void CreateHelper(int flg)
        {
        /*  key_t k = ftok(pathname.c_str(), projid);
            if (k < 0)
            {
                ERR_EXIT("ftok");
            } */
        // printf("key: 0x%x\n", k);
            // _shmid = shmget(k, _size, IPC_CREAT | IPC_EXCL |gmode);
            printf("key: 0x%x\n", _key);
            _shmid = shmget(k, _size, flg);
            if (_shmid < 0)
            {
                ERR_EXIT("shmget");
            }
            printf("shmid: %d\n", _shmid);
        }
        void Create()
        {
            CreateHelper(IPC_CREAT | IPC_EXCL |gmode);
        }
        void Attach()
        {
            _start_mem = shmat(_shmid,nullptr,0);
        // if((int)_start_mem<0)
            if((long long)_start_mem<0)
            {
                ERR_EXIT("shmat");
            }
            printf("attach success\n");
        }
        void Get()
        {
            /*  key_t k = ftok(pathname.c_str(), projid);
            if (k < 0)
            {
                ERR_EXIT("ftok\n");
            }
            printf("key: 0x%x\n", k);
            _shmid = shmget(k, _size, IPC_CREAT);
            if(_shmid < 0)
            {
                ERR_EXIT("Get");
            }
            printf("shmid: %d", _shmid); */
            CreateHelper(IPC_CREAT);
        }
         void Destroy()
         {
                if(_shmid == gdefaultid) return ;
            int n =shmctl(_shmid,IPC_RMID,nullptr);
            if(n>0)
            {
                printf("shmctl detele shm: %d success!\n",_shmid);
            }
            else
            {
                ERR_EXIT("shmctl");
            }
         }
        
       
private:
    key_t _key;
    int _shmid;
    int _size;
    void* _start_mem;
    std::string _usertype;
};    