///#include <stdio.h>
///#include <unistd.h>
///#include <stdlib.h>
///
///int g_unval;
///int g_val = 100;
///
///int main(int argc, char *argv[], char *env[])
///{
///    const char *str = "helloworld";
///    printf("code addr: %p\n", main);
///    printf("init global addr: %p\n", &g_val);
///    printf("uninit global addr: %p\n", &g_unval);
///
///    static int test = 10;
///    char *heap_mem = (char*)malloc(10);
///    char *heap_mem1 = (char*)malloc(10);
///    char *heap_mem2 = (char*)malloc(10);
///    char *heap_mem3 = (char*)malloc(10);
///    printf("heap addr: %p\n", heap_mem); //heap_mem(0), &heap_mem(1)
///    printf("heap addr: %p\n", heap_mem1); //heap_mem(0), &heap_mem(1)
///    printf("heap addr: %p\n", heap_mem2); //heap_mem(0), &heap_mem(1)
///    printf("heap addr: %p\n", heap_mem3); //heap_mem(0), &heap_mem(1)
///
///    printf("test static addr: %p\n", &test); //heap_mem(0), &heap_mem(1)
///    printf("stack addr: %p\n", &heap_mem); //heap_mem(0), &heap_mem(1)
///    printf("stack addr: %p\n", &heap_mem1); //heap_mem(0), &heap_mem(1)
///    printf("stack addr: %p\n", &heap_mem2); //heap_mem(0), &heap_mem(1)
///    printf("stack addr: %p\n", &heap_mem3); //heap_mem(0), &heap_mem(1)
///
///    printf("read only string addr: %p\n", str);
///    for(int i = 0 ;i < argc; i++)
///    {
///        printf("argv[%d]: %p\n", i, argv[i]);
///    }
///    for(int i = 0; env[i]; i++)
///    {
///        printf("env[%d]: %p\n", i, env[i]);
///    }
///
///    return 0;
///}
///
///
///
///
///
/////#include <stdio.h>
/////#include <unistd.h>
/////#include <stdlib.h>
/////#include <string.h>
/////
/////extern char **environ;
/////
/////// main有参数吗?有
/////// 最多可以有几个? 3个
/////// 是父进程传递给我们的
/////int main(int argc, char *argv[])
/////{
/////    (void)argc;
/////    (void)argv;
/////    if(fork() == 0)
/////    {
/////       for(int i = 0; environ[i]; i++)
/////       {
/////           printf("environ[%d]-> %s\n", i, environ[i]);
/////       }
/////    }
/////    sleep(3);
/////
/////  //  const char *who = getenv("USER");
/////  //  if(who == NULL) return 1;
/////
/////  //  if(strcmp(who, "whb")==0)
/////  //  {
/////  //      printf("这是程序的正常执行逻辑\n");
/////  //  }
/////  //  else
/////  //  {
/////  //      printf("Only Whb!!\n");
/////  //  }
/////    
/////    
/////    
/////    
/////    //char *value = getenv("PATH");
/////    //if(value==NULL)return 1;
/////    //printf("PATH->%s\n", value);
/////   // for(int i = 0; env[i]; i++)
/////   // {
/////   //     printf("env[%d]-> %s\n", i, env[i]);
/////   // }
/////
/////
///////    if(argc != 2)
///////    {
///////        printf("Usage: %s [-a|-b|-c]\n", argv[0]);
///////        return 1;
///////    }
///////
///////    const char *arg = argv[1];
///////
///////    if(strcmp(arg, "-a")==0)
///////        printf("这是功能1\n");
///////    else if(strcmp(arg, "-b")==0)
///////        printf("这是功能2\n");
///////    else if(strcmp(arg, "-c")==0)
///////        printf("这是功能3\n");
///////    else
///////        printf("Usage: %s [-a|-b|-c]\n", argv[0]);
///////
/////
/////
/////
/////    //for(int i = 0; i < argc; i++)
/////    //{
/////    //    printf("argv[%d]: %s\n", i, argv[i]);
/////    //}
/////    return 0;
/////}
