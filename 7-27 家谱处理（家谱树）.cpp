/*7-27 ���״��� (30 ��)
����ѧ�о����ڼ���ܸ���Ȥ�������о���Ա�Ѽ���һЩ����ļ��׽����о���ʵ���У�ʹ�ü����������ס�Ϊ��ʵ�����Ŀ�ģ��о���Ա������ת��Ϊ�ı��ļ�������Ϊ�����ı��ļ���ʵ����

John
  Robert
    Frank
    Andrew
  Nancy
    David
�����ı��ļ��У�ÿһ�а���һ���˵����֡���һ���е����������������������ȡ����׽������������ȵĺ���������ǵ��ɷ�����Ӳ������ڼ����С�ÿ���˵���Ů�ȸ�ĸ������2���ո������������ı��ļ�Ϊ����John���������������ȣ�����������ŮRobert��Nancy��Robert��������ŮFrank��Andrew��Nancyֻ��һ����ŮDavid��

��ʵ���У��о���Ա���ռ��˼�ͥ�ļ�������ȡ�˼������й������˹�ϵ�ĳ�����䡣����Ϊ�����й�ϵ�ĳ������ʵ����

John is the parent of Robert
Robert is a sibling of Nancy
David is a descendant of Robert
�о���Ա��Ҫ�ж�ÿ������������滹�Ǽ٣����д��������о���Ա�жϡ�

�����ʽ:
�������ȸ���2��������N��2��N��100����M����100��������NΪ���������ֵ�������MΪ�����г������������������ÿ�в�����70���ַ���

���ֵ��ַ����ɲ�����10��Ӣ����ĸ��ɡ��ڼ����еĵ�һ�и���������ǰû�������ո񡣼����е�����������������2���ո񣬼������Ǽ������������ȣ���һ�и��������֣��ĺ���������������һ������ǰ����k���ո�����һ����������������k+2���ո�

��һ��������ͬ�������ֲ���������Σ��Ҽ�����û�г��ֵ����ֲ�������ڳ�������С�ÿ���������ʽ���£�����X��YΪ�����еĲ�ͬ���֣�

X is a child of Y
X is the parent of Y
X is a sibling of Y
X is a descendant of Y
X is an ancestor of Y
�����ʽ:
���ڲ��������е�ÿ�������䣬��һ�������True���������Ϊ�棬��False���������Ϊ�١�

��������:
6 5
John
  Robert
    Frank
    Andrew
  Nancy
    David
Robert is a child of John
Robert is an ancestor of Andrew
Robert is a sibling of Nancy
Nancy is the parent of Frank
John is a descendant of Andrew

�������:
True
True
True
False
False
*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

inline void Judge(bool fact)
{
    if (fact)
        cout << "True" << endl;
    else
        cout << "False" << endl;
}

bool isDescendant(string &name1, string &name2, map<string, string> &parent)
{
    string member = name1;
    while (parent[member] != "")
    {
        member = parent[member];
        if (member == name2)
            return true;
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    string name;
    char c;
    map<string, string> parent;
    map<int, string> rank;
    cin >> name;
    rank[0] = name;
    parent[name] = ""; //�����һ�����Ե㡿�������õ�һ����(John)�ĸ��ڵ�ָ���Լ������򵱳���"Robert is a sibling of John"���ж����ʱ������
    cin.get();
    for (int i = 0; i < n - 1; ++i)
    {
        int cnt = 0;
        while ((c = cin.get()) == ' ')
            ++cnt;
        getline(cin, name); //�����������Ե㡿����ʹ��cin>>name�����򵱸���ֻ��һ���ַ�ʱ��cin���Զ����ж�ȡname��
        name = c + name;
        parent[name] = rank[cnt - 2]; //ֱ��������ǰ�ո�ĸ������������ȼ������֣�
        rank[cnt] = name;   
//rankֻ���סĳһ�������ֵ��Ǹ��ˣ����ݼ��׵����뷽ʽ����֪��ֻ��ĳһ�������ֵ��Ǹ��˻��п��ܳ�Ϊ�����˵ĸ��ڵ㣬���Կ���ֱ�Ӹ���
//getline�����Ѿ�����ĩβ�Ļس�����ȡ��������ﲻ��Ҫcin.get()
    }
    string name1, name2, judge1, judge2;
    for (int i = 0; i < m; ++i)
    {
        cin >> name1;
        cin.ignore(4);
        cin >> judge1;
        cin >> judge2;
        cin.ignore(4);
        cin >> name2;
        if (judge1 == "a")
        {
            if (judge2 == "child")
                Judge(parent[name1] == name2);
            else if (judge2 == "sibling")
                Judge(parent[name1] == parent[name2]);
            else if (judge2 == "descendant")
                Judge(isDescendant(name1, name2, parent));
        }
        else if (judge1 == "the")
            Judge(parent[name2] == name1);
        else
            Judge(isDescendant(name2, name1, parent));
    }
}
//����������ַ�������Ҳ��һ���ѵ�,rank�Ǳ��ʽ��һ������