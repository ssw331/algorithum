#include <iostream>
using namespace std;

static int coun = 0;
static int now_max = 0;
static int s[2] = { 1, 2 }, c[2] = { 1, 3 };

void DFS(int n, int m, int cal = 0, int step = 0)
{
    if (cal <= n && step == m && cal >= now_max)//�����·�����ĺ͵�ǰ���������Ȼ����ż�¼����������
    {
        coun++;//����m������¼
        now_max = cal;//ͬʱ�������·������
    }
    else if (step <= m && cal <= n)
    {
        DFS(n, m, cal + c[1], step + s[1]);//��3��2��
        DFS(n, m, cal + c[0], step + s[0]);//��1��1��
    }
}

int Coun_for_Q2(int m, int n)
{
    int n_cal = m;
    int move = m;
    if (m > n || m <= 0 || n <= 0)
        return 0;
    else
    {
        int i = 1;
        for (; i + n_cal <= n && move >= 1 && move > i; i++)//�������в�����n��·�����ϣ��ҵ��������
        {
            move--;
        }
        if (i + n_cal > n || move <= i)//һ����Ϊi�˳�ѭ������Ҫ��⣬��Ϊforѭ�����߼��ṹ
            i--;
        if (move < 1 && move <= i)
            move++;
        int comb = 0, comb_1 = 1, comb_2 = 1, comb_3 = 1;
        for (int j = 1; j <= move; j++)
            comb_1 *= j;
        for (int j = 1; j <= (move - i); j++)
            comb_2 *= j;
        for (int j = 1; j <= i; j++)
            comb_3 *= j;
        comb = comb_1 / (comb_3 * comb_2);//����C(i,move)
        return comb;
    }
}

int main() {
    int n, m;
    cin >> m >> n;

    cout << "˼·1��" << endl;
    DFS(n, m);
    cout << coun << endl;

    cout << "˼·2��" << endl;
    cout << Coun_for_Q2(m, n) << endl;

    return 0;
}