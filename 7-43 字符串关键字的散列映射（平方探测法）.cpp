/*7-43 字符串关键字的散列映射 (25 分)
给定一系列由大写英文字母组成的字符串关键字和素数P，用移位法定义的散列函数H(Key)将关键字Key中的最后3个字符映射为整数，每个字符占5位；再用除留余数法将整数映射到长度为P的散列表中。例如将字符串AZDEG插入长度为1009的散列表中，我们首先将26个大写英文字母顺序映射到整数0~25；再通过移位将其映射为3×32^2+4×32+6=3206；然后根据表长得到3206，即是该字符串的散列映射位置。

发生冲突时请用平方探测法解决。

输入格式:
输入第一行首先给出两个正整数N（≤500）和P（≥2N的最小素数），分别为待插入的关键字总数、以及散列表的长度。第二行给出N个字符串关键字，每个长度不超过8位，其间以空格分隔。

输出格式:
在一行内输出每个字符串关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。

输入样例1:
4 11
HELLO ANNK ZOE LOLI

输出样例1:
3 10 4 0

输入样例2:
6 11
LLO ANNA NNK ZOJ INNK AAA
输出样例2:
3 0 10 9 6 1*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
    int n, p;
    cin >> n >> p;
    map<int, string> hash;
    string s;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        auto si = s.rbegin();
        int Hkey = 0;
        for (int j = 0; j < 3 && si != s.rend(); ++j, ++si)
            Hkey += (*si - 'A') << j * 5;
        Hkey = Hkey % p;
        if (hash.find(Hkey) == hash.end() || hash[Hkey] == s) //无冲突或已存
        {
            hash[Hkey] = s;
            cout << ((i == 0) ? "" : " ") << Hkey;
        }
        else
        {
            int index;
            for (int k = 1; k <= p / 2; ++k)
            {
                index = (Hkey + k * k) % p;
                if (hash.find(index) == hash.end())
                    break;
                index = (Hkey - k * k) % p + (Hkey - k * k < 0 ? p : 0); //注意【?:】优先级！！！#另外负数的取余也是负数：-7/3=-1
                if (hash.find(index) == hash.end())
                    break;
            }
            hash[index] = s;
            cout << ((i == 0) ? "" : " ") << index;
        }
    }
}