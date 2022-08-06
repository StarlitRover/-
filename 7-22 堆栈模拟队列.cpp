/*7-22 堆栈模拟队列 (25 分)
设已知有两个堆栈S1和S2，请用这两个堆栈模拟出一个队列Q。

输入格式:
输入首先给出两个正整数N1和N2，表示堆栈S1和S2的最大容量。随后给出一系列的队列操作：A item表示将item入列（这里假设item为整型数字）；D表示出队操作；T表示输入结束。

输出格式:
对输入中的每个D操作，输出相应出队的数字，或者错误信息ERROR:Empty。如果入队操作无法执行，也需要输出ERROR:Full。每个输出占1行。

输入样例:
3 2
A 1 A 2 A 3 A 4 A 5 D A 6 D A 7 D A 8 D D D D T

输出样例:
ERROR:Full
1
ERROR:Full
2
3
4
7
8
ERROR:Empty*/

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int max, min;
    cin >> max >> min;
    if (max < min)
        swap(max, min);
    stack<int> output, buffer;
    char cmd;
    while (cin >> cmd, cmd != 'T')
    {
        switch (cmd)
        {
            case 'A':
                int n;
                cin >> n;
                if (buffer.size() < min)
                    buffer.push(n);
                else if (output.empty())
                {
                    while (!buffer.empty())
                    {
                        output.push(buffer.top());
                        buffer.pop();
                    }
                    buffer.push(n);
                }
                else
                    cout << "ERROR:Full" << endl;
                break;
            case 'D':
                if (!output.empty())
                {
                    cout << output.top() << endl;
                    output.pop();
                }
                else if (!buffer.empty())
                {
                    while (!buffer.empty())
                    {
                        output.push(buffer.top());
                        buffer.pop();
                    }
                    cout << output.top() << endl;
                    output.pop();
                }
                else
                    cout << "ERROR:Empty" << endl;
                break;
        }
    }
}

//基本思路：小栈作为缓冲暂存区，大栈作为最终输出区。先往小栈中压入数据，若小栈满则将小栈数据逐一取出压入大栈，此时倒序变为正序。
/*注意事项：
1.小栈往大栈迁移时必须将当前小栈清空，否则会改变顺序
2.只有当大栈无数据时才能向大栈压入数据:大栈不为空但不满 且小栈已满时 不能压入数据
3.之所以大栈作为输出是为了能容纳小栈内数据最多(满)时的所有数据
4.要输出时若大栈为空则将当下小栈内全部数据迁移过来