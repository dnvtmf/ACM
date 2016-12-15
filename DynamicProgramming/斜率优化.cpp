/*
斜率优化
形如 $dp[n] = \min{\{ f(i) + g(i) \times h(n) \}} + c(n)$ 的dp可以使用斜率优化, 将时间复杂度从 $O(n^2)$ 降到$O(n)$
上述dp方程构造成另一个形式: $z = y + x \times k$, 其中$k = h(n), x = g(i), y = f(i), z = dp[n] - c(n)$, 问题变为在二维平面的一系列点(x, y) 中寻找一个点使经过这个点且斜率为k的直线在y轴的截距最小. 这样的点一定在下凸壳上.
如果x是递增或递减的, 那么可以使用 Graham 算法来维护下凸壳.
同时如果k是有序的, 可以使用单调队列优化. [Codeforces 351 Levels and Regions] (http://codeforces.com/contest/674/problem/C)
如果k是无序的, 那么在下凸壳中二分查找答案.
*/
P stk[NUM];
int top;
LL cross(P a, P b, P c)
{
	return (b.FI - a.FI) * (b.SE - c.SE) - (b.SE - a.SE) * (b.FI - c.FI);
}
inline LL calc(P &a, int x)
{
	return a.FI * x + a.SE;
}
int main()
{
	for(int i = 0; i < n; ++i) {
		LL dp = c(i);
		//二分查找答案
		if(top != 0) {
			if(top == 1) {
				dp += calc(stk[0], h(i));
			}
			else {
				int l = 1, r = p - 1, mid, res = 1;
				while(l <= r) {
					mid = (l + r) >> 1;
					LL tmp = calc(stk[mid], h[i]) - calc(stk[mid-1], h[i]);
					if(tmp >= 0) {
						res = mid;
						l = mid + 1;
					}
					else
						r = mid - 1;
				}
				if(res == 1) {
					dp += min(calc(stk[1], h[i]), calc(stk[i], h[i]));

				}
				else {
					dp += calc(stk[res], h[i]);
				}
			}
		}
		P tmp(g(i), f(i));//要求第一维x递增, 第二维y有序
		while(top > 1 && cross(stk[top - 2], tmp, stk[top - 1]) >= 0) --top;
		stk[top++] = tmp;
	}
	return 0;
}
