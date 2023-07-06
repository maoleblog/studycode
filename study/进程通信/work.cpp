// #include <iostream>
// #include <unistd.h>
// #include <cstring>
// using namespace std;


// int main()
// {
//     int pipearr[2]={0};
//     int s=pipe(pipearr);
//     if(s<0){
//         cout<<"创建管道失败"<<endl;
//         exit(-1);
//     }
//     pid_t pid=fork();
//     if(pid==0){
//         //子进程读
//         close(pipearr[1]);
//         char buffer[1000];
//         while (true)
//         {
//             ssize_t ret = read(pipearr[0], buffer, 4);
//             if (ret == 0)
//             {
//                 // 读完
//                 cout << "子进程读取完毕" << endl;
//                 exit(0);
//             }
//             else if(ret>0){
//                 cout<<buffer;
//             }
//         }
        
//     }
//     //父进程写 i am father
//     char data[]="i am father";
//     close(pipearr[0]);
//     ssize_t ret= write(pipearr[1],data,sizeof(data));
//     if(ret<0){
//         cout<<"写入错误"<<endl;
//     }
//     return 0;
// }
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    int ret = open("test.txt", O_RDONLY);
    cout << "test2:" << ret << endl;
    sleep(100000);
    return 0;
}