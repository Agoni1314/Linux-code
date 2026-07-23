#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

void ChildWrite(int wfd)
{
   char c=0;
    int cnt =0;
    while(true)
    {
        
        write(wfd,&c,1);
        printf("child:%d\n",cnt++);
    }
}

 void FatherRead(int rfd)
 {
     char buffer[1024];
     while(true)
     {
        sleep(100);
        buffer[0]=0;
        ssize_t n = read(rfd,buffer,sizeof(buffer)-1);//因为没有把\0写进去，就要预留\0的位置
        if(n>0)
        {
            buffer[n]=0;
            std::cout<<"child say:"<<buffer<<std::endl;
        }
         else if(n==0)
        {
            std::cout<<"n:"<<n<<std::endl;
            std::cout<<"child退出， 我也退出";
            break;
        }
        else
        {
            break;
        }  
        break;  
     }
 }

//读关闭,写继续,发送9号信号
/* void ChildWrite(int wfd)
{
    char buffer[1024];
    int cnt =0;
    while(true)
    {
        snprintf(buffer,sizeof(buffer),"i am child,pid:%d,cnt:%d",getpid(),cnt++);
        write(wfd,buffer,strlen(buffer));//向文件写字符串不用把\0写进去，\0是c的标准，和文件无关
        printf("child:%d\n",cnt);
       sleep(2);
    }
}

 void FatherRead(int rfd)
 {
     char buffer[1024];
     while(true)
     {
        buffer[0]=0;
        ssize_t n = read(rfd,buffer,sizeof(buffer)-1);//因为没有把\0写进去，就要预留\0的位置
        if(n>0)
        {
            buffer[n]=0;
            std::cout<<"child say:"<<buffer<<std::endl;
        }
         else if(n==0)
        {
            std::cout<<"n:"<<n<<std::endl;
            std::cout<<"child退出， 我也退出";
            break;
        }
        else
        {
            break;
        }  
        break;  
     }
 } */


/* //写完之后就关掉
void ChildWrite(int wfd)
{
    char buffer[1024];
    int cnt =0;
    while(true)
    {
        snprintf(buffer,sizeof(buffer),"i am child,pid:%d,cnt:%d",getpid(),cnt++);
        write(wfd,buffer,strlen(buffer));//向文件写字符串不用把\0写进去，\0是c的标准，和文件无关
       printf("child:%d\n",cnt);
       sleep(2);
       break;
    }
}

 void FatherRead(int rfd)
 {
     char buffer[1024];
     while(true)
     {
        buffer[0]=0;
        ssize_t n = read(rfd,buffer,sizeof(buffer)-1);//因为没有把\0写进去，就要预留\0的位置
        if(n>0)
        {
            buffer[n]=0;
            std::cout<<"child say:"<<buffer<<std::endl;
        }
        else if(n==0)
        {
            std::cout<<"n:"<<n<<std::endl;
            std::cout<<"child退出， 我也退出";
            break
        }
        else
        {
            break;
        }    
     }
 }
 */
/* //写的慢
void ChildWrite(int wfd)
{
    char buffer[1024];
    int cnt =0;
    while(true)
    {
        snprintf(buffer,sizeof(buffer),"i am child,pid:%d,cnt:%d",getpid(),cnt++);
        write(wfd,buffer,strlen(buffer));//向文件写字符串不用把\0写进去，\0是c的标准，和文件无关
       printf("child:%d\n",cnt);
       sleep(1);
    }
}
//读的快
 void FatherRead(int rfd)
 {
     char buffer[1024];
     while(true)
     {
       
        buffer[0]=0;
        ssize_t n = read(rfd,buffer,sizeof(buffer)-1);//因为没有把\0写进去，就要预留\0的位置
        if(n>0)
        {
            buffer[n]=0;
            std::cout<<"child say:"<<buffer<<std::endl;
        }
        
     }
 } */

/* //写的快
void ChildWrite(int wfd)
{
    char buffer[1024];
    int cnt =0;
    while(true)
    {
        snprintf(buffer,sizeof(buffer),"i am child,pid:%d,cnt:%d",getpid(),cnt++);
        write(wfd,buffer,strlen(buffer));//向文件写字符串不用把\0写进去，\0是c的标准，和文件无关
       printf("child:%d\n",cnt);
    }
}
//读的慢,
 void FatherRead(int rfd)
 {
     char buffer[1024];
     while(true)
     {
        sleep(5);
        buffer[0]=0;
        ssize_t n = read(rfd,buffer,sizeof(buffer)-1);//因为没有把\0写进去，就要预留\0的位置
        if(n>0)
        {
            buffer[n]=0;
            std::cout<<"child say:"<<buffer<<std::endl;
        }
        sleep(2);
     }
 } */

int main()
{
    //创建管道
    int fds[2]={0};  //0读 1写
    int ret =pipe(fds);
    if(ret<0)
    {
        std::cerr<<"Pipe error"<<std::endl;
        return 1;
    }
    std::cout << "fds[0]: " << fds[0] << std::endl;
    std::cout << "fds[1]: " << fds[1] << std::endl;


    //创建子进程
pid_t id=fork();
if(id==0)
{
    //关闭读端，形成通信信道
    close(fds[0]);
    ChildWrite(fds[1]);
    close(fds[1]);
    exit(0);
}


    //关闭写端，形成通信信道
    close(fds[1]);
    FatherRead(fds[0]);
    waitpid(id,nullptr,0);
    close(fds[0]);

    int status=0;
    int ret=waitpid(id,&status,0);//获取子进程的退出信息
    if(ret>0)
    {
        printf("exit code: %d,exit signal:%d\n",(status>>8)&0xFF,status&0x7F);
        sleep(5);
    }
    return 0;
}