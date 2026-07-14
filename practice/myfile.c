#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
//int main()
//{
//  umask(0);
// // int  fd=open("log.txt",O_TRUNC|O_CREAT|O_WRONLY,0666);
// // int  fd=open("log.txt",O_APPEND|O_CREAT|O_WRONLY,0666);
//  if(fd<0)
//  {
//    perror("open failed");
//    return 1;
//  }
// // const char *msg="cpp\n";
//  int cnt=5;
//  int ret=12345;
//  while(cnt)
//  {
//    //当作字符来写
//   // write(fd,msg,strlen(msg));
//    
//   char buffer[16];
//   snprintf(buffer,sizeof(buffer),"%d",ret);
//    write(fd,buffer,strlen(buffer));
//    cnt--;
//  }
//  close(fd);
//  return 0;
//}


//int main()
//{
//  umask(0);
//  int fd=open("log.txt",O_RDONLY);
//  if(fd<0)
//  {
//    printf("open failed");
//    return 1;
//  }
//  printf("fd:%d\n",fd);
//  while(1)
//  {
//    char buffer[64];
//    //文件中读取的字节数作为返回值
//    int n=read(fd,buffer,sizeof(buffer)-1);
//    if(n>0)
//    {
//      buffer[n]=0;
//      printf("%s\n",buffer);
//    }
//    else if(n==0)
//      break;
//  }
//  return 0;
//}




//int main()
//{
//  umask(0);
//  printf("stdin:%d\n",stdin->_fileno);
//  printf("stdout:%d\n",stdout->_fileno);
//  printf("stderr:%d\n",stderr->_fileno);
//
//  int fd1=open("log1.txt",O_CREAT|O_TRUNC|O_WRONLY,0666); 
//  int fd2=open("log2.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  int fd3=open("log3.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  int fd4=open("log4.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
//
//  printf("fd1:%d\n",fd1);
//  printf("fd2:%d\n",fd2);
//  printf("fd3:%d\n",fd3);
//  printf("fd4:%d\n",fd4);
//
//  close(fd1);
//  close(fd2);
//  close(fd3);
//  close(fd4);
//  return 0;
//}


//int main()
//{
//  close(1);
//  int fd=open("myfile.txt",O_CREAT|O_WRONLY,0666);
//    if(fd<0)
//    {
//      perror("error");
//      return 1;
//    }
//  printf("fd:%d\n",fd);
//  fflush(stdout);
//  close(fd);
//  return 0;
//}


//int main()
//{
//  int fd = open("./log", O_CREAT | O_RDWR);
//  if (fd < 0) {
//    perror("open");
//    return 1;
//}
//  close(1);
//  dup2(fd, 1);
//  for (;;)
//  {
//    char buf[1024] = {0};
//    ssize_t read_size = read(0, buf, sizeof(buf) - 1);
//    if (read_size < 0)
//    {
//        perror("read");
//        break;
//    }
//      printf("%s", buf);
//      fflush(stdout);
//  }
//    return 0;
//}



//int main()
//{
//  //close(0);
// // close(2);
//   close(1);
//  int fd5=open("log5.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
// printf("fd:%d",fd5);
//  return 0;
//}


//int main()
//{
//  int fd6 = open("log6.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
//if(fd6 < 0) exit(1);
//
//dup2(fd6, 1);
//close(fd6);
//
//// 默认向显示器输出
//printf("fd6: %d\n", fd6);
//printf("hello bit\n");
//printf("hello bit\n");
//printf("hello bit\n");
//fprintf(stdout, "hello stdout\n");
//fprintf(stdout, "hello stdout\n");
//fprintf(stdout, "hello stdout\n");
//fprintf(stdout, "hello stdout\n");
//  return 0;
//}

int main()
{
  int fd7 = open("log7.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
if(fd7 < 0) exit(1);

dup2(fd7, 1);
//close(fd);

// 默认向显示器输出
printf("fd7: %d\n", fd7);
printf("hello bit\n");
printf("hello bit\n");
printf("hello bit\n");
fprintf(stdout, "hello stdout\n");
fprintf(stdout, "hello stdout\n");
fprintf(stdout, "hello stdout\n");
fprintf(stdout, "hello stdout\n");

const char *msg = "hello world\n";
write(fd7, msg, strlen(msg));
  return 0;
}



























