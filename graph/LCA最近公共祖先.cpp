///最近公共祖先LCA Least Common Ancestors
//较为暴力的做法:
/*
预处理: dfs深度搜索, 求出每个结点的深度.
单个查询: 查询(u, v)的LCA, 不断寻找深度较大的那个结点的父亲结点, 直至到达同一结点为止.
时间复杂度: 预处理: $O(|V|)$, 单次查询: $O(n)$
*/
//Tarjian的离线算法 $O(n+q)$
struct edge {int next, to, lca;};
//由要查询的<u,v>构成的图
edge qe[MAXE * 2];
int qh[MAXV], qtot;
//原图
edge e[MAXE * 2]
int head[MAXV], tot;
//并查集
int fa[MAXV];
inline int find(int x)
{
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
bool vis[MAXV];
void LCA(int u)
{
	vis[u] = true;
	fa[u] = u;
	for(int i = head[u]; i != -1; i = e[i].next)
		if(!vis[e[i].to]) {
			LCA(e[i].to);
			fa[e[i].to] = u;
		}
	for(int i = qh[u]; i != -1; i = qe[i].next)
		if(vis[qe[i].to]) {
			qe[i].lca = find(eq[i].to);
			eq[i ^ 1].lca = qe[i].lca;//无向图, 入边两次
		}
}

//RMQ的在线算法 $O(n \log{n})$
/*算法描述:
	dfs扫描一遍整棵树, 记录下经过的每一个结点(每一条边的两个端点)和结点的深度(到根节点的距离),一共2n-1次记录
	再记录下第一次扫描到结点u时的序号
	RMQ: 得到dfs中从u到v路径上深度最小的结点, 那就是LCA[u][v].
*/
struct lca_node {
	int u, dep;
	inline bool operator < (const lca_node &b) const {return dep < b.dep;}
};
struct __LCA {
	lca_node st[MAXE][23];
	int id[MAXV], Lg2[MAXE], cnt;
	__LCA()
	{
		Lg2[1] = 0;
		for(int i = 2 ; i < MAXE; ++i) Lg2[i] = Lg2[i >> 1] + 1;
	}
	void st_init()
	{
		cnt = 0;
		dfs(1, -1, 0);
		for(int i = cnt - 1; i >= 0; --i) {
			for(int j = 1; i + (1 << j) <= cnt; ++j)
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	inline int LCA(int u, int v)
	{
		u = id[u], v = id[v];
		if(u > v) swap(u, v);
		int k = Lg2[v - u + 1];
		return min(st[u][k], st[v - (1 << k) + 1][k]).u;
	}

	void dfs(int u, int fa, int dep)
	{
		st[id[u] = cnt++][0] = (lca_node) {u, dep};
		for(int i = head[u]; ~i; i = e[i].next) {
			if(e[i].to == fa) continue;
			dfs(e[i].to, u, dep + 1);
			st[cnt++][0] = (lca_node) {u, dep};
		}
	}
} lca;
