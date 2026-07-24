
#include"comm.hpp"

int main()
{
  /*   //write
    int fd = open(FIFO_FILE, O_WRONLY);
if (fd < 0)
{
    std::cerr << "open fifo error" << std::endl;
    return 2;
}

// 写入操作
std::string message;
int cnt = 1;
pid_t id = getpid();
while(true)
{
    std::cout << "Please Enter…… ";
    std::getline(std::cin, message);
    message += (", message number: " + std::to_string(cnt++) + ", [" + std::to_string(id) + "]");
    write(fd, message.c_str(), message.size());
}

    close(fd); */

     FileOpen writerfile(PATH,FILENAME);
     writerfile.OpenForWrite();
     writerfile.Write();
     writerfile.Close();
    return 0;
}