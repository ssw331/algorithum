#include <iostream>
using namespace std;

static int coun = 0;
static int s[2] = { 1, 2 }, c[2] = { 1, 3 };

void DFS(int n, int m, int cal = 0, int step = 0)//时间复杂度到了指数
{
    if (cal <= n && step == m)
        coun++;//正好走到m步，记录它
    else if(step <= m && cal <= n)
    {
        DFS(n, m, cal + c[0], step + s[0]);//走1卡1步
        DFS(n, m, cal + c[1], step + s[1]);//走3卡2步
    }
}

int Coun_for_Q1(int m, int n)//时间复杂度大致在O(n, m^2)
{
    int n_cal = m;//总会存在的最优解（即卡路里消耗最小的解——每次只走1步）
    int move = m;//此时有m次行动
    int sum = 1;
    if (m > n || m <= 0 || n <= 0)
        return 0;
    else
    {
        for (int i = 1; i * 2 + n_cal <= n && move >= 1; i++)//遍历所有不超过n卡路里的组合
        {
            move--;//每将1次行动改为2步，就会有一次1步的行动被取消，否则无法维护step数为m
            int comb = 0, comb_1 = 1, comb_2 = 1;
            for (int j = 1; j <= move; j++)
                comb_1 *= j;
            for (int j = 1; j <= (move - i); j++)
                comb_2 *= j;
            comb = comb_1 / comb_2;//计算C(i,move)
            sum += comb;
        }
        return sum;
    }
}

int main() {
    int n, m;
    cin >> m >> n;
    cout << Coun_for_Q1(m, n);

    //DFS(n, m);
    //cout << coun;

    return 0;
}