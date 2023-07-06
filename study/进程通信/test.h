#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

typedef function<void()> fun;
vector<fun> commontable;
unordered_map<int,string> desc;

void readMysql()
{
    cout<<"读取数据库"<<"进程pid"<<getpid()<<endl<<endl;
}
void accurl()
{
    cout<<"访问网页"<<"进程pid"<<getpid()<<endl<<endl;
}
void dataencr()
{
    cout<<"数据加密"<<"进程pid"<<getpid()<<endl<<endl;
}
void persistence()
{
    cout<<"数据持久化"<<"进程pid"<<getpid()<<endl<<endl;
}
void load()
{
    desc.insert({commontable.size(),"读取数据库"});
    commontable.push_back(readMysql);

    desc.insert({commontable.size(), "访问网页"});
    commontable.push_back(accurl);

    desc.insert({commontable.size(), "数据加密"});
    commontable.push_back(dataencr);

    desc.insert({commontable.size(), "数据持久化"});
    commontable.push_back(persistence);
}

int tableSize()
{
    return commontable.size();
}