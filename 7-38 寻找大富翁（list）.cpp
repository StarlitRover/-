/*7-38 寻找大富翁 (25 分)
胡润研究院的调查显示，截至2017年底，中国个人资产超过1亿元的高净值人群达15万人。假设给出N个人的个人资产值，请快速找出资产排前M位的大富翁。

输入格式:
输入首先给出两个正整数N（≤10^6）和M（≤10），其中N为总人数，M为需要找出的大富翁数；接下来一行给出N个人的个人资产值，以百万元为单位，为不超过长整型范围的整数。数字间以空格分隔。

输出格式:
在一行内按非递增顺序输出资产排前M位的大富翁的个人资产值。数字间以空格分隔，但结尾不得有多余空格。

输入样例:
8 3
8 12 7 3 20 9 5 18

输出样例:
20 18 12*/

//Method 1:
#include <iostream>
#include <list>

using namespace std;

int main()
{
    int n, m, t;
    cin >> n >> m;
    m = min(m, n);   //确保m不会超过n
    list<int> money; //只存前m个数据
    for (int i = 0; i < n; ++i)
    {
        bool flag = false;
        cin >> t;
        if (money.size() == m && t <= money.back())
            continue;
        for (auto i = money.begin(); i != money.end(); ++i)
            if (*i < t)
            {
                flag = true;
                money.insert(i, t);
                break;
            }
        if (!flag) //money内元素不足m且t是当前容器最小元素时
            money.push_back(t);
        else if (money.size() > m)
            money.erase(--money.end());
    }
    cout << money.front();
    for (auto i = ++money.begin(); i != money.end(); ++i)
        cout << " " << *i;
}
//本题M<=10是关键，事实上我们只要确定前m个位置即可，剩余元素无需排序

//Method 2:
#include<iostream>
#include<set>

using namespace std;

int main()
{
    int n, m, t;
    cin >> n >> m;
    multiset<int, greater<>> money;
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        money.insert(t);
    }
    auto top = money.begin();
    cout << *top;
    int inf = min(n, m);
    for (auto i = 1; i < inf; ++i)
    {
        ++top;
        cout << " " << *top;
    }
}
//一般做法，但N较大时会超时