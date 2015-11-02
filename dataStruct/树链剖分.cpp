///树链剖分 Heavy-Light Decomposition
//将一个树划分为若干个不相交的路径, 使每个结点仅在一条路径上.
//满足: 从结点u到v最多经过$\log{N}$条路径, 以及$\log{N}$条不在路径上的边.
//采用启发式划分, 即某结点选择与子树中结点数最大的儿子划分为一条路径.
//时间复杂度: 用其他数据结构来维护每条链, 复杂度为所选数据结构乘以 $\log{N}$.
//用split()来进行树链剖分, 其中使用bfs进行划分操作. 对于每一个结点v, 找到它的size最大的子结点u. 如果u不存在, 那么给v分配一条新的路径, 否则v就延续u所属的路径.
//查询两个结点u, v之间的路径是, 首先判断它们是否属于同一路径. 如果不是, 选择所属路径顶端结点h的深度较大的结点, 不妨假设是v, 查询v到h, 并令v = father[h]继续查询, 直至u, v属于同一路径. 最后在这条路径上查询并返回.
/*
sz[u]: 结点u的子树的结点数量
fa[u]: 结点u的父结点
dep[u]: 结点u在树中的深度
belong[u]: 结点u所在剖分链的编号
id[u]: 结点u在其路径中的编号, 由深入浅编号
start[p]: 链p的第一个结点
len[p]: 链p的长度
total: 划分链的数量
dfn: 树中结点的遍历顺序
*/
struct edge
{
    int next, to;
} e[NUM << 1];
int head[NUM], tot;
void init()
{
    memset(head, -1, sizeof(head));
    tot = 0;
}
void add_edge(int u, int v)
{
    e[tot] = (edge) {head[u], v};
    head[u] = tot++;
}
int sz[NUM], fa[NUM], dep[NUM];
int belong[NUM], id[NUM];
int start[NUM], len[NUM], total;
int dfn[NUM];
bool vis[NUM];
void split()
{
    int tail = 0,  top = 0;
    dep[dfn[top++] = 1] = 0;
    fa[1] = 0;
    while(tail < top)
    {
        int u = dfn[tail++];
        for(int i = head[u]; ~i; i = e[i].next)
            if(e[i].to != fa[u])
            {
                dep[dfn[top++] = e[i].to] = dep[u] + 1;
                fa[e[i].to] = u;
            }
    }
    memset(vis, 0, sizeof(vis));
    total = 0;
    while(top)
    {
        int u = dfn[--top], v = -1;
        sz[u] = 1;
        for(int i = head[u]; ~i; i = e[i].next)
            if(vis[e[i].to])
            {
                sz[u] += sz[e[i].to];
                if(v == -1 || sz[e[i].to] > sz[v])
                    v = e[i].to;
            }
        if(v == -1)
        {
            id[u] = len[++total] = 1;
            belong[start[total] = u] = total;
        }
        else
        {
            id[u] = ++len[belong[u] = belong[v]];
            start[belong[u]] = u;
        }
        vis[u] = true;
    }
}
void Query(int u, int v)
{
    int x = belong[u], y = belong[v];
    while(x != y)
    {
        int& w = dep[start[x]] > dep[start[y]] ? u : v;
        int& z = dep[start[x]] > dep[start[y]] ? x : y;
        //query[z][id[w]-->len[z]]
        w = fa[start[z]];
        z = belong[w];
    }
    u = id[u], v = id[v];
    if(u > v) swap(u, v);
    //query [x][u-->v]
}
