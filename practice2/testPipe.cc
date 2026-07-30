 #include<iostream>
#include <unistd.h>
#include<cstring>
#include<cstdio>
#include<sys/types.h>
#include <sys/wait.h>

  void ChildWrite(int wfd)
   {
        char buffer[1024];
        int cnt=0;
        char c=0;
        while(true)
        {
            //snprintf(buffer,sizeof(buffer),"i am child,pid:%d,cnt:%d",getpid(),cnt++);
            //write(wfd,buffer,strlen(buffer));//写入实际的字节数
           /*  sleep(1);
            if(cnt==5)
            exit(1); */
            write(wfd,&c,1);
            printf("child: %d\n", cnt++);
        }
   }

    void FatherRead(int rds)
    {
        char buffer[1024];
        while(true)
        {
            sleep(10);
            buffer[0]=0;
            ssize_t n=read(rds,buffer,sizeof(buffer)-1);//读取最大的容量
            if(n>0)
            {
                buffer[n]=0;
                std::cout<<"child say:"<<buffer<<std::endl;
            }
            else if(n == 0)
            {
                std::cout << "n : " << n << std::endl;
                std::cout << "child 退出，我也退出";
                break;
            }
            else
            {
                break;
            }
            break;
        }
    }

int main()
{
    int fds[2]={0};
    int n =pipe(fds);
    if(n<0)
    {
        std::cerr<<"Pipeline failed!"<<std::endl;
        return 1;
    }
     std::cout << "fds[0]: " << fds[0] << std::endl;
    std::cout << "fds[1]: " << fds[1] << std::endl; 

    pid_t id=fork();
    if(id==0)
    {
        //child
        //关闭读端
        close(fds[0]);
        ChildWrite(fds[1]);
        close(fds[1]);
    }
        //father
        //关闭写端
        close(fds[1]);
        FatherRead(fds[0]);
        //waitpid(id,nullptr,0);
        close(fds[0]);

        int status=0;
        int ret =waitpid(id,&status,0);
        if(ret>0)
        {
             printf("exit code: %d, exit signal: %d\n", (status>>8)&0xFF, status&0x7F);
            sleep(5);
        }
            return 0;
} 



