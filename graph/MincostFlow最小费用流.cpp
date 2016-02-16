///最小费用最大流 miniunm cost flow
//不断寻找最短路增广即可
//复杂度: $O(F \cdot MaxFlow(G))$
//对于稀疏图的效率较高, 对于稠密图的的效率低
///dijkstra实现 基于0开始的图
const int MAXV = 11000, MAXE = 41000;
struct edge {int next, to, cap, cost;} e[MAXE << 1];
int head[MAXV], htot;
int V;
void init()
{
    memset(head, -1, sizeof(head));
    htot = 0;
}
void add_edge(int u, int v, int cap, int cost)
{
    e[htot] = (edge) {head[u], v, cap, cost};
    head[u] = htot++;
    e[htot] = (edge) {head[v], u, 0, -cost};
    head[v] = htot++;
}
int dist[MAXV];
int prev[MAXV], pree[MAXV];
int h[MAXV], V;
void dijkstra(int s)
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(dist, dist + V, INF);
    que.push(P(0, s));
    dist[s] = 0;
    while(!que.empty())
    {
        P p = que.top(); que.pop();
        int u = p.SE;
        if(dist[u] < p.FI) continue;
        for(int i = head[u]; ~i; i = e[i].next)
            if(e[i].cap > 0 && dist[e[i].to] > dist[u] + e[i].cost + h[u] - h[e[i].to])
            {
                dist[e[i].to] = dist[u] + e[i].cost + h[u] - h[e[i].to];
                prev[e[i].to] = u;
                pree[e[i].to] = i;
                que.push(P(dist[e[i].to], e[i].to));
            }
    }
}
int min_cost_flow(int s, int t, int flow)
{
    int min_cost = 0;
    memset(h, 0, sizeof(h));
    for(bool f = true; f;)
    {
        f = false;
        for(int u = 0; u < V; ++u)
            for(int i = head[u]; ~i; i = e[i].next)
                if(e[i].cap > 0 && h[e[i].to] > h[u] + e[i].cost)
                    h[e[i].to] = h[u] + e[i].cost, f = true;
    }
    while(flow > 0)
    {
        dijkstra(s);
        if(dist[t] == INF) return -1;
        for(int i = 0; i < V; i++) h[i] += dist[t];
        int now_flow = flow;
        for(int u = t; u != s; u = prev[u])//寻找瓶颈边
            now_flow = min(now_flow, e[pree[u]].cap);
        flow -= now_flow;
        min_cost += now_flow * (dist[t] - h[s] + h[t]);
        for(int u = t; u != s; u = prev[u])
        {
            e[pree[u]].cap -= now_flow;
            e[pree[u] ^ 1].cap += now_flow;
        }
    }
    return min_cost;
}

///spfa实现 基于0开始的图
int dist[MAXV];
int InQue[MAXV], Pree[MAXV], Prev[MAXV];
bool spfa(int s, int t)
{
    memset(dist, 0x3f, sizeof(dist));
    //memset(InQue, 0, sizeof(InQue));
    queue<int> que;
    que.push(s);
    dist[s] = 0;
    InQue[s] = 1;
    while(!que.empty())
    {
        int u = que.front(); que.pop();
        InQue[u] = 0;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if(e[i].cap > 0 && dist[v] > dist[u] + e[i].cost)
            {
                dist[v] = dist[u] + e[i].cost;
                Pree[v] = i;
                Prev[v] = u;
//                assert(e[i].cap > 0);
                if(InQue[v] == 0)
                {
                    InQue[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    return dist[t] != 0x3f3f3f3f;
}
void min_cost_flow(int s, int t, int flow)
{
    int ans = 0;
    while(flow > 0 && spfa(s, t))
    {
        int cur_flow = flow;
        for(int u = t; u != s; u = Prev[u])
            cur_flow = min(cur_flow, e[Pree[u]].cap);
        flow -= cur_flow;
        ans += dist[t] * cur_flow;
        for(int u = t; u != s; u = Prev[u])
        {
            e[Pree[u]].cap -= cur_flow;
            e[Pree[u] ^ 1].cap += cur_flow;
        }
    }
    return ans;
}

///zkw最小费用流, 在稠密图上很快
const int MAXV = 11000, MAXE = 41000;
struct edge {int next, to, cap, cost;} e[MAXE << 1];
int head[MAXV], htot;
int V;
void init()
{
    memset(head, -1, sizeof(head));
    htot = 0;
}
void add_edge(int u, int v, int cap, int cost)
{
    e[htot] = (edge) {head[u], v, cap, cost};
    head[u] = htot++;
    e[htot] = (edge) {head[v], u, 0, -cost};
    head[v] = htot++;
}
int dist[MAXV];
int slk[MAXV];
int src, sink;//源和汇
bool vis[MAXV];
int min_cost;//最小费用
int aug(int u, int f)
{
    int left = f;
    if(u == sink)
    {
        min_cost += f * dist[src];
        return f;
    }
    vis[u] = true;
    for(int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to;
        if(e[i].cap > 0 && !vis[v])
        {
            int t = dist[v] + e[i].cost - dist[u];
            if(t == 0)
            {
                int delta = aug(v, min(e[i].cap, left));
                if(delta > 0) e[i].cap -= delta, e[i ^ 1].cap += delta, left -= delta;
                if(left == 0) return f;
            }
            else
                slk[v] = min(t, slk[v]);
        }
    }
    return f - left;
}
bool modlabel()
{
    int delta = INF;
    for(int i = 0; i < V; i++)
        if(!vis[i]) delta = min(delta, slk[i]), slk[i] = INF;
    if(delta == INF) return false;
    for(int i = 0; i < V; i++)
        if(vis[i]) dist[i] += delta;
    return true;
}
int zkw_min_cost_flow(int s, int t)
{
    src = s, sink = t;
    min_cost = 0;
    int flow = 0;
    memset(dist, 0, sizeof(dist));
    memset(slk, 0x3f, sizeof(slk));
    int tmp = 0;
    do
    {
        do
        {
            memset(vis, false, sizeof(vis));
            flow += tmp;
        }
        while((tmp = aug(src, INF)));
    }
    while(modlabel());
    return min_cost;
}
