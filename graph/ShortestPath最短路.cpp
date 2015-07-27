///最短路 Shortest Path
//Bellman-Ford算法$ O(|E|*|V|)$
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
int d[MAXV], outque[MAXV];
bool vis[MAXV];
bool spfa(int s)
{
    for(int i = 0; i < V; i++)
    {
        vis[i] = false;
        d[i] = INF;
        outque[i] = 0;
    }
    d[s] = 0;
    queue<int> que;
    que.push(s);
    vis[s] = true;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        vis[u] = false;
        if(++outque[u] > V) return false;;
        for(int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            if(d[v] > d[u] + e[i].w)
            {
                d[v] = d[u] + e[i].w;
                if(!vis[v])
                {
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return true;
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

//dijkstra算法 $O(|E|\log{|V|})$
struct edge {int v, cost;};
vector<edge> g[MAXV];
int d[MAXV];

void dijkstra(int s)
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(d, d + V, INF);
    d[s] = 0;
    que.push(P(0, s));
    while(!que.empty())
    {
        P p = que.top(); que.pop();
        int u = p.second;
        if(d[u] < p.first) continue;
        for(int i = 0; i < g[u].size(); i++)
        {
            edge &e = g[u][i];
            if(d[e.v] > d[u] + e.cost)
            {
                d[e.v] = d[u] + e.cost;
                que.push(P(d[e.v], e.v));
            }
        }
    }
}

///任意两点间最短路
//Floyd-Warshall算法 $O(|V|^3)$
int d[MAX_V][MAX_V];
int V;
void floyd_warshall()
{
    int i, j, k;
    for(k = 0; k < V; k++)
        for(i = 0; i < V; i++)
            for(j = 0; j < V; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
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

///两点间最短路 -- 所有可行路径还原
/*如果无重边, 从终点t反向dfs, 将所有满足d[u] + e.w = e[v]的边e(u,v)加入路径中即可 $O(|E|)$
  其他情况, 在计算最短路时, 将源点s到其他所有点的最短路加入最短路逆图中, 然后从终点t反向bfs, 标记所有经过的点, 最后将所有连接到非标记点的边去掉即可
*/
//情况1
int vis[MAXV];
vector<edge> G[MAXV];
void add_edge() {}
void get_pathG(int u)
{
    vis[u] = 1;
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].v, w = g[u][i].w;
        if(d[v] + w == d[u])
        {
            add_edge(u, v);
            add_edge(v, u);
            if(!vis[v])
                get_pathG(v);
        }
    }
}
//情况2
struct edge
{
//...
} e[MAXE];
int head[MAXV], tot;
vector<int> g[MAXV];//所有最短路形成的逆图
int vis[MAXV];
void dijkstra(int s)
{
    //... ... other part see above
    for(int i = head[u]; i != -1; i = e[i].next)
    {
        int v = e[i].to;
        if(d[v] > d[u] + e[i].w)
        {
            g[v].clear();
            g[v].push_back(u);
            d[v] = d[u] + e[i].w;
            que.push(P(d[v], v));
        }
        else if(d[v] == d[u] + e[i].w)
        {
            g[v].push_back(u);
        }
    }
}

void get_all_path(int s, int t)
{
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(t);
    vis[t] = 1;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        for(int i = 0; i < g[u].size(); i++)
            if(!vis[g[u][i]])
            {
                vis[g[u][i]] = 1;
                que.push(g[u][i]);
            }
    }
    for(int i = 1; i <= V; i++)
        if(!vis[i])
        {
            g[i].clear();//清空不是路径上的点
        }
}
