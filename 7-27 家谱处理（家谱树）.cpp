/*7-27 家谱处理 (30 分)
人类学研究对于家族很感兴趣，于是研究人员搜集了一些家族的家谱进行研究。实验中，使用计算机处理家谱。为了实现这个目的，研究人员将家谱转换为文本文件。下面为家谱文本文件的实例：

John
  Robert
    Frank
    Andrew
  Nancy
    David
家谱文本文件中，每一行包含一个人的名字。第一行中的名字是这个家族最早的祖先。家谱仅包含最早祖先的后代，而他们的丈夫或妻子不出现在家谱中。每个人的子女比父母多缩进2个空格。以上述家谱文本文件为例，John这个家族最早的祖先，他有两个子女Robert和Nancy，Robert有两个子女Frank和Andrew，Nancy只有一个子女David。

在实验中，研究人员还收集了家庭文件，并提取了家谱中有关两个人关系的陈述语句。下面为家谱中关系的陈述语句实例：

John is the parent of Robert
Robert is a sibling of Nancy
David is a descendant of Robert
研究人员需要判断每个陈述语句是真还是假，请编写程序帮助研究人员判断。

输入格式:
输入首先给出2个正整数N（2≤N≤100）和M（≤100），其中N为家谱中名字的数量，M为家谱中陈述语句的数量，输入的每行不超过70个字符。

名字的字符串由不超过10个英文字母组成。在家谱中的第一行给出的名字前没有缩进空格。家谱中的其他名字至少缩进2个空格，即他们是家谱中最早祖先（第一行给出的名字）的后代，且如果家谱中一个名字前缩进k个空格，则下一行中名字至多缩进k+2个空格。

在一个家谱中同样的名字不会出现两次，且家谱中没有出现的名字不会出现在陈述语句中。每句陈述语句格式如下，其中X和Y为家谱中的不同名字：

X is a child of Y
X is the parent of Y
X is a sibling of Y
X is a descendant of Y
X is an ancestor of Y
输出格式:
对于测试用例中的每句陈述语句，在一行中输出True，如果陈述为真，或False，如果陈述为假。

输入样例:
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

输出样例:
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
    parent[name] = ""; //【最后一个测试点】绝不能让第一个人(John)的父节点指向自己，否则当出现"Robert is a sibling of John"的判断语句时便会出错
    cin.get();
    for (int i = 0; i < n - 1; ++i)
    {
        int cnt = 0;
        while ((c = cin.get()) == ' ')
            ++cnt;
        getline(cin, name); //【第三个测试点】不能使用cin>>name，否则当该行只有一个字符时，cin会自动换行读取name！
        name = c + name;
        parent[name] = rank[cnt - 2]; //直接用名字前空格的个数代表其优先级（辈分）
        rank[cnt] = name;   
//rank只会记住某一辈最后出现的那个人，根据家谱的输入方式我们知道只有某一辈最后出现的那个人还有可能成为其他人的父节点，所以可以直接覆盖
//getline函数已经将行末尾的回车符读取，因此这里不需要cin.get()
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
//这个问题在字符处理方面也是一个难点,rank是本问解的一个亮点