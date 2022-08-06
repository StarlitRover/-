/*7-38 Ѱ�Ҵ��� (25 ��)
�����о�Ժ�ĵ�����ʾ������2017��ף��й������ʲ�����1��Ԫ�ĸ߾�ֵ��Ⱥ��15���ˡ��������N���˵ĸ����ʲ�ֵ��������ҳ��ʲ���ǰMλ�Ĵ��̡�

�����ʽ:
�������ȸ�������������N����10^6����M����10��������NΪ��������MΪ��Ҫ�ҳ��Ĵ�������������һ�и���N���˵ĸ����ʲ�ֵ���԰���ԪΪ��λ��Ϊ�����������ͷ�Χ�����������ּ��Կո�ָ���

�����ʽ:
��һ���ڰ��ǵ���˳������ʲ���ǰMλ�Ĵ��̵ĸ����ʲ�ֵ�����ּ��Կո�ָ�������β�����ж���ո�

��������:
8 3
8 12 7 3 20 9 5 18

�������:
20 18 12*/

//Method 1:
#include <iostream>
#include <list>

using namespace std;

int main()
{
    int n, m, t;
    cin >> n >> m;
    m = min(m, n);   //ȷ��m���ᳬ��n
    list<int> money; //ֻ��ǰm������
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
        if (!flag) //money��Ԫ�ز���m��t�ǵ�ǰ������СԪ��ʱ
            money.push_back(t);
        else if (money.size() > m)
            money.erase(--money.end());
    }
    cout << money.front();
    for (auto i = ++money.begin(); i != money.end(); ++i)
        cout << " " << *i;
}
//����M<=10�ǹؼ�����ʵ������ֻҪȷ��ǰm��λ�ü��ɣ�ʣ��Ԫ����������

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
//һ����������N�ϴ�ʱ�ᳬʱ