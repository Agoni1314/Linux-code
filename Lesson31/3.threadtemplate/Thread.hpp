#ifndef _THREAD_H_
#define _THREAD_H_

#include<iostream>
#include<string>
#include<pthread.h>
#include<cstring>
#include<functional>

namespace ThreadModlue
{
    template<typename T>
    class Thread
    {
        using func_t = std::function<void(T)>;
        private:
            void EnableDetach()
            {
                std::cout<<"线程已经分离"<<std::endl;
                _isdetach=true;
            }
        //bug
        static uint32_t number=1;
        
        public:
            Thread(func_t func,T data)
            :_tid(0)
            ,_isdetach(false)
            ,isruning(false)
            ,res(nullptr)
            ,_func(func)
            ,_data(data)
            {
                _name="thread-"+std::to_string(number++);
            }
            void Detach()
            {
                if(_isdetach)
                return;
                if(_istuning)
                pthread_detach(_tid);
                EnableDetach();
            }
            void EnableRuning()
            {
                isruning=true;
            }
            static void *Routine(void *args)//属于类内部的成员函数，默认包含this，要加static,就没有this了
            {
                Thread<T>*self=static_cast<Thread<T>*>(args);
                self->EnableDetach();
                if(self->_isdetach)
                {
                    self->Detach();
                }
                self->_func(self->_data);//回调
                return nullptr;
            }
            void Start()
            {
                int n=pthread_create(&_tid,nullptr,Routine,this)
                if(n != 0)
                {
                    std::cerr<<"creaye thread error:"<<strerror(n)<<std::endl;
                     return false;
                }
                else
                {
                    std::cout<<_name<<"create success"<<std::endl;
                }
            }
            ~Thread(){}
            void Stop()
            {
                if(_isruning)
                {
                    int n=pthread_cancel(_tid);
                    if(n!=0)
                    {
                          std::cerr<<"creaye thread error:"<<strerror(n)<<std::endl;
                          return false;
                    }
                    else
                    {
                        _isruning=false;
                        stdd::cout<<_name<<"stop"<<std::endl;
                        return true;
                    }
                    
                }
                return false;
            }
            void Join()
            {
                if(_isdetach)
                {
                    std::cout<<"线程分离,不能join"<<std::endl;
                      return;
                }
              
                int n=pthread_Join(_tid,&res);
                if(n!=0)
                {
                    std::cerr<<"creaye thread error:"<<strerror(n)<<std::endl;
                    return false;
                }
                else
                {
                    std::cout<<"join success"<<std::endl;
                    return true;
                }
            }
        private:
        pthread_t _tid;
        std::string _name;
        bool _isdetach;
        bool _isruning;
        void *res;
        func_t _func;
        T _data;
    }
};

#endif