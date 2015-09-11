///最短路 Shortest Path
//dijkstra算法 $O(|E|\log{|V|})$
struct edge {int next, to, cost;} e[MAXE];
int head[MAXV], tot;
int V, E;//结点数和边数(结点编号开始于1)
void init();
void add_edge(int u, int v, int w);
int dist[MAXV];
void dijstra(int s)
{
    priority_queue<P, vector<P>, greater<P> > que;
    for(int i = 1; i <= V; ++i) dist[i] = INF;
    dist[s] = 0;
    que.push(P(0, s));
    while(!que.empty())
    {
        P p = que.top(); que.pop();
        int u = p.SE;
        if(dist[u] < p.FI) continue;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            if(dist[e[i].to] <= dist[u] + e[i].cost) continue;
            dist[e[i].to] = dist[u] + e[i].cost;
            que.push(P(dist[e[i].to], e[i].to));
        }
    }
}

//dijkstra算法$O(|V|^2)$
int cost[MAXV][MAXV];
int d[MAXV];
bool vis[MAXV];
void dijkstra(int s)
{
    fill(d, d + V, INF);
    memset(vis, 0, sizeof(vis));
    d[s] = 0;
    while(true)
    {
        int v = -1;
        for(int u = 0; u < V; u++)
            if(!vis[u] && (v == -1 || d[u] < d[v]))
                v = u;
        if(v == -1) break;
        for(int u = 0; u < V; u++)
            d[u] = min(d[u], d[v] + cost[v][u]);
    }
}
//Bellman-Ford算法$ O(|E| \cdot |V|)$
//$d[v] = \min{\{d[u] + w[e]\}}(e = <u, v> \in E)$

const int MAXV = 1000, MAXE = 1000, INF = 1000000007;
struct edge {int u, v, cost;} e[MAXE];
int V, E;
//graph G
int d[MAXV];
void Bellman_Ford(int s)
{
    for(int i = 0; i < V; i++)
        d[i] = INF;
    d[s] = 0;
    while(true)
    {
        bool update = false;
        for(int i = 0; i < E; i++)
        {
            if(d[e[i].u] != INF && d[e[i].v] > d[e[i].u] + e[i].cost)
            {
                d[e[i].v] = d[e[i].u] + e[i].cost;
                update = true;
            }
        }
    }
}
//判负圈
bool find_negative_loop()
{
    memset(d, 0, sizeof(d));
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < E; j++)
        {
            if(d[e[j].v] > d[e[i].u] + e[j].cost)
            {
                d[e[j].v] = d[e[j].u] + e[j].cost;
                if(i == V - 1)
                    return true;
                //循环了V次后还不能收敛，即存在负圈
            }
        }
    }
    return false;
}

//spfa算法 $O(|E|\log{|V|})$
//适用于负权图和稀疏图, 稳定性不如dijstra
//存在负环返回false
int dist[MAXV];
int outque[MAXV];//出队次数, 如果大于V, 证明有负圈
bool vis[MAXV];
bool spfa(int s)
{
    for(int i = 0; i < V; i++)
    {
        vis[i] = false;
        dist[i] = INF;
        outque[i] = 0;
    }
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    vis[s] = true;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        vis[u] = false;
        if(++outque[u] > V) return false;
        for(int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            if(dist[v] <= dist[u] + e[i].cost) continue;
            dist[v] = dist[u] + e[i].cost;
            if(vis[v]) continue;
            vis[v] = true;
            que.push(v);
        }
    }
    return true;
}

///任意两点间最短路
//Floyd-Warshall算法 $O(|V|^3)$
int dist[MAXV][MAXV];
void floyd_warshall(int V)
{
    int i, j, k;
    for(k = 0; k < V; k++)
        for(i = 0; i < V; i++)
            for(j = 0; j < V; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

///两点间最短路 -- 一条可行路径还原
/*用prev[u]记录从s到u的最短路上u的前驱结点*/
vector <int> get_path(int t)
{
    vector <int> path;
    for(; t != -1; t = prev[t])
        path.push_back(t);
    reverse(path.begin(), path.end());
    return path;
}

///两点间最短路 -- 所有可行路径还原 $O(|E|)$
/*
从终点t反向dfs, 将所有满足dist[u] = e.cost + dist[v]的边e(u,v)加入路径中即可
在无向图中直接运行即可, 而在有向图中需要在其逆图中运行.
*/
int InPath[MAXE << 1];
void GetPath()
{
    memset(vis, 0, sizeof(vis));
    //memset(InPath, 0, sizeof(InPath));
    queue<int> que;
    que.push(n);
    vis[n] = true;
    while(!que.empty())
    {
        int u = que.front(); que.pop();
        for(int i = head[u]; ~i; i = e[i].next)
        {
            if(dist[u] != dist[e[i].to] + e[i].cost) continue;
            InPath[i] = InPath[i ^ 1] = true;
            if(vis[e[i].to]) continue;
            vis[e[i].to] = true;
            que.push(e[i].to);
        }
    }
}
///求最短路网络上的桥
//方法1: 将最短路网络新建一个图, 跑Tarjan算法.
//方法2: 最短路径还原时, 当且仅当队列为空, 且当前结点只有一条边指向s时, 该边为桥
//求割点类似
int vis[MAXV];
int ce[MAXE], num;
void get_bridge(int s, int t)//在逆图中运行
{
    priority_queue<P> que;
    que.push(P(dist[t], t));//按到t的距离远近出队, 保证割点一定后出队
    memset(vis, 0, sizeof(vis));
    vis[t] = 1;
    num = 0;
    while(!que.empty())
    {
        int u = que.top().SE;
        que.pop();
        int cnt = 0;
        if(que.empty())
        {
            for(int i = rhead[u]; i != -1; i = re[i].next)
            {
                int v = re[i].to, w = re[i].cost;
                if(dist[v] + w == dist[u])
                {
                    cnt++;
                    if(cnt >= 2) break;
                }
            }
        }
        bool f = que.empty() && cnt == 1;//当且仅当, 队列为空且只有一条路时, 找到桥
        for(int i = rhead[u]; i != -1; i = re[i].next)
        {
            int v = re[i].to, w = re[i].cost;
            if(dist[v] + w == dist[u])
            {
                if(f) ce[num++] = i;
                if(!vis[v])
                {
                    vis[v] = 1;
                    que.push(P(dist[v], v));
                }
            }
        }
    }
}
