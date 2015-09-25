///最大流 maximum flow
//最大流最小割定理 : 最大流 = 最小割
///FF算法 Ford-Fulkerson算法 $O(F|E|)$ F为最大流量
//1. 初始化：原边容量不变，回退边容量为0，max_flow = 0
//2. 在残留网络中找到一条从源S到汇T的增广路，找不到得到最大流max_flow
//3. 增广路中找到瓶颈边，max_flow加上其容量
//4. 增广路中每条边减去瓶颈边容量，对应回退边加上其容量
struct edge
{
    int to, cap, rev;
};

vector <edge> G[MAXV];
bool used[MAXV];

void add_edge(int from, int to, int cap)
{
    G[from].push_back((edge) {to, cap, G[to].size()});
    G[to].push_back((edge) {from, 0, G[from].size() - 1});
}

//dfs寻找增广路
int dfs(int v, int t, int f)
{
    if(v == t)
        return f;
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++)
    {
        edge &e = G[v][i];
        if(!used[e.to] && e.cap > 0)
        {
            int d = dfs(e.to, t , min(f, e.cap));
            if(d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

//求解从s到t的最大流
int max_flow(int s, int t)
{
    int flow = 0;
    for(;;)
    {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if(f == 0)
            return flow;
        flow += f;
    }
}
///Dinic算法 $O(|E| \cdot |V|^2)$
//似乎比链式前向星快
struct edge {int to, cap, rev;};
vector <edge> G[MAXV];
int level[MAXV];
int iter[MAXV];
void init()
{
    for(int i = 0; i < MAXV; i++)
        G[i].clear();
}
void add_edge(int from, int to, int cap)
{
    G[from].push_back((edge) {to, cap, (int) G[to].size()});
    G[to].push_back((edge) {from, 0, (int) G[from].size() - 1 });
}
bool bfs(int s, int t)
{
    memset(level, -1, sizeof(level));
    queue <int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        int v = que.front();
        que.pop();
        for(int i = 0; i < (int)G[v].size(); i++)
        {
            edge &e = G[v][i];
            if(e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int t, int f)
{
    if(v == t) return f;
    for(int &i = iter[v]; i < (int)G[v].size(); i++)
    {
        edge &e = G[v][i];
        if(e.cap > 0 && level[v] < level[e.to])
        {
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0, cur_flow;
    while(bfs(s, t))
    {
        memset(iter, 0, sizeof(iter));
        while((cur_flow = dfs(s, t, INF)) > 0) flow += cur_flow;
    }
    return flow;
}
///SAP算法 $O(|E| \cdot |V|^2)$
#define MAXV 1000
#define MAXE 10000
struct edge
{
    int cap, next, to;
} e[MAXE * 2];
int head[MAXV], tot_edge;
void init()
{
    memset(head, -1, sizeof(head));
    tot_edge = 0;
}
void add_edge(int u, int v, int cap)
{
    e[tot_edge] = (edge) {cap, head[u], v};
    head[u] = tot_edge++;
}
int V;
int numh[MAXV];//用于GAP优化的统计高度数量数组
int h[MAXV];//距离标号数组
int pree[MAXV], prev[MAXV];//前驱边与结点
int SAP_max_flow(int s, int t)
{
    int i, flow = 0, u, cur_flow, neck = 0, tmp;
    memset(h, 0, sizeof(h));
    memset(numh, 0, sizeof(numh));
    memset(prev, -1, sizeof(prev));
    for(i = 1; i <= V; i++)//从1开始的图，初识化为当前弧的第一条临接边
        pree[i] = head[i];
    numh[0] = V;
    u = s;
    while(h[s] < V)
    {
        if(u == t)
        {
            cur_flow = INT_MAX;
            for(i = s; i != t; i = e[pree[i]].to)
            {
                if(cur_flow > e[pree[i]].cap)
                {
                    neck = i;
                    cur_flow = e[pree[i]].cap;
                }
            }//增广成功，寻找"瓶颈"边
            for(i = s; i != t; i = e[pree[i]].to)
            {
                tmp = pree[i];
                e[tmp].cap -= cur_flow;
                e[tmp ^ 1].cap += cur_flow;
            }//修改路径上的边容量
            flow += cur_flow;
            u = neck;//下次增广从瓶颈边开始
        }
        for(i = pree[u]; i != -1; i = e[i].next)
            if(e[i].cap && h[u] == h[e[i].to] + 1)
                break;//寻找可行弧
        if(i != -1)
        {
            pree[u] = i;
            prev[e[i].to] = u;
            u = e[i].to;
        }
        else
        {
            if(0 == --numh[h[u]])break;//GAP优化
            pree[u] = head[u];
            for(tmp = V, i = head[u]; i != -1; i = e[i].next)
                if(e[i].cap)
                    tmp = min(tmp, h[e[i].to]);
            h[u] = tmp + 1;
            ++numh[h[u]];
            if(u != s) u = prev[u];//从标号并且从当前结点的前驱重新增广
        }
    }
    return flow;
}

///EK算法 $O(|V| \cdot |E|^2)$
//bfs寻找增广路
const int MAXV = 210;
int g[MAXV][MAXV], pre[MAXV];
int n;
bool vis[MAXV];
bool bfs(int s, int t)
{
    queue <int> que;
    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    que.push(s);
    vis[s] = true;
    while(!que.empty())
    {
        int u = que.front();
        if(u == t) return true;
        que.pop();
        for(int i = 1; i <= n; i++)
            if(g[u][i] && !vis[i])
            {
                vis[i] = true;
                pre[i] = u;
                que.push(i);
            }
    }
    return false;
}
int EK_max_flow(int s, int t)
{
    int u, max_flow = 0, minv;
    while(bfs(s, t))
    {
        minv = INF;
        u = t;
        while(pre[u] != -1)
        {
            minv = min(minv, g[pre[u]][u]);
            u = pre[u];
        }
        ans += minv;
        u = t;
        while(pre[u] != -1)
        {
            g[pre[u]][u] -= minv;
            g[u][pre[u]] += minv;
            u = pre[u];
        }
    }
    return max_flow;
}
