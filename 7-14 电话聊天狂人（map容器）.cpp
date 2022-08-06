/*7-14 电话聊天狂人 (25 分)
给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

输入格式:
输入首先给出正整数N（≤10^5），为通话记录条数。随后N行，每行给出一条通话记录。简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

输出格式:
在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832

输出样例:
13588625832 3*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, size_t> cnt;
    string tmp;
    int n, max = 0, max_cnt = 0;
    cin >> n;
    for (int i = 0; i < 2 * n; ++i)
    {
        cin >> tmp;
        cnt[tmp] += 1;
        if (cnt[tmp] > max)
            max = cnt[tmp];
    }
    string max_tel;
    for (auto &k: cnt)
        if (k.second == max)
        {
            max_cnt += 1;
            if (max_tel.empty())
                max_tel = k.first;
        };
    cout << max_tel << " " << max;
    if (max_cnt > 1)
        cout << max_cnt;
}