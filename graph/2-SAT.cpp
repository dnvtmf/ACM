///2-SAT
/*
布尔方程的可满足性问题(SAT)
合取范式 $(a∨b∨ \cdots)∧(c∨d∨ \cdots)∧ \cdots$ 中每个 $(a∨b∨ \cdots)$中文字的个数不超过2个, 则对应的SAT问题称为2-SAT问题.

建图方式:
用有向边<u, v>表示选了u则一定要选v.
令a表示true，则!a表示false.
若a和b必须一起选，即(a && b) || (!a && !b) == true, 则建边<a, b>, <b, a>, <!a, !b>, <!b, !a>
若a和b中只能选一个，即(a && !b) || (!a && b) == true, 则建边<b, !a>, <a, !b>
如果必须选a， 即 a == true, 则建边<!a, a>
如果不能选a， 即 !a == true, 则建边<a, !a>
*/
//解法, 利用强连通分量分解, (a∨b)改为(￢a=> b)∧(￢b => a), 然后建边(~a,b), (~b, a)

///强连通缩点法 拓扑排序求任意一组解
bool solveable()//是否有解
{
    scc();//进行强连通分量分解
    //判断是否x和~x在不同强连通分量中
    for(int i = 0; i < V; i++)
        if(cmp[i] == cmp[i + V])
            return false;
    return true;
}
//拓扑排序求任意一组解部分
queue <int> que;
vector <vector <int> > dag;//缩点后逆向DAG图
int res[MAXV];//结果
int indeg[MAXV];//入度
int cf[MAXV];

void solve()
{
    dag.assign(scc + 1, vector<int> ());
    memset(indeg, 0, sizeof(indeg));
    memset(res, 0, sizeof(res));
    //DAG
    for(int i = 0; i < V; i++)
    {
        for(int v = 0; v < G[i].size(); v++)
        {
            if(Belong[i] != Belong[G[i][v]])
            {
                dag[Belong[i]].push_back(Belong[G[i][v]]);
                indeg[Belong[G[i][v]]]++;
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        cf[Belong[i]] = Belong[i + n];
        cf[Belong[i + n]] = Belong[i];
    }
    while(!que.empty())que.pop();
    for(int i = 0; i < scc_num; i++)
        if(indeg[i] == 0)
            que.push(i);
    while(!que.empty())
    {
        int v = que.front();
        que.pop();
        if(res[v] == 0)
        {
            res[v] = 1;
            res[cf[v]] = 2;
        }
        for(int i = 0; i < dag[v].size(); i++)
        {
            indeg[dag[v][i]]--;
            if(indeg[dag[v][i]] == 0)
                que.push(dag[v][i]);
        }
    }
}

///染色法 可以得到字典序最小的解
#define T(i) ((i)<<1)
#define F(i) (((i)<<1) + 1)
const int MAXV = 1000, MAXE = 2000;
struct edge {int next, to;} e[MAXE];
int head[MAXV], tot;
int V;
void init() {memset(head, -1, sizeof(head)); tot = 0;}
void add_edge(int u, int v) {e[tot] = (edge) {head[u], v}; head[u] = tot++;}
bool vis[MAXV];//结果
int stk[MAXV], top;//辅助栈
bool dfs(int u)
{
    if(vis[u ^ 1]) return false;
    if(vis[u])return true;
    vis[u] = true;
    stk[top++] = u;
    for(int i = head[u]; ~i; i = e[i].next) if(!dfs(e[i].to)) return false;
    return true;
}
bool twoSat()
{
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < V; i += 2)
    {
        if(vis[i] || vis[i ^ 1]) continue;
        top = 0;
        if(!dfs(i))
        {
            while(top) vis[stk[--top]] = false;
            if(!dfs(i ^ 1)) return false;
        }
    }
    return true;
}

///染色法二
/*
2-sta即 将一张图的所有顶点染成红黑两种颜色, 使每一条边的两个顶点的颜色都不同.
*/
const int maxv = 220;
vector<int> g[maxv];//无向图
int V;//顶点数, (0-based)
int color[maxv];
void add_edge(int u, int v)
{
    //加的边是结点u和结点v的颜色必需不同
    g[u].push_back(v);
    g[v].push_back(u);
}

bool dfs(int u, int c)
{
    color[u] = c;
    for(int i = 0; i < g[u].size(); i++)
    {
        if(color[u] == -1)
        {
            if(!dfs(g[u][i], !c));
            return false;
        }
        else if(color[g[u][i]] == c)
            return false;
    }
    return true;
}

bool twoSat()
{
    memset(color, -1, sizeof(color));
    for(int i = 0; i < V; i++)
        if(color[i] == -1 && !dfs(i, 1))
            return false;
    return true;
}
