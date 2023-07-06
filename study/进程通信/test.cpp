#include <iostream>
#include <cassert>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    int pipearry[2]={0};
    int s=pipe(pipearry);

    assert(s==0);
    (void)s;
    //因为12行在release中没有用
    //为了防止在运行的时候出现警告信息用了第13行的代码
#ifdef DEBUGE
    cout<<"pipearry[0]"<<pipearry[0]<<endl;
    cout<<"pipearry[1]"<<pipearry[1]<<endl;

#endif
    pid_t pid=fork();
    if(pid==0)//child,关闭写端——pipearry[1]
    {
        //接受消息
        close(pipearry[1]);
        char buffer[1000];
        while(true)
        {
            ssize_t  ret=read(pipearry[0],buffer,sizeof(buffer));
            if(ret>0){
                buffer[ret]=0;
                cout<<"接收成功：接收的数据为->"<<buffer<<endl;
            }
            else if(ret==0){
                cout<<"父进程退出，子进程马上退出"<<endl;
                break;
            }
            else{
                cout<<"异常错误"<<endl;
                break;
            }
        }
        exit(0);

    }
    //father，关闭读端——pipearry[0]
    //写信息
    close(pipearry[0]);
    char buffer[]="我是父进程";
    int count=0;
    while(true){
        ssize_t ret = write(pipearry[1],buffer,sizeof(buffer));
        cout<<buffer<<':'<<count++<< "子进程pid"<<pid<< "父进程pid"<<getpid()<<endl;
        sleep(1);
        if(count==5){
            cout<<"父进程退出"<<endl;
            break;
        }
    }
    close(pipearry[1]);
    pid_t n= waitpid(pid,nullptr,0);
    cout<<"pid:"<<pid<<"n:"<<n<<endl;

    return 0;
}