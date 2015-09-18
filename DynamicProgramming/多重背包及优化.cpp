///多重背包及优化
/*定义
	描述: 有m种物品和一个容量为V的背包. 第i $(i = 1, 2, \cdots, n)$中物品最多有$n_i$个, 单个价值为$w_i$, 单个体积为$c_i$. 求装入体积和不超过的背包容量的物品的最大价值和为多少.
	状态定义: dp[i][j]表示将前i种物品的体积和为j时的最大价值和.
	转移方程: $dp[i][j] = \min{\{dp[i-1][j - c_i k] + w_i k\}} (0 \leq k \leq n_i)$.
*/
/*朴素做法 $O(V \sum_{i=1}^{m}{n_i})$

*/
/*二进制优化 $O(V \sum_{i=1}^{m}{\log{n_i}})$
	将每种物品分为由$1, 2, 4, \cdots, 2^p, n_i - 2^p$个物品组成的若干堆, 其中p为满足$2^p \leq n_i$的最大值. 再用01背包做即可.
*/
/*单调队列优化 $O(Vm)$
*/
int dp[NUM];
int deq[NUM], top, tail, id[NUM];
int MultiPacket(int m, int c[], int w[], int n[], int V)
{
    memset(dp, 0x3f, sizeof(dp));
    int inf = dp[0], i, j, k, pos;
    dp[0] = 0;
    for(i = 0; i < m; ++i)
    {
        for(j = 0; j < c[i]; ++j)
        {
            top = tail = 0;
            int tot = (V + c[i] - 1) / c[i];
            for(k = 0, pos = j; k <= tot; ++k, pos += c[i])
            {
                if(pos <= V)
                {
                    while(top != tail && deq[top - 1] + (k - id[top - 1]) * w[i] >= dp[pos]) --top;
                    if(dp[pos] != inf) deq[top] = dp[pos], id[top++] = k;
                    if(top != tail) dp[pos] = deq[tail] + (k - id[tail]) * w[i];
                }
                else if(top != tail)
                {
                    dp[V] = min(dp[V], deq[tail] + (k - id[tail]) * w[i]);
                }
                if(top != tail && k - id[tail] == n[i]) ++tail;
            }
        }
    }
    return dp[V];
}
