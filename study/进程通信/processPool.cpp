#include <iostream>
#include <unistd.h>
#include <cassert>
#include <vector>
#include <ctime>
#include <sys/wait.h>

using namespace std;
#include "test.h"

#define PROCESSSUM 5

int waitread(int fd, bool &quit)
{
    int commond;
    ssize_t s = read(fd, &commond, sizeof(commond));
    if (s == 0)
    {
        quit = true;
        return -1;
    }
    return commond;
}

int main()
{
    load();
    // 多个子进程用来接收任务
    vector<pair<pid_t, int>> childs;
    for (int i = 0; i < PROCESSSUM; i++)
    {
        // 准备管道
        int pipearry[2] = {0};
        int s = pipe(pipearry);
        assert(s == 0);
        (void)s;
        // 创建子进程
        pid_t id = fork();
        if (id == 0)
        {
            // 关闭写端

            close(pipearry[1]);
            // 接收父进程发的任务
            while (true)
            {
                // 读取任务
                bool quit = false; // 表示进程是否结束
                int commond = waitread(pipearry[0], quit);

                if (quit)
                    break;
                // 接收到命令，查看是哪个命令
                if (commond >= 0 && commond < tableSize())
                {
                    commontable[commond]();
                }
                else
                {
                    cout << "命令输入错误" << endl;
                }
                
            }
            exit(1);
        }
        // 存储子进程
        // 父进程关闭读端
        close(pipearry[0]);
        childs.push_back(make_pair(id, pipearry[1]));
    }
    // 派发任务
    srand((unsigned)time(nullptr));
    while (true)
    {
        int commond = rand() % tableSize();
        int choisechild = rand() % childs.size();

        // int commond=0;
        // int choisechild=0;
        write(childs[choisechild].second, &commond, sizeof(commond));


        sleep(1);
    }
    for (auto &x : childs)
    {
        close(x.second);
        waitpid(x.first, nullptr, 0);
    }

    return 0;
}