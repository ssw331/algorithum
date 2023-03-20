#include <iostream>
using namespace std;

static int coun = 0;
static int now_max = 0;
static int s[2] = { 1, 2 }, c[2] = { 1, 3 };

void DFS(int n, int m, int cal = 0, int step = 0)
{
    if (cal <= n && step == m && cal >= now_max)//如果卡路里消耗和当前最大消耗相等或更大才记录，否则无视
    {
        coun++;//正好m步，记录
        now_max = cal;//同时更新最大卡路里消耗
    }
    else if (step <= m && cal <= n)
    {
        DFS(n, m, cal + c[1], step + s[1]);//走3卡2步
        DFS(n, m, cal + c[0], step + s[0]);//走1卡1步
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
        for (; i * 2 + n_cal <= n && move >= 1; i++)//遍历所有不超过n卡路里的组合
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
        comb = comb_1 / comb_2;//计算C(i,m)
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