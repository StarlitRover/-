/*7-22 ��ջģ����� (25 ��)
����֪��������ջS1��S2��������������ջģ���һ������Q��

�����ʽ:
�������ȸ�������������N1��N2����ʾ��ջS1��S2�����������������һϵ�еĶ��в�����A item��ʾ��item���У��������itemΪ�������֣���D��ʾ���Ӳ�����T��ʾ���������

�����ʽ:
�������е�ÿ��D�����������Ӧ���ӵ����֣����ߴ�����ϢERROR:Empty�������Ӳ����޷�ִ�У�Ҳ��Ҫ���ERROR:Full��ÿ�����ռ1�С�

��������:
3 2
A 1 A 2 A 3 A 4 A 5 D A 6 D A 7 D A 8 D D D D T

�������:
ERROR:Full
1
ERROR:Full
2
3
4
7
8
ERROR:Empty*/

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int max, min;
    cin >> max >> min;
    if (max < min)
        swap(max, min);
    stack<int> output, buffer;
    char cmd;
    while (cin >> cmd, cmd != 'T')
    {
        switch (cmd)
        {
            case 'A':
                int n;
                cin >> n;
                if (buffer.size() < min)
                    buffer.push(n);
                else if (output.empty())
                {
                    while (!buffer.empty())
                    {
                        output.push(buffer.top());
                        buffer.pop();
                    }
                    buffer.push(n);
                }
                else
                    cout << "ERROR:Full" << endl;
                break;
            case 'D':
                if (!output.empty())
                {
                    cout << output.top() << endl;
                    output.pop();
                }
                else if (!buffer.empty())
                {
                    while (!buffer.empty())
                    {
                        output.push(buffer.top());
                        buffer.pop();
                    }
                    cout << output.top() << endl;
                    output.pop();
                }
                else
                    cout << "ERROR:Empty" << endl;
                break;
        }
    }
}

//����˼·��Сջ��Ϊ�����ݴ�������ջ��Ϊ���������������Сջ��ѹ�����ݣ���Сջ����Сջ������һȡ��ѹ���ջ����ʱ�����Ϊ����
/*ע�����
1.Сջ����ջǨ��ʱ���뽫��ǰСջ��գ������ı�˳��
2.ֻ�е���ջ������ʱ�������ջѹ������:��ջ��Ϊ�յ����� ��Сջ����ʱ ����ѹ������
3.֮���Դ�ջ��Ϊ�����Ϊ��������Сջ���������(��)ʱ����������
4.Ҫ���ʱ����ջΪ���򽫵���Сջ��ȫ������Ǩ�ƹ���