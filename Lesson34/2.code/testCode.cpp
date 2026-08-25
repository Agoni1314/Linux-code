#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <pthread.h>

#define NUM 5
int cnt = 1000;

pthread_mutex_t glock = PTHREAD_MUTEX_INITIALIZER; // 定义锁, 为什么一定要有锁？？
pthread_cond_t gcond = PTHREAD_COND_INITIALIZER;   // 定义条件变量

// 等待是需要等，什么条件才会等呢？票数为0，等待之前，就要对资源的数量进行判定。
// 判定本身就是访问临界资源！，判断一定是在临界区内部的.
// 判定结果，也一定在临界资源内部。所以，条件不满足要休眠，一定是在临界区内休眠的!
// 证明一件事情：条件变量，可以允许线程等待
//                       可以允许一个线程唤醒在cond等待的其他线程， 实现同步过程
void *threadrun(void *args)
{
    std::string name = static_cast<const char *>(args);
    while (true)
    {
        pthread_mutex_lock(&glock);
        // 直接让对用的线程进行等待?? 临界资源不满足导致我们等待的!
        pthread_cond_wait(&gcond, &glock); // glock在pthread_cond_wait之前，会被自动释放掉
        std::cout << name << " 计算: " << cnt << std::endl;
        cnt++;
        pthread_mutex_unlock(&glock);
    }
}

int main()
{
    std::vector<pthread_t> threads;
    for (int i = 0; i < NUM; i++)
    {
        pthread_t tid;
        char *name = new char[64];
        snprintf(name, 64, "thread-%d", i);
        int n = pthread_create(&tid, nullptr, threadrun, name);
        if (n != 0)
            continue;
        threads.push_back(tid);
        sleep(1);
    }

    sleep(3);

    // 每隔1s唤醒一个线程
    while(true)
    {
        std::cout << "唤醒所有线程... " << std::endl;
        pthread_cond_broadcast(&gcond);
        
        // std::cout << "唤醒一个线程... " << std::endl;
        // pthread_cond_signal(&gcond);
        sleep(1);
    }

    for (auto &id : threads)
    {
        int m = pthread_join(id, nullptr);
        (void)m;
    }

    return 0;
}