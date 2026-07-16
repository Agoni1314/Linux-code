#include "Shm.hpp"
#include "Fifo.hpp"

int main()
{
    Shm shm(pathname, projid, CREATER);
    // sleep(5);
    shm.Attr();


    NamedFifo fifo(PATH, FILENAME);

    // 文件操作了
    FileOper readerfile(PATH, FILENAME);
    readerfile.OpenForRead();

    char *mem = (char *)shm.VirtualAddr();
    // 我们读写共享内存，有没有使用系统调用？？也没有！！
    while (true)
    {
        if (readerfile.Wait())
        {
            printf("%s\n", mem);
        }
        else
            break;
    }

    readerfile.Close();
    std::cout << "server end normal!" << std::endl; // server段的析构函数没有被成功调用！
    return 0;
}