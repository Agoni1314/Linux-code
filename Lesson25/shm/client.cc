#include "Shm.hpp"
#include "Fifo.hpp"

int main()
{
    FileOper writerfile(PATH, FILENAME);
    writerfile.OpenForWrite();

    Shm shm(pathname, projid, USER);
    char *mem = (char *)shm.VirtualAddr();
    // 我们读写共享内存，有没有使用系统调用？？没有！！
    int index = 0;
    for (char c = 'A'; c <= 'B'; c++, index += 2)
    {
        // 才是向共享内存写入
        sleep(1);
        mem[index] = c;
        mem[index + 1] = c;
        sleep(1);
        mem[index+2] = 0;

        writerfile.Wakeup();
    }

    writerfile.Close();
    return 0;
}