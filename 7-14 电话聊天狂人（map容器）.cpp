/*7-14 �绰������� (25 ��)
���������ֻ��û�ͨ����¼���ҳ�����ͨ����������������ˡ�

�����ʽ:
�������ȸ���������N����10^5����Ϊͨ����¼���������N�У�ÿ�и���һ��ͨ����¼�������������ֻ�г��������ͽ��շ���11λ���ֹ��ɵ��ֻ����룬�����Կո�ָ���

�����ʽ:
��һ���и���������˵��ֻ����뼰��ͨ������������Կո�ָ�������������˲�Ψһ���������������С�ĺ��뼰��ͨ�����������Ҹ��Ӹ������п��˵�������

��������:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832

�������:
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