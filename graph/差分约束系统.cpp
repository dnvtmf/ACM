///差分约束系统
// $AX \leq B$ 即若干线性不等式 $d[i] - d[j] \leq w[k], 1 \leq i, j \leq n, 1 \leq k \leq m$
//建边：对一个差分约束条件$d[u] - d[v] \leq w[k]$建一条有向边<u, v> 权值为w[k]
//解法：d[s] = 0, d[i] = INF(i != s) ; spfa() ; 存在负环无解, 无最短路(d[i] == INF)可取任意值, 可得一组解
#define MAXV 1000
#define MAXE 10000
#define INF 1000000007
struct edge
{
    int from;
    int to;
    int next;
    int w;
} e[MAXE];
int head[MAXV], tot;
int V, E;
void add_edge(int u, int v, int w)
{
    e[tot] = (edge) {u, v, head[u], w};
    head[u] = tot++;
}
void init() {memset(head, -1, sizeof(head)); tot = 0;}

int dist[MAXV];
bool inque[MAXV];
int outque[MAXV];

bool spfa(int s)
{
    int i, u, v;
    queue<int> que;
    for(i = 1; i <= V; i++)
    {
        inque[i] = true;
        outque[i] = 0;
        que.push(i);
        dist[i] = INF;
    }
    dist[s] = 0;
    while(!que.empty())
    {
        u = que.front();
        que.pop();
        if(++outque[u] > V) return false;
        inque[u] = false;
        for(i = head[u]; i != -1; i = e[i].next)
        {
            v = e[i].to;
            if(dist[v] <= dist[u] + e[i].w) continue;
            dist[v] = dist[u] + e[i].w;
            if(!inque[v])
            {
                que.push(v);
                inque[v] = true;
            }
        }
    }
    return true;
}
