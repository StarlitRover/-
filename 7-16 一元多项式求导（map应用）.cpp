/*7-16 һԪ����ʽ�� (20 ��)
��ƺ�����һԪ����ʽ�ĵ�����

�����ʽ:
��ָ���ݽ���ʽ�������ʽ������ϵ����ָ��������ֵ��Ϊ������1000�������������ּ��Կո�ָ���

�����ʽ:
����������ͬ�ĸ�ʽ�����������ʽ�������ϵ����ָ�������ּ��Կո�ָ�������β�����ж���ո�

��������:
3 4 -5 2 6 1 -2 0

�������:
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
            cout << (k != dp.rbegin() ? " " : "") << k->second << " " << k->first; //����ͷ�Ƿ���Ҫ�ո������м�
}
//map̫ǿ�˰�