///最大流 maximum flow
//最大流最小割定理: 最大流 = 最小割
//常数比较: 高标推进 < SAP(gap) < dinic < sap < bfs + ek
///FF算法 Ford-Fulkerson算法 $O(F|E|)$ F为最大流量
//1. 初始化：原边容量不变，回退边容量为0，max_flow = 0
//2. 在残留网络中找到一条从源S到汇T的增广路，找不到得到最大流max_flow
//3. 增广路中找到瓶颈边，max_flow加上其容量
//4. 增广路中每条边减去瓶颈边容量，对应回退边加上其容量

struct edge {int next, to, cap;} e[MAXE];
int head[MAXV], tot;
void gInit() {memset(head, -1, sizeof(head)); tot = 0;}
void add_edge(int u, int v, int cap)
{
    e[tot] = (edge) {head[u], v, cap}; head[u] = tot++;
    e[tot] = (edge) {head[v], u, 0}; head[v] = tot++;
}
int used[MAXV], time_stamp;
int dfs(int u, int t, int f)
{
    if(u == t) return f;
    used[u] = time_stamp;
    for(int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to;
        if(used[v] != time_stamp && e[i].cap > 0)
        {
            int d = dfs(v, t, min(f, e[i].cap));
            if(d > 0)
            {
                e[i].cap -= d;
                e[i ^ 1].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0, cur_flow;
    memset(used, 0, sizeof(used));
    time_stamp = 0;
    for(;;)
    {
        ++time_stamp;
        if((cur_flow = dfs(s, t, INF)) == 0)
            return flow;
        flow += cur_flow;
    }
}
///Dinic算法 $O(|E| \cdot |V|^2)$
//似乎比链式前向星快
struct edge {int to, cap, rev;};
vector <edge> G[MAXV];
int level[MAXV];
int iter[MAXV];
void gInit()
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
            edge& e = G[v][i];
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
    for(int& i = iter[v]; i < (int)G[v].size(); i++)
    {
        edge& e = G[v][i];
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
///SAP(Shortest Augmenting Paths)算法 $O(|E| \cdot |V|^2)$
const int MAXV = 1000 + 10, MAXE = MAXV * MAXV;
struct edge {int next, to, cap;} e[MAXE];
int head[MAXV], tot, V;
void gInit() {memset(head, -1, sizeof(head)); tot = 0; V = 0;}
void add_edge(int u, int v, int cap)
{
    e[tot] = (edge) {head[u], v, cap}; head[u] = tot++;
    e[tot] = (edge) {head[v], u, 0}; head[v] = tot++;
}

int h[MAXV];//距离标号数组
int numh[MAXV];//用于GAP优化的统计高度数量数组
int iter[MAXV];//当前弧优化
int Prev[MAXV];//前驱结点
int sap(int s, int t)
{
    memset(h, 0, sizeof(h));
    memset(numh, 0, sizeof(numh));
    memset(Prev, -1, sizeof(Prev));
    for(int i = 0; i < V; ++i) iter[i] = head[i];//从0开始的图，初始化为第一条邻接边
    numh[0] = V;
    int u = s, max_flow = 0, i;
    while(h[s] < V)
    {
        if(u == t)//增广成功
        {
            int flow = INF, neck = -1;
            for(u = s; u != t; u = e[iter[u]].to)
            {
                if(flow > e[iter[u]].cap)
                {
                    neck = u;
                    flow = e[iter[u]].cap;
                }
            }//寻找"瓶颈"边
            for(u = s; u != t; u = e[iter[u]].to)
            {
                e[iter[u]].cap -= flow;
                e[iter[u] ^ 1].cap += flow;
            }//修改路径上的边容量
            max_flow += flow;
            u = neck;//下次增广从瓶颈边之前的结点开始
        }
        //寻找可行弧
        for(i = iter[u]; ~i; i = e[i].next)
            if(e[i].cap > 0 && h[u] == h[e[i].to] + 1)
                break;
        if(i != -1)
        {
            iter[u] = i;
            Prev[e[i].to] = u;
            u = e[i].to;
        }
        else
        {
            if(0 == --numh[h[u]]) break;//GAP优化
            iter[u] = head[u];
            for(h[u] = V, i = head[u]; ~i; i = e[i].next)
            {
                if(e[i].cap > 0)
                {
                    h[u] = min(h[u], h[e[i].to]);
                }
            }
            ++h[u];
            ++numh[h[u]];
            if(u != s) u = Prev[u];//从标号并且从当前结点的前驱重新增广
        }
    }
    return max_flow;
}

///EK(Edmonds_Karp)算法 $O(|V| \cdot |E|^2)$
//bfs寻找增广路
const int MAXV = 210;
int n, m, g[MAXV][MAXV], prev[MAXV];
bool vis[MAXV];
bool bfs(int s, int t)
{
    std::queue<int> que;
    memset(prev, -1, sizeof(prev));
    memset(vis, 0, sizeof(vis));
    que.push(s);
    vis[s] = true;
    while(!que.empty())
    {
        int u = que.front(); que.pop();
        if(u == t) return true;
        for(int i = 1; i <= n; ++i)
            if(!vis[i] && g[u][i])
            {
                vis[i] = true;
                prev[i] = u;
                que.push(i);
            }
    }
    return false;
}
int EK_max_flow(int s, int t)
{
    int u, flow = 0, minv;
    while(bfs(s, t))
    {
        for(minv = INF, u = t; prev[u] != -1; u = prev[u])
            minv = std::min(minv, g[prev[u]][u]);
        flow += minv;
        for(u = t; prev[u] != -1; u = prev[u])
        {
            g[prev[u]][u] -= minv;
            g[u][prev[u]] += minv;
        }
    }
    return flow;
}
