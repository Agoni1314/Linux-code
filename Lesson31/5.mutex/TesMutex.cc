// 操作共享变量会有问题的售票系统代码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int ticket = 1000;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *route(void *arg)
{
    char *id = (char *)arg;
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (ticket > 0) // 1. 判断
        {
            usleep(1000);                               // 模拟抢票花的时间
            printf("%s sells ticket:%d\n", id, ticket); // 2. 抢到了票
            ticket--;                                   // 3. 票数--
            pthread_mutex_unlock(&lock);
        }
        else
        {
            pthread_mutex_unlock(&lock);

            break;
        }
    }
    return nullptr;
}

int main(void)
{
    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, route, (void *)"thread 1");
    pthread_create(&t2, NULL, route, (void *)"thread 2");
    pthread_create(&t3, NULL, route, (void *)"thread 3");
    pthread_create(&t4, NULL, route, (void *)"thread 4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
}