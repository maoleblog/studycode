#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    int ret = open("test.txt", O_RDONLY);
    cout << "test1:" << ret << endl;
    sleep(100000);
    return 0;
}