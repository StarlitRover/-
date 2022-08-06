/*7-21 求前缀表达式的值 (25 分)
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。前缀表达式指二元运算符位于两个运算数之前，例如2+3*(7-4)+8/4的前缀表达式是：+ + 2 * 3 - 7 4 / 8 4。请设计程序计算前缀表达式的结果值。

输入格式:
输入在一行内给出不超过30个字符的前缀表达式，只包含+、-、*、/以及运算数，不同对象（运算数、运算符号）之间以空格分隔。

输出格式:
输出前缀表达式的运算结果，保留小数点后1位，或错误信息ERROR。

输入样例:
+ + 2 * 3 - 7 4 / 8 4

输出样例:
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
            for (int i = 1; i < tmp.size(); ++i)//检测是否输入非法字符
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
					if(a==0)//这个测试点绝了:除数不能为0
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
	try//防止expr仅剩一个操作符，stod会抛出异常
	{
    	cout << fixed << setprecision(1) << stod(expr[0]);
	}
	catch (exception)
	{
		cout << "ERROR";
 	}
}

//逆波兰表达式 --from website
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
    if (!(ss >> c)) //从全局变量stringstream流中逐一读入数据与运算符
        flag = 1;   //如果未读到则说明前缀表达式不合法(因为只有上一位为操作符时才会递归调用,那么前缀表达式中操作符后面必有数)
    
    if (c[1] == '\0')//判断是否为操作符:操作符只有一位因此第二位是'\0'
	{
        double numb1, numb2;
        switch (c[0]) //递归是其核心思想
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