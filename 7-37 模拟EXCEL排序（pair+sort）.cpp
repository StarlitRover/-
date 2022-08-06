/*7-37 ģ��EXCEL���� (25 ��)
Excel���Զ�һ���¼������ָ�������������д����ʵ�����ƹ��ܡ�

�����ʽ:
����ĵ�һ�а�������������N(��10^5) ��C������N�Ǽ�¼��������C��ָ��������кš�֮���� N�У�ÿ�а���һ��ѧ����¼��ÿ��ѧ����¼��ѧ�ţ�6λ���֣���֤û���ظ���ѧ�ţ���������������8λ�Ҳ������ո���ַ��������ɼ���[0, 100]�ڵ���������ɣ�����������1���ո������

�����ʽ:
��N���������Ҫ�������Ľ����������C=1ʱ����ѧ�ŵ������򣻵�C=2ʱ���������ķǵݼ��ֵ������򣻵�C=3ʱ�����ɼ��ķǵݼ����򡣵�����ѧ��������ͬ����������ͬ�ɼ�ʱ�������ǵ�ѧ�ŵ�������

��������:
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60

�������:
000001 Zoe 60
000007 James 85
000010 Amy 90*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<string, pair<string, int>> person; //����������ʱ����typedefһ��
//pair yyds~
int main()
{
    int n, s, c;
    string num, name;
    vector<person> info;
    cin >> n >> c;
    for (int i = 0; i < n; ++i)
    {
        cin >> num >> name >> s;
        info.push_back(move(pair(num, pair(name, s)))); //move���Ч��
    }
    switch (c)
    {
        case 1:
            sort(info.begin(), info.end(), [](person &a, person &b)
            { return a.first < b.first; });
            break;
        case 2:
            sort(info.begin(), info.end(), [](person &a, person &b)
            { return a.second.first < b.second.first || (a.second.first == b.second.first && a.first < b.first); });
            break;
        case 3:
            sort(info.begin(), info.end(), [](person &a, person &b)
            { return a.second.second < b.second.second || (a.second.second == b.second.second && a.first < b.first); });
            break;
    }
    for (auto &p: info)
        cout << p.first << " " << p.second.first << " " << p.second.second << endl;
}