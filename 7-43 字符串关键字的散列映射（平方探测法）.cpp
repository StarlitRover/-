/*7-43 �ַ����ؼ��ֵ�ɢ��ӳ�� (25 ��)
����һϵ���ɴ�дӢ����ĸ��ɵ��ַ����ؼ��ֺ�����P������λ�������ɢ�к���H(Key)���ؼ���Key�е����3���ַ�ӳ��Ϊ������ÿ���ַ�ռ5λ�����ó���������������ӳ�䵽����ΪP��ɢ�б��С����罫�ַ���AZDEG���볤��Ϊ1009��ɢ�б��У��������Ƚ�26����дӢ����ĸ˳��ӳ�䵽����0~25����ͨ����λ����ӳ��Ϊ3��32^2+4��32+6=3206��Ȼ����ݱ��õ�3206�����Ǹ��ַ�����ɢ��ӳ��λ�á�

������ͻʱ����ƽ��̽�ⷨ�����

�����ʽ:
�����һ�����ȸ�������������N����500����P����2N����С���������ֱ�Ϊ������Ĺؼ����������Լ�ɢ�б�ĳ��ȡ��ڶ��и���N���ַ����ؼ��֣�ÿ�����Ȳ�����8λ������Կո�ָ���

�����ʽ:
��һ�������ÿ���ַ����ؼ�����ɢ�б��е�λ�á����ּ��Կո�ָ�������ĩβ�����ж���ո�

��������1:
4 11
HELLO ANNK ZOE LOLI

�������1:
3 10 4 0

��������2:
6 11
LLO ANNA NNK ZOJ INNK AAA
�������2:
3 0 10 9 6 1*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
    int n, p;
    cin >> n >> p;
    map<int, string> hash;
    string s;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        auto si = s.rbegin();
        int Hkey = 0;
        for (int j = 0; j < 3 && si != s.rend(); ++j, ++si)
            Hkey += (*si - 'A') << j * 5;
        Hkey = Hkey % p;
        if (hash.find(Hkey) == hash.end() || hash[Hkey] == s) //�޳�ͻ���Ѵ�
        {
            hash[Hkey] = s;
            cout << ((i == 0) ? "" : " ") << Hkey;
        }
        else
        {
            int index;
            for (int k = 1; k <= p / 2; ++k)
            {
                index = (Hkey + k * k) % p;
                if (hash.find(index) == hash.end())
                    break;
                index = (Hkey - k * k) % p + (Hkey - k * k < 0 ? p : 0); //ע�⡾?:�����ȼ�������#���⸺����ȡ��Ҳ�Ǹ�����-7/3=-1
                if (hash.find(index) == hash.end())
                    break;
            }
            hash[index] = s;
            cout << ((i == 0) ? "" : " ") << index;
        }
    }
}