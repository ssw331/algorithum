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
        for (; i * 2 + n_cal <= n && move >= 1; i++)//�������в�����n��·������
        {
            move--;
        }
        if (i * 2 + n_cal > n)
            i--;
        if (move < 1)
            move++;
        int comb = 0, comb_1 = 1, comb_2 = 1;
        for (int j = 1; j <= move; j++)
            comb_1 *= j;
        for (int j = 1; j <= (move - i); j++)
            comb_2 *= j;
        comb = comb_1 / comb_2;//����C(i,m)
        return comb;
    }
}

int main() {
    int n, m;
    cin >> m >> n;
    cout << Coun_for_Q2(m, n);

    //DFS(n, m);
    //cout << coun;

    return 0;
}