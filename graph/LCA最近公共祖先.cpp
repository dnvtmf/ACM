///最近公共祖先LCA Least Common Ancestors
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
        if(!vis[e[i].to])
        {
            LCA(e[i].to);
            fa[e[i].to] = u;
        }
    for(int i = qh[u]; i != -1; i = qe[i].next)
        if(vis[qe[i].to])
        {
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
struct node
{
    int u;//记录经过的结点
    int depth;//记录当前结点的深度
} vs[2 * MAXV];
bool operator < (node a, node b) {return a.depth < b.depth;}
int id[MAXV];//记录第一次经过点u时的dfn序号
void dfs(int u, int fa, int dep, int &k)
{
    vs[k] = (node) {u, dep};
    id[u] = k++;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].to != fa)
        {
            dfs(e[i].to, u, dep + 1, k);
            vs[k++] = (node) {u, dep};
        }
}
//RMQ
//动态查询id[u] 到 id[v] 之间的depth最小的结点
//ST表
int Log2[MAXV * 2];
node st[MAXV * 2][32];
void pre_st(int n, node ar[])
{
    Log2[1] = 0;
    for(int i = 2; i <= n; i++) Log2[i] = Log2[i >> 1] + 1;
    for(int i = n - 1; i >= 0; i--)
    {
        st[i][0] = ar[i];
        for(int j = 1; i + (1 << j) <= n; j++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
    }
}
int query(int l, int r)
{
    int k = Log2[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]).u;
}

void lca_init()
{
    int k = 0;
    dfs(1, -1, 0, k);
    pre_st(k, vs);
}

int LCA(int u, int v)
{
    u = id[u], v = id[v];
    if(u > v) swap(u, v);
    return query(u, v);
}
