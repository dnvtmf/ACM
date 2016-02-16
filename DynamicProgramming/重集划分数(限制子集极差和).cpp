/*来源: Group Projects http://codeforces.com/contest/626/problem/F
  题意: 给一个长度为n的数组a, 将其分为若干个group, 每个集合的imbalance为其最大值减最小值, 数组a的imbalance为所有group的imbalance的和, 求使数组的imbalance <= K的划分数(mod 1e9 + 7)
  数据范围: 1 <= n <= 200, 0 <= k <= 1000, 1 <= a[i] <= 500(i = 1, 2, ... , n)
  解决方法: 先将数组排序, 定义dp[i][j][k]为前i个数, 有j个未结束的集合, 当前的总的imbalance值为k的方案数
  使用滚动数组, 时间复杂度 $O(n^2 K)$
*/
const int mod = 1e9 + 7;
int dp[2][110][1100];
#define ADD(x, y) {if((x += (y)) >= mod) x -= mod;}
int solve(int n, int K, int a[])
{
	a[0] = 0;
    sort(a + 1, a + 1 + n);
    int now = 0, nxt = 1;
    memset(dp[now], 0, sizeof(dp[now]));
    dp[now][0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        memset(dp[nxt], 0, sizeof(dp[nxt]));
        for(int j = 0; j + j <= n; ++j)//number of groups without close
        {
            for(int k = 0; k <= K; ++k)//now value of imbalance
            {
                if((val = dp[now][j][k]) == 0) continue;
                int w = k + j * (a[i] - a[i - 1]);//w is now total of imbalance
                if(w > K) continue;
                ADD(dp[nxt][j + 1][w], val);//begin
                if(j > 0) ADD(dp[nxt][j][w], 1ll * val * j % mod);//middle
                if(j > 0) ADD(dp[nxt][j - 1][w], 1ll * val * j % mod); //end
                ADD(dp[nxt][j][w], val); //new group only have this
            }
        }
        swap(now, nxt);
    }
    int ans = 0;
    for(int i = 0; i <= K; ++i)
        ADD(ans, dp[now][0][i]);
    return ans;
}
