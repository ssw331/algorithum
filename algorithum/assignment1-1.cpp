#include <iostream>
using namespace std;

static int coun = 0;
static int s[2] = { 1, 2 }, c[2] = { 1, 3 };

void DFS(int n, int m, int cal = 0, int step = 0)//ʱ�临�Ӷȵ���ָ��
{
    if (cal <= n && step == m)
        coun++;//�����ߵ�m������¼��
    else if(step <= m && cal <= n)
    {
        DFS(n, m, cal + c[0], step + s[0]);//��1��1��
        DFS(n, m, cal + c[1], step + s[1]);//��3��2��
    }
}

int Coun_for_Q1(int m, int n)//ʱ�临�Ӷȴ�����O(n, m^2)
{
    int n_cal = m;//�ܻ���ڵ����Ž⣨����·��������С�Ľ⡪��ÿ��ֻ��1����
    int move = m;//��ʱ��m���ж�
    int sum = 1;
    if (m > n || m <= 0 || n <= 0)
        return 0;
    else
    {
        for (int i = 1; i + n_cal <= n && move >= 1 && move > i; i++)//�������в�����n��·�����ϣ���Ϊ��һ�������ˣ�����n_calҲÿ�μ�����һ
        {
            move--;//ÿ��1���ж���Ϊ2�����ͻ���һ��1�����ж���ȡ���������޷�ά��step��Ϊm
            int comb = 0, comb_1 = 1, comb_2 = 1, comb_3 = 1;
            for (int j = 1; j <= move; j++)
                comb_1 *= j;
            for (int j = 1; j <= (move - i); j++)
                comb_2 *= j;
            for (int j = 1; j <= i; j++)
                comb_3 *= j;
            comb = comb_1 /(comb_3 * comb_2);//����C(i,move)
            sum += comb;
        }
        return sum;
    }
}

int main() {
    int n, m;
    cin >> m >> n;

    cout << "˼·1��" << endl;
    DFS(n, m);
    cout << coun << endl;

    cout << "˼·2��" << endl;
    cout << Coun_for_Q1(m, n) << endl;

    return 0;
}