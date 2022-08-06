/*7-21 ��ǰ׺���ʽ��ֵ (25 ��)
�������ʽ��ǰ׺��ʾ������׺��ʾ���ͺ�׺��ʾ������ʽ��ǰ׺���ʽָ��Ԫ�����λ������������֮ǰ������2+3*(7-4)+8/4��ǰ׺���ʽ�ǣ�+ + 2 * 3 - 7 4 / 8 4������Ƴ������ǰ׺���ʽ�Ľ��ֵ��

�����ʽ:
������һ���ڸ���������30���ַ���ǰ׺���ʽ��ֻ����+��-��*��/�Լ�����������ͬ������������������ţ�֮���Կո�ָ���

�����ʽ:
���ǰ׺���ʽ��������������С�����1λ���������ϢERROR��

��������:
+ + 2 * 3 - 7 4 / 8 4

�������:
13.0*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    vector<string> expr;
    vector<bool> isNum;
    string tmp;
    while (cin >> tmp/*, tmp != "0"*/)
    {
        if (tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/")
        {
            expr.push_back(tmp);
            isNum.push_back(false);
        }
        else if (tmp[0] == '+' || tmp[0] == '-' || isdigit(tmp[0]))
        {
            for (int i = 1; i < tmp.size(); ++i)//����Ƿ�����Ƿ��ַ�
                if (!isdigit(tmp[i]) && tmp[i] != '.')
                {
                    cout << "ERROR";
                    exit(0);
                }
            expr.push_back(tmp);
            isNum.push_back(true);
        }
    }
    for (int i = expr.size() - 1; i >= 0; --i)
    {
        if (isNum[i])
            continue;
        try
        {
            int a = stoi(expr.at(i + 2));
            expr.erase(expr.begin() + i + 2);
            int b = stoi(expr.at(i + 1));
            expr.erase(expr.begin() + i + 1);
            switch (expr[i][0])
            {
                case '+':
                    expr[i] = to_string(a + b);
                    break;
                case '-':
                    expr[i] = to_string(b - a);
                    break;
                case '*':
                    expr[i] = to_string(a * b);
                    break;
                case '/':
					if(a==0)//������Ե����:��������Ϊ0
	                    {
	                        cout<<"ERROR";
	                        exit(0);
	                    }
                    expr[i] = to_string(1.0 * b / a);
                    break;
            }
        }
        catch (exception)
        { cout << "ERROR"; }
    }
    if (expr.size() != 1)
    {
        cout << "ERROR";
        exit(0);
    }
	try//��ֹexpr��ʣһ����������stod���׳��쳣
	{
    	cout << fixed << setprecision(1) << stod(expr[0]);
	}
	catch (exception)
	{
		cout << "ERROR";
 	}
}

//�沨�����ʽ --from website
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<sstream>
#include<stdlib.h>
#include<iostream>
using namespace std;
stringstream ss;
int flag;
double f()
{
    char c[9];
    if (!(ss >> c)) //��ȫ�ֱ���stringstream������һ���������������
        flag = 1;   //���δ������˵��ǰ׺���ʽ���Ϸ�(��Ϊֻ����һλΪ������ʱ�Ż�ݹ����,��ôǰ׺���ʽ�в��������������)
    
    if (c[1] == '\0')//�ж��Ƿ�Ϊ������:������ֻ��һλ��˵ڶ�λ��'\0'
	{
        double numb1, numb2;
        switch (c[0]) //�ݹ��������˼��
        {
        case '+':return f() + f(); break;
        case '-':return f() - f(); break;
        case '*':return f()*f(); break;
        case '/':
            numb1 = f(); numb2 = f();
            if (fabs(numb2-0.0)<0.0000001){
                flag = 1;
                return 0.0;
            }
            else return numb1 / numb2; break;
        }
    }
    return atof(c);
}
int main()
{
    string s;
    flag = 0;
    getline(cin, s);
    ss << s;
    double n = f();
    if (flag)
        cout << "ERROR" << endl;
    else printf("%.1lf\n", n);
}