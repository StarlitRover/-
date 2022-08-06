/*7-15 QQ�ʻ����������½ (25 ��)
ʵ��QQ���ʻ���������ʻ���½�ļ򻯰湦�ܡ������ս�ǣ���˵���ڵ�QQ�����Ѿ���10λ���ˡ�

�����ʽ:
�������ȸ���һ��������N����10^5����������N��ָ�ÿ��ָ��ĸ�ʽΪ������������ո�QQ���루�ո����롱�����������Ϊ��N��������New��ʱ��ʾҪ������һ��QQ�ţ����������ʻ��ĺ�������룻�����Ϊ��L��������Login��ʱ��ʾ�����ʻ���½�������ǵ�½��Ϣ��QQ����Ϊһ��������10λ��������1000����˵QQ���ܵĺ�����1001��������������Ϊ��С��6λ��������16λ���Ҳ������ո���ַ�����

�����ʽ:
���ÿ��ָ�������Ӧ����Ϣ��

1�����������ʻ��ɹ����������New: OK����
2����������ĺ����Ѿ����ڣ��������ERROR: Exist����
3�������ʻ���½�ɹ����������Login: OK����
4�������ʻ�QQ���벻���ڣ��������ERROR: Not Exist����
5�������ʻ���������������ERROR: Wrong PW����

��������:
5
L 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
L 1234567890 myQQ@qq
L 1234567890 myQQ@qq.com

�������:
ERROR: Not Exist
New: OK
ERROR: Exist
ERROR: Wrong PW
Login: OK*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, string> info;
    int n;
    cin >> n;
    char cmd;
    string account, password;
    for (int i = 0; i < n; ++i)
    {
        cin >> cmd >> account >> password;
        auto loc = info.find(account);
        switch (cmd)
        {
            case 'L':
                if (loc == info.end())
                    cout << "ERROR: Not Exist" << endl;
                else if (loc->second == password)
                    cout << "Login: OK" << endl;
                else
                    cout << "ERROR: Wrong PW" << endl;
                break;
            case 'N':
                if (loc == info.end())
                {
                    cout << "New: OK" << endl;
                    info[account] = password;
                }
                else
                    cout << "ERROR: Exist" << endl;
                break;
        }
    }
}
