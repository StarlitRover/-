/*7-29 修理牧场 (25 分)
农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要N块木头，每块木头长度为整数L_i
?
 个长度单位，于是他购买了一条很长的、能锯成N块的木头，即该木头的长度是L_i的总和。

但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就设酬金等于所锯木头的长度。例如，要将长度为20的木头锯成长度为8、7和5的三段，第一次锯木头花费20，将木头锯成12和8；第二次锯木头花费12，将长度为12的木头锯成7和5，总花费为32。如果第一次将木头锯成15和5，则第二次锯木头花费15，总花费为35（大于32）。

请编写程序帮助农夫计算将木头锯成N块的最少花费。

输入格式:
输入首先给出正整数N（≤10^4），表示要将木头锯成N块。第二行给出N个正整数（≤50），表示每段木块的长度。

输出格式:
输出一个整数，即将木头锯成N块的最少花费。

输入样例:
8
4 5 1 2 1 3 1 1

输出样例:
49*/

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<>> log; //priority_queue<Type, Container, Functional>
    int n, tmp;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> tmp;
        log.push(tmp);
    }
    int sum = 0;
    while (log.size() != 1)
    {
        int a = log.top();
        log.pop();
        int b = log.top();
        log.pop();
        sum += a + b;
        log.push(a + b);
    }
    cout << sum;
}
//本问的本质事实上是Huffman Tree，每一段木头即为一个叶子节点，每一个叶子节点的路径代表了这段长度被计算了几次，所以我们只需构造出一个Huffman Tree即可