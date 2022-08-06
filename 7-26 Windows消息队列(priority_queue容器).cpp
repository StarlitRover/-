/*7-26 Windows消息队列 (25 分)
消息队列是Windows系统的基础。对于每个进程，系统维护一个消息队列。如果在进程中有特定事件发生，如点击鼠标、文字改变等，系统将把这个消息加到队列当中。同时，如果队列不是空的，这一进程循环地从队列中按照优先级获取消息。请注意优先级值低意味着优先级高。请编辑程序模拟消息队列，将消息加到队列中以及从队列中获取消息。

输入格式:
输入首先给出正整数N（≤10^5），随后N行，每行给出一个指令??GET或PUT，分别表示从队列中取出消息或将消息添加到队列中。如果指令是PUT，后面就有一个消息名称、以及一个正整数表示消息的优先级，此数越小表示优先级越高。消息名称是长度不超过10个字符且不含空格的字符串；题目保证队列中消息的优先级无重复，且输入至少有一个GET。

输出格式:
对于每个GET指令，在一行中输出消息队列中优先级最高的消息的名称和参数。如果消息队列中没有消息，输出EMPTY QUEUE!。对于PUT指令则没有输出。

输入样例:
9
PUT msg1 5
PUT msg2 4
GET
PUT msg3 2
PUT msg4 4
GET
GET
GET
GET

输出样例:
msg2
msg3
msg4
msg1
EMPTY QUEUE!*/

#include <iostream>
#include <queue>

using namespace std;

class node
{
private:
    int rank;
public:
    string msg;
    node(int _rank,string _msg):rank(_rank),msg(_msg){};
    friend bool operator <(const node& a,const node& b) //friend bool operator <(node& a,node& b)将会报错,因为没有保证a,b不变
    {return a.rank>b.rank;}
};

int main()
{
    int n, p;
    cin >> n;
    string cmd, tmp;
    priority_queue<node> queue; //神奇的优先队列容器
    for (int i = 0; i < n; ++i)
    {
        cin >> cmd;
        if (cmd == "PUT")
        {
            cin >> tmp >> p;
            node apd(p,tmp);
            queue.push(apd);
        }
        else
        {
            if (queue.empty())
                cout << "EMPTY QUEUE!" << endl;
            else
            {
                cout << queue.top().msg << endl;
                queue.pop();
            }
        }
    }
}
//这一题可以使用map，但是map将会超时