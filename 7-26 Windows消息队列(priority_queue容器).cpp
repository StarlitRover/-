/*7-26 Windows��Ϣ���� (25 ��)
��Ϣ������Windowsϵͳ�Ļ���������ÿ�����̣�ϵͳά��һ����Ϣ���С�����ڽ��������ض��¼�������������ꡢ���ָı�ȣ�ϵͳ���������Ϣ�ӵ����е��С�ͬʱ��������в��ǿյģ���һ����ѭ���شӶ����а������ȼ���ȡ��Ϣ����ע�����ȼ�ֵ����ζ�����ȼ��ߡ���༭����ģ����Ϣ���У�����Ϣ�ӵ��������Լ��Ӷ����л�ȡ��Ϣ��

�����ʽ:
�������ȸ���������N����10^5�������N�У�ÿ�и���һ��ָ��??GET��PUT���ֱ��ʾ�Ӷ�����ȡ����Ϣ����Ϣ��ӵ������С����ָ����PUT���������һ����Ϣ���ơ��Լ�һ����������ʾ��Ϣ�����ȼ�������ԽС��ʾ���ȼ�Խ�ߡ���Ϣ�����ǳ��Ȳ�����10���ַ��Ҳ����ո���ַ�������Ŀ��֤��������Ϣ�����ȼ����ظ���������������һ��GET��

�����ʽ:
����ÿ��GETָ���һ���������Ϣ���������ȼ���ߵ���Ϣ�����ƺͲ����������Ϣ������û����Ϣ�����EMPTY QUEUE!������PUTָ����û�������

��������:
9
PUT msg1 5
PUT msg2 4
GET
PUT msg3 2
PUT msg4 4
GET
GET
GET
GET

�������:
msg2
msg3
msg4
msg1
EMPTY QUEUE!*/

#include <iostream>
#include <queue>

using namespace std;

class node
{
private:
    int rank;
public:
    string msg;
    node(int _rank,string _msg):rank(_rank),msg(_msg){};
    friend bool operator <(const node& a,const node& b) //friend bool operator <(node& a,node& b)���ᱨ��,��Ϊû�б�֤a,b����
    {return a.rank>b.rank;}
};

int main()
{
    int n, p;
    cin >> n;
    string cmd, tmp;
    priority_queue<node> queue; //��������ȶ�������
    for (int i = 0; i < n; ++i)
    {
        cin >> cmd;
        if (cmd == "PUT")
        {
            cin >> tmp >> p;
            node apd(p,tmp);
            queue.push(apd);
        }
        else
        {
            if (queue.empty())
                cout << "EMPTY QUEUE!" << endl;
            else
            {
                cout << queue.top().msg << endl;
                queue.pop();
            }
        }
    }
}
//��һ�����ʹ��map������map���ᳬʱ