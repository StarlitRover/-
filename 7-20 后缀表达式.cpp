/*7-20 表达式转换 (25 分)
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。

输入格式:
输入在一行中给出不含空格的中缀表达式，可包含+、-、*、\以及左右括号()，表达式不超过20个字符。

输出格式:
在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。

输入样例:
2+3*(7-4)+8/4

输出样例:
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
    bool isNum = false, flag = true;//isNum区分前一个字符是不是数字,flag标记是否为输出开头以确定是否需要输出空格
    for (auto &s: expr)
    {
        if (s >= '0' && s <= '9' || s == '.')
        {
            cout << (flag || isNum ? (flag = false, "") : " ") << s;
            isNum = true;
        }
        else if (s == ')')
        {
            isNum = true;//')'后面只可能是运算符因此考虑到作为运算数开头的'+' '-'识别问题需要将isNum置为true,否则会将')'后面的'+' '-'识别为运算数的符号位
            while (opr.top() != '(')
            {
                cout << " " << opr.top();
                opr.pop();
            }
            opr.pop();
        }
        else
        {
            if (!isNum && (s == '-' || s == '+')) //判断是否为运算数的符号位
            {
                cout << (flag ? "" : " ") << (s == '+' ? "" : "-"); //注意输出的时候需要忽略作为运算数符号位的'+'
                isNum = true;
                continue;
            }
            isNum = false;
            while (!opr.empty() && opr.top() != '(' && priority(opr.top()) >= priority(s))
			//之所以是>=是因为同等运算符是按照从左至右的顺序计算的,因此需要把先前读进的同等级运算符输出
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
1.这里根据'+' '-'前面一位是否为运算符来判断它们是符号位还是运算符，但其中有一种情况例外')'
2.输入的算式中正数前可能含'+'，然而输出的正数不可以含有'+'