///ST表(Sparse Table)
//对静态数组，查询任意区间[l, r]的最大（小）值
// 预处理O(nlog n), 查询O(1)
#define MAX 10000
int st[MAX][22];//st表 -- st[i][j]表示从第i个元素起，连续2^j个元素的最大（小）值
int Log2[MAX];//对应于数x中最大的是2的幂的区间长度， k = floor(log2(R - L + 1))
void pre_ST(int n, int ar[])//n 数组长度， ar 数组
{
    int i, j;
    Log2[1] = 0;
    for(i = 2; i <= n; i++) Log2[i] = Log2[i>>1] + 1;
    for(i = n - 1; i >= 0; i--)
    {
        st[i][0] = ar[i];
        for(j = 1; i + (1 << j) <= n; j++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}
int query(int l, int r)
{
    int k = Log2[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}
