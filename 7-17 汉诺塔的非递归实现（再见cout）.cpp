/*7-17 汉诺塔的非递归实现 (25 分)
借助堆栈以非递归（循环）方式求解汉诺塔的问题（n, a, b, c），即将N个盘子从起始柱（标记为“a”）通过借助柱（标记为“b”）移动到目标柱（标记为“c”），并保证每个移动符合汉诺塔问题的要求。

输入格式:
输入为一个正整数N，即起始柱上的盘数。

输出格式:
每个操作（移动）占一行，按柱1 -> 柱2的格式输出。*/

#include <iostream>
#include <stack>

using namespace std;

class single
{
public:
    char start;
    char end;
    int n;

    single(char s, char e, int n) :
            start(s), end(e), n(n)
    {};
};

int main()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "a -> c" << endl;
        exit(0);
    }
    stack<single> info;
    info.push(single('a', 'c', n));
    while (!info.empty())
    {
        auto s = info.top();
        info.pop();
        if (s.n == 1)
            printf("%c -> %c\n", s.start, s.end); //cout害我一直卡在第四个测试点.......
        else
        {
            char r = (char) ('a' + 'b' + 'c' - s.start - s.end);
            info.push(single(r, s.end, s.n - 1));
            info.push(single(s.start, s.end, 1));
            info.push(single(s.start, r, s.n - 1));
        }
    }
}
//这题不难，只是cout这玩意…