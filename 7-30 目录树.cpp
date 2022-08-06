/*7-30 Ŀ¼�� (30 ��)
��ZIP�鵵�ļ��У�����������ѹ���ļ���Ŀ¼�����·�������ơ���ʹ��WinZIP��GUI�����ZIP�鵵�ļ�ʱ�����Դ���Щ��Ϣ���ؽ�Ŀ¼����״�ṹ�����д����ʵ��Ŀ¼����״�ṹ���ؽ�������

�����ʽ:
�������ȸ���������N����10^4������ʾZIP�鵵�ļ��е��ļ���Ŀ¼�����������N�У�ÿ�������¸�ʽ���ļ���Ŀ¼�����·�������ƣ�ÿ�в�����260���ַ�����

·���������е��ַ�������Ӣ����ĸ�����ִ�Сд����
���š�\������Ϊ·���ָ������֣�
Ŀ¼�Է��š�\��������
�������ظ���������Ŀ��
���������С������2MB��
�����ʽ:
�������е�·���������rootĿ¼����rootĿ¼��ʼ�������ʱÿ��Ŀ¼��������Լ������֣�Ȼ�����ֵ������������Ŀ¼��Ȼ�����ֵ�����������ļ���ע�⣬�����ʱ��Ӧ����Ŀ¼����Թ�ϵʹ�ÿո����������ÿ��Ŀ¼���ļ�����һ��������2���ո�

��������:
7
b
c\
ab\cd
a\bc
ab\d
a\d\a
a\d\z\

�������:
root
  a
    d
      z
      a
    bc
  ab
    cd
    d
  c
  b*/
 
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class node
{
public:
    string name;
    map<string, node> paths; //Ϊ�˸�����ز�����Ŀ¼�ڵ㣬��map�Դ�������
    set<string> files;

    node() = default;;

    explicit node(string _name) : name(move(_name)) //�����_name�Ѿ��ǽ�ʵ�θ��ƽ�����ı��������move��ʵ��û��Ӱ��
    {};

    bool operator<(const node &b) const
    { return this->name < b.name; }
};

void Output(node &n, int k) //�ݹ�������
{
    cout<<string(k,' ');
    cout << n.name << endl;
    for (auto &p: n.paths)
        Output(p.second, k + 2);
    for (auto &s: n.files)
    {
        cout<<string(k+2,' ');
        cout << s << endl;
    }
};

int main()
{
    int n;
    cin >> n;
    string input, name;
    node root("root"), *pre = &root; //��ָ��������
    for (int j = 0; j < n; ++j)
    {
        cin >> input;
        pre = &root;
        for (int i = 0; i < input.size(); ++i)
        {
            for (i; i < input.size(); ++i) //������\���򳬳��ַ�������ʱ ��ȡname
                if (input[i] != '\\')
                    name += input[i];
                else
                    break;
            if (i != input.size())
            {
                pre->paths.insert({name,move(node(name))}); //��name��ֵ�Ѵ����򲻻����
                pre = &(pre->paths[name]);
            }
            else
                pre->files.insert(name);
            name.clear();
        }
    }
    Output(root, 0);
}