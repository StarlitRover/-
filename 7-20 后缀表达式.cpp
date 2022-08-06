/*7-20 ���ʽת�� (25 ��)
�������ʽ��ǰ׺��ʾ������׺��ʾ���ͺ�׺��ʾ������ʽ���ճ�ʹ�õ��������ʽ�ǲ�����׺��ʾ��������Ԫ�����λ�������������м䡣����Ƴ�����׺���ʽת��Ϊ��׺���ʽ��

�����ʽ:
������һ���и��������ո����׺���ʽ���ɰ���+��-��*��\�Լ���������()�����ʽ������20���ַ���

�����ʽ:
��һ�������ת����ĺ�׺���ʽ��Ҫ��ͬ������������������ţ�֮���Կո�ָ�������β�����ж���ո�

��������:
2+3*(7-4)+8/4

�������:
2 3 7 4 - * + 8 4 / +
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

short priority(char &x)
{
    switch (x)
    {
        case '+':
            return 0;
        case '-':
            return 0;
        case '*':
            return 1;
        case '/':
            return 1;
        case '(':
            return 2;
    }
}

int main()
{
    string expr;
    cin >> expr;
    stack<char> opr;
    bool isNum = false, flag = true;//isNum����ǰһ���ַ��ǲ�������,flag����Ƿ�Ϊ�����ͷ��ȷ���Ƿ���Ҫ����ո�
    for (auto &s: expr)
    {
        if (s >= '0' && s <= '9' || s == '.')
        {
            cout << (flag || isNum ? (flag = false, "") : " ") << s;
            isNum = true;
        }
        else if (s == ')')
        {
            isNum = true;//')'����ֻ�������������˿��ǵ���Ϊ��������ͷ��'+' '-'ʶ��������Ҫ��isNum��Ϊtrue,����Ὣ')'�����'+' '-'ʶ��Ϊ�������ķ���λ
            while (opr.top() != '(')
            {
                cout << " " << opr.top();
                opr.pop();
            }
            opr.pop();
        }
        else
        {
            if (!isNum && (s == '-' || s == '+')) //�ж��Ƿ�Ϊ�������ķ���λ
            {
                cout << (flag ? "" : " ") << (s == '+' ? "" : "-"); //ע�������ʱ����Ҫ������Ϊ����������λ��'+'
                isNum = true;
                continue;
            }
            isNum = false;
            while (!opr.empty() && opr.top() != '(' && priority(opr.top()) >= priority(s))
			//֮������>=����Ϊͬ��������ǰ��մ������ҵ�˳������,�����Ҫ����ǰ������ͬ�ȼ���������
            {
                cout << " " << opr.top();
                opr.pop();
            }
            opr.push(s);
        }
    }
    while (!opr.empty())
    {
        cout << " " << opr.top();
        opr.pop();
    }
}

/*Notice:
1.�������'+' '-'ǰ��һλ�Ƿ�Ϊ��������ж������Ƿ���λ�������������������һ���������')'
2.�������ʽ������ǰ���ܺ�'+'��Ȼ����������������Ժ���'+'