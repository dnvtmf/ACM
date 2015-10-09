///树的最小支配集, 最小点覆盖, 最大独立集
/*最小支配集V': 对于图G=(V, E)中的任一顶点u, 要么属于集合V', 要么与V'中的顶点相邻, 且|V'|最小
最小点覆盖V': 对于图G=(V, E)中的任一边<u, v>, 要么u属于V', 要么v属于V', 且|V'|最小.
最大独立集V': 对于图G=(V, E)中取出尽可能多的点使这些点间没有边相连
对任意图G, 无多项式时间解法, 对树有两种解法
*/
/*贪心法 $O(n)$
对树进行深度优先遍历, 反遍历序中:
最小支配集: 对即不属于支配集, 也不与支配集相邻的顶点, 如果父节点不属于支配集, 将其父节点加入支配集
最小点覆盖: 当前结点和其父节点都不属于覆盖集, 将父节点加入覆盖集, 标记当前点和父节点为已覆盖
最大独立集: 当前结点未被覆盖, 把该结点加入独立集, 标记当前点和父节点为已覆盖.

默认根结点的父节点为自己, 最小支配集和最大独立集需检查根结点是否满足贪心条件.
*/

//DFS
int n, m;
int fa[MAXV];
int vis[MAXV];
int dfn[MAXV], now;
void dfs(int u)
{
    dfn[now++] = u;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(!vis[e[i].to])
        {
            vis[e[i].to] = true;
            fa[e[i].to] = u;
            dfs(e[i].to);
        }
}

int greedy()
{
	bool s[MAXV] = {};
	bool res[MAXV] = {};
	int ans = 0;
	for(int i = n - 1; i >= 0; --i)
	{
		int t = dfn[i];
		//最小支配集
		if(!s[t])
		{
			if(!res[p[t]])
			{
				s[p[t]] = true;
				++ans;
			}
			s[t] = true;
			s[p[t]] = true;
			s[p[p[t]]] = true;
		}
		//最小点覆盖
		if(!s[t] && !s[p[t]])
		{
			res[p[t]] = true;
			++ans;
			s[t] = s[p[t]] = true;
		}
		//最大独立集
		if(!s[t])
		{
			res[t] = true;
			++ans;
			s[t] = s[p[t]] = true;
		}
	}
	return ans;
}
//dp $O(n)$
//最小支配集
void DP(int u, int p)
{
	dp[u][2] = 0;
	dp[u][0] = 1;
	bool s = false;
	int sum = 0, inc = INF;
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].to;
		if(v == p) continue;
		DP(v, u);
		dp[u][0] += min(dp[v][0], min(dp[v][1], dp[v][2]));
		if(dp[v][0] <= dp[v][1])
		{
			sum += dp[v][0];
			s = true;
		}
		else
		{
			sum += dp[v][1];
			inc = min(inc, dp[v][0] - dp[v][1]);
		}
		if(dp[v][1] != INF && dp[u][2] != INF)
			dp[u][2] += dp[v][1];
		else
			dp[u][2] = INF;
	}
	if(inc == INF && !s) dp[u][1] = INF;
	else
	{
		dp[u][1] = sum;
		if(!s) dp[u][1] += inc;
	}
}
//最小点覆盖
void DP(int u, int p)
{
	dp[u][0] = 1;
	dp[u][1] = 0;
	for(int i = head[u]; ~i; i = e[i].next)
	{
		v = e[i].to;
		if(v == p) continue;
		DP(v, u);
		dp[u][0] += min(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}
//最大独立集
void DP(int u, int p)
{
	dp[u][0] = 1;
	dp[u][1] = 0;
	for(int i = head[u]; ~i; i = e[i].next)
	{
		v = e[i].to;
		if(v == p) continue;
		DP(v, u);
		dp[u][0] += dp[v][1];
		dp[u][1] += max(dp[v][0], dp[v][1]);
	}
}
