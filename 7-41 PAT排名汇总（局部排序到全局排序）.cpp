/*7-41 PAT�������� (25 ��)
�������������������ԣ�Programming Ability Test�����PAT��ּ��ͨ��ͳһ��֯�����߿��Լ��Զ����ⷽ���͹۵����п������㷨�����������ʵ����������ѧ�����ۼ������������˲ţ�Ϊ��ҵѡ���˲��ṩ�ο���׼����ַhttp://www.patest.cn����

ÿ�ο��Ի������ɸ���ͬ�Ŀ���ͬʱ���У�ÿ�������þ�����������������ĳɼ������Խ����󣬸�������ĳɼ������̻��ܳ�һ���ܵ�������

���ھ�����дһ�������Զ��鲢��������ĳɼ���������������

�����ʽ:
����ĵ�һ�и���һ��������N����100����������������������N������ĳɼ�����ʽΪ������һ�и���������K����300��������ÿ���Ŀ������������K�У�ÿ�и���1����������Ϣ���������ţ���13λ��������ɣ��͵÷֣�Ϊ[0,100]�����ڵ����������м��ÿո�ָ���

�����ʽ:
�����ڵ�һ��������������������������ܵ�������ÿ����������Ϣռһ�У�˳��Ϊ�����š����������������š��ڸÿ�������������п��㰴���������˳���1��N��š�����������밴���������ķǵݼ�˳������������ͬ�����Ŀ���Ӧ����ͬ���Σ��������ŵĵ���˳�������

��������:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85

�������:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class student
{
public:
    string num;
    int score, test_room, room_rank;

    student(string n, int s, int tr) : num(n), score(s), test_room(tr)
    {};
};

bool cmp(student &x, student &y) //����cmp�ȽϺ���
{ return x.score > y.score || (x.score == y.score && x.num < y.num); }

int main()
{
    int n, m, rank, pre;
    cin >> n;
    vector<student> room, all;
    for (int i = 0; i < n; ++i)
    {
        cin >> m;
        for (int j = 0; j < m; ++j)
        {
            string num;
            int score;
            cin >> num >> score;
            room.emplace_back(student(num, score, i + 1));
        }
        sort(room.begin(), room.end(), cmp);
        rank = 1, pre = room[0].score;
        for (int j = 0; j < m; ++j)
        {
            rank = (room[j].score == pre) ? rank : j + 1;
            room[j].room_rank = rank;
            pre = room[j].score;
        }
        all.insert(all.end(), room.begin(), room.end()); //�Ƚ��굥�������󽫸ÿ���ѧ����Ϣ����all�����room
        room.clear();
    }
    sort(all.begin(), all.end(), cmp);
    cout << all.size() << endl;
    rank = 1, pre = all[0].score;
    for (int i = 0; i < all.size(); ++i)
    {
        rank = (all[i].score == pre) ? rank : i + 1;
        pre = all[i].score;
        cout << all[i].num << " " << rank << " " << all[i].test_room << " " << all[i].room_rank << endl;
    }
}