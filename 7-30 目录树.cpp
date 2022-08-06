/*7-30 目录树 (30 分)
在ZIP归档文件中，保留着所有压缩文件和目录的相对路径和名称。当使用WinZIP等GUI软件打开ZIP归档文件时，可以从这些信息中重建目录的树状结构。请编写程序实现目录的树状结构的重建工作。

输入格式:
输入首先给出正整数N（≤10^4），表示ZIP归档文件中的文件和目录的数量。随后N行，每行有如下格式的文件或目录的相对路径和名称（每行不超过260个字符）：

路径和名称中的字符仅包括英文字母（区分大小写）；
符号“\”仅作为路径分隔符出现；
目录以符号“\”结束；
不存在重复的输入项目；
整个输入大小不超过2MB。
输出格式:
假设所有的路径都相对于root目录。从root目录开始，在输出时每个目录首先输出自己的名字，然后以字典序输出所有子目录，然后以字典序输出所有文件。注意，在输出时，应根据目录的相对关系使用空格进行缩进，每级目录或文件比上一级多缩进2个空格。

输入样例:
7
b
c\
ab\cd
a\bc
ab\d
a\d\a
a\d\z\

输出样例:
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
    map<string, node> paths; //为了更方便地查找子目录节点，且map自带排序功能
    set<string> files;

    node() = default;;

    explicit node(string _name) : name(move(_name)) //这里的_name已经是将实参复制进来后的变量，因此move对实参没有影响
    {};

    bool operator<(const node &b) const
    { return this->name < b.name; }
};

void Output(node &n, int k) //递归输出结果
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
    node root("root"), *pre = &root; //用指针来导航
    for (int j = 0; j < n; ++j)
    {
        cin >> input;
        pre = &root;
        for (int i = 0; i < input.size(); ++i)
        {
            for (i; i < input.size(); ++i) //遇到【\】或超出字符串长度时 截取name
                if (input[i] != '\\')
                    name += input[i];
                else
                    break;
            if (i != input.size())
            {
                pre->paths.insert({name,move(node(name))}); //若name键值已存在则不会更改
                pre = &(pre->paths[name]);
            }
            else
                pre->files.insert(name);
            name.clear();
        }
    }
    Output(root, 0);
}