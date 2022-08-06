/*7-17 ��ŵ���ķǵݹ�ʵ�� (25 ��)
������ջ�Էǵݹ飨ѭ������ʽ��⺺ŵ�������⣨n, a, b, c��������N�����Ӵ���ʼ�������Ϊ��a����ͨ�������������Ϊ��b�����ƶ���Ŀ���������Ϊ��c����������֤ÿ���ƶ����Ϻ�ŵ�������Ҫ��

�����ʽ:
����Ϊһ��������N������ʼ���ϵ�������

�����ʽ:
ÿ���������ƶ���ռһ�У�����1 -> ��2�ĸ�ʽ�����*/

#include <iostream>
#include <stack>

using namespace std;

class single
{
public:
    char start;
    char end;
    int n;

    single(char s, char e, int n) :
            start(s), end(e), n(n)
    {};
};

int main()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "a -> c" << endl;
        exit(0);
    }
    stack<single> info;
    info.push(single('a', 'c', n));
    while (!info.empty())
    {
        auto s = info.top();
        info.pop();
        if (s.n == 1)
            printf("%c -> %c\n", s.start, s.end); //cout����һֱ���ڵ��ĸ����Ե�.......
        else
        {
            char r = (char) ('a' + 'b' + 'c' - s.start - s.end);
            info.push(single(r, s.end, s.n - 1));
            info.push(single(s.start, s.end, 1));
            info.push(single(s.start, r, s.n - 1));
        }
    }
}
//���ⲻ�ѣ�ֻ��cout�����⡭