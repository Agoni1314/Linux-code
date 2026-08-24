// 阻塞队列的实现
#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <pthread.h>

const int defaultcap = 5; // for test

template <typename T>
class BlockQueue
{
private:
    bool IsFull() { return _q.size() >= _cap; }
    bool IsEmpty() { return _q.empty(); }

public:
    BlockQueue(int cap = defaultcap)
        : _cap(cap), _csleep_num(0), _psleep_num(0)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_full_cond, nullptr);
        pthread_cond_init(&_empty_cond, nullptr);
    }
    void Equeue(const T &in)
    {
        pthread_mutex_lock(&_mutex);
        // 生产者调用
        while (IsFull())
        {
            // 应该让生产者线程进行等待
            // 重点1：pthread_cond_wait调用成功，挂起当前线程之前，要先自动释放锁！！
            // 重点2：当线程被唤醒的时候，默认就在临界区内唤醒！要从pthread_cond_wait
            // 成功返回，需要当前线程，重新申请_mutex锁！！！
            // 重点3：如果我被唤醒，但是申请锁失败了？？我就会在锁上阻塞等待！！！
            _psleep_num++;
            std::cout << "生产者，进入休眠了: _psleep_num" <<  _psleep_num << std::endl;
            // 问题1: pthread_cond_wait是函数吗？有没有可能失败？pthread_cond_wait立即返回了
            // 问题2：pthread_cond_wait可能会因为，条件其实不满足，pthread_cond_wait 伪唤醒
            pthread_cond_wait(&_full_cond, &_mutex);
            _psleep_num--;
        }
        // 100%确定：队列有空间
        _q.push(in);

        // 临时方案
        // v2
        if(_csleep_num>0)
        {
            pthread_cond_signal(&_empty_cond);
            std::cout << "唤醒消费者..." << std::endl;
        }

        // pthread_cond_signal(&_empty_cond); // 可以
        pthread_mutex_unlock(&_mutex); // TODO
        // pthread_cond_signal(&_empty_cond); // 可以
    }
    T Pop()
    {
        // 消费者调用
        pthread_mutex_lock(&_mutex);
        while (IsEmpty())
        {
            _csleep_num++;
            pthread_cond_wait(&_empty_cond, &_mutex);
            _csleep_num--;
        }
        T data = _q.front();
        _q.pop();

        if(_psleep_num > 0)
        {
            pthread_cond_signal(&_full_cond);
            std::cout << "唤醒消费者" << std::endl;
        }

        // pthread_cond_signal(&_full_cond);
        pthread_mutex_unlock(&_mutex);
        return data;
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_full_cond);
        pthread_cond_destroy(&_empty_cond);
    }

private:
    std::queue<T> _q; // 临界资源！！！
    int _cap;         // 容量大小

    pthread_mutex_t _mutex;
    pthread_cond_t _full_cond;
    pthread_cond_t _empty_cond;

    int _csleep_num; // 消费者休眠的个数
    int _psleep_num; // 生产者休眠的个数
};