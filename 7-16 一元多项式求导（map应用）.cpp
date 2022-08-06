/*7-16 一元多项式求导 (20 分)
设计函数求一元多项式的导数。

输入格式:
以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。

输入样例:
3 4 -5 2 6 1 -2 0

输出样例:
12 3 -10 1 6 0*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<int, int> poly, dp;
    int coe, idx;
    while (cin >> coe >> idx)
        poly[idx] = coe;
    for (auto &k: poly)
        if (k.first != 0)
            dp[k.first - 1] = k.second * k.first;
    if (dp.empty())
        cout << "0 0";
    else
        for (auto k = dp.rbegin(); k != dp.rend(); ++k)
            cout << (k != dp.rbegin() ? " " : "") << k->second << " " << k->first; //将开头是否需要空格语句进行简化
}
//map太强了吧