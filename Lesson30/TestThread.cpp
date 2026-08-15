#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <cstring>

// 创建多线程

// const int num = 10;

// void *routine(void *args)
// {
//     sleep(1);
//     std::string name = static_cast<const char *>(args);
//     delete (char*)args;

//     int cnt = 5;
//     while (cnt--)
//     {
//         std::cout << "new线程名字: " << name << std::endl;
//         sleep(1);
//     }
//     return nullptr;
// }

// int main()
// {
//     // char id[64];
//     std::vector<pthread_t> tids;
//     for (int i = 0; i < num; i++)
//     {
//         pthread_t tid;
//         // bug??
//         char *id = new char[64];
//         snprintf(id, 64, "thread-%d", i);
//         int n = pthread_create(&tid, nullptr, routine, id);
//         if (n == 0)
//             tids.push_back(tid);
//         else
//             continue;
//     }

//     for (int i = 0; i < num; i++)
//     {
//         // 一个一个的等待
//         int n = pthread_join(tids[i], nullptr);
//         if (n == 0)
//         {
//             std::cout << "等待新线程成功" << std::endl;
//         }
//     }

//     return 0;
// }

// // 1. main函数结束，代表主线程结束，一般也代表进程结束
// // 2. 新线程对应的入口函数，运行结束，代表当前线程运行结束

// // 3. 一个问题：给线程传递的参数和返回值，可以是任意类型(包括对象)

// class Task
// {
// public:
//     Task(int a, int b) : _a(a), _b(b) {}
//     int Execute()
//     {
//         return _a + _b;
//     }
//     ~Task() {}

// private:
//     int _a;
//     int _b;
// };

// class Result
// {
// public:
//     Result(int result) : _result(result)
//     {
//     }
//     int GetResult() { return _result; }
//     ~Result() {}

// private:
//     int _result;
// };

// // 线程终止的问题
// // 1. 线程的入口函数，进行return就是线程终止
// // 注意: 线程不能用exit()终止，因为exit是终止进程的！！！！！
// // 2. pthread_exit();
// // 3. 线程如果被取消，退出结果是-1【PTHREAD_CANCELED】
// // void* p : 开辟空间的
// void *routine(void *args)
// {
//     pthread_detach(pthread_self());
//     std::cout << "新线程被分离" << std::endl;
//     int cnt = 5;
//     while (cnt--)
//     {
//         std::cout << "new线程名字: " << std::endl;
//         sleep(1);
//     }

//     return nullptr;
//     // Task *t = static_cast<Task*>(args);
//     // sleep(100);
//     // Result *res = new Result(t->Execute());
//     // sleep(1);
//     // // return res;
//     // // exit(13);
//     // pthread_exit(res);
//     // std::cout << "haha, 新线程不应该看到这里" << std::endl;
// }

// // 如果主线程不想再关心新线程，而是当新线程结束的时候，让他自己释放？？
// // 设置新线程为分离状态
// // 技术层面:  线程默认是需要被等待的，joinable。如果不想让主线程等待新线程
// // 想让新线程结束之后，自己退出，设置为分离状态(!joinable or detach)  // TODO
// // 理解层面：线程分离，主分离新，新把自己分离。
// // 分离的线程，依旧在进程的地址空间中，进程的所有资源，被分离的线程，依旧可以访问，可以操作。
// // 主不等待新线程。
// // 分离操作
// // 如果线程被设置为分离状态，不需要进行join，join会失败！！
// int main()
// {
//     pthread_t tid;
//     // Task *t = new Task(10, 20);
//     pthread_create(&tid, nullptr, routine, (void *)"thread-1");

//     // pthread_detach(tid);
//     // std::cout << "新线程被分离" << std::endl;

//     int cnt = 5;
//     while (cnt--)
//     {
//         std::cout << "main线程名字: " << std::endl;
//         sleep(1);
//     }

//     int n = pthread_join(tid, nullptr);
//     if (n != 0)
//     {
//         std::cout << "pthread_join error: " << strerror(n) << std::endl;
//     }
//     else
//     {
//         std::cout << "pthread_join success: " << strerror(n) << std::endl;
//     }

//     // sleep(3);
//     // pthread_cancel(tid);
//     // std::cout << "新线程被取消" << std::endl;

//     // void *ret = nullptr;
//     // // 默认线程无异常
//     // pthread_join(tid, &ret); // pthread_join: 拿到的返回值，就是线程退出设定的返回值
//     // std::cout << "新线程结束, 运行结果: " << (long long)ret << std::endl;

//     // Result* ret = nullptr;
//     // pthread_join(tid, (void**)&ret);
//     // int n = ret->GetResult();
//     // std::cout << "新线程结束, 运行结果: " << n << std::endl;

//     // delete t;
//     // delete ret;
//     return 0;
// }