///有向图强连通分量
//Kosaraju算法 $O(|V| + |E|)$ 利用逆图
/*
1. 先在原图中dfs(深度优先搜索), 记录下搜索次序
2. 在按反向次序在逆图中dfs, 每次dfs中遍历的子图即为一个强连通分量
*/
int V;//顶点数
const int MAXV = 1000;
vector <int> G[MAXV], rG[MAXV];//图, 逆图
vector <int> vs;//后序遍历的顶点列表
bool used[MAXV];
int cmp[MAXV];//所属强连通分量的拓扑序

void add_edge(int from, int to)
{
    G[from].push_back(to);
    rG[from].push_back(from);
}

void dfs(int v)
{
    used[v] = true;
    for(i = 0; i < G[v].size(); i++)
        if(!used[G[v][i]])
            dfs(G[v][i]);
    vs.push_back(v);
}
void rdfs(int v, int k)//逆图dfs
{
    used[v] = true;
    cmp[v] = k;
    for(int i = 0; i < rG[v].size(); i++)
        if(!used[rG[v][i]])
            rdfs(rG[v][i], k);
}

int scc()//返回强连通分量数
{
    memset(used, 0, sizeof(used));
    vs.clear();
    for(int v =  0; v < V; v++)
        if(!used[v])
            dfs(v);
    memset(used, 0, sizeof(used));
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--)
        if(!used[vs[i]])
            rdfs(vs[i], k++);
    return k;
}

//Tarjan算法 $O(|V| + |E|)$
const int MAXV = 2000;
const int MAXE = 2000;
struct edge {int to, next;} edge[MAXE];
int head[MAXV], tot;
int Low[MAXV], dfn[MAXV], Belong[MAXV];//Belong数组的值是1~scc
int Index, Stack[MAXV], top;
int scc;//强连通分量数
bool Instack[MAXV];
int num[MAXV]; //各个强连通分量包含点的个数

void add_edge(int from, int to)
{
    edge[tot].to = to;
    edge[tot].next = head[from];
    head[from] = tot++;
}

void Tarjan(int u)
{
    int v;
    Low[u] = dfn[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        v = edge[i].to;
        if(!dfn[v])
        {
            Tarjan(v);
            if(Low[u] > Low[v])
                Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > dfn[v])
            Low[u] = dfn[v];
        if(Low[u] == dfn[u])
        {
            scc++;
            do
            {
                v = Stack[--top];
                Instack[v] = false;
                Belong[v] = scc;
                num[scc]++;//
            }
            while(u != v);
        }
    }
}
void solve()
{
    memset(dfn, 0, sizeof(dfn));
    memset(Instack, false, sizeof(Instack));
    memset(num, 0, sizeof(num));
    Index = scc = top = 0;
    for(int i = 1; i <= V; i++)
        if(!dfn[i])
            Tarjan(i);
}
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}

//Gabow算法 $O(|V| + |E|)$
const int MAXV = 110;
vector <int> G[MAXV];
int V;
int dfn[MAXV];//标记进入顶点时间
int Belong[MAXV];//存储强连通分量, 其中belg[i]表示顶点i属于第belg[i]个强连通分量
int stk1[MAXV], top1;//辅助堆栈
int stk2[MAXV], top2;//辅助堆栈
int scc, Index;
void dfs(int v)
{
    dfn[v] = ++Index;
    stk1[++top1] = v;
    stk2[++top2] = v;
    for(int i = 0; i < G[v].size(); i++)
    {
        if(dfn[G[v][i]] == 0)
            dfs(G[v][i]);
        else if(Belong[G[v][i]] == 0)
        {
            while(dfn[stk2[top2]] > dfn[G[v][i]])
                top2--;
        }
    }
    if(stk2[top2] == v)
    {
        top2--;
        scc++;
        do
        {
            Belong[stk1[top1]] = scc;
        }
        while(stk1[top1--] != v);
    }
}
//Gabow算法, 求解Belong[1..n], 且返回强连通分量个数,
int Gabow()
{
    memset(Belong, 0, sizeof(Belong));
    memset(dfn, 0, sizeof(dfn));
    Index = scc = top1 = top2 = 0;
    for(int v = 0; v < V; i++)
        if(!dfn[v])
            dfs(v);
    return scc;
}
/*Kosaraju算法的第二次深搜隐藏了一个拓扑性质, 而Tarjan算法和Gabow算法省略了第二次深搜, 所以, 它们不具有拓扑性质. Tarjan算法用堆栈和标记, Gabow用两个堆栈 (其中一个堆栈的实质是代替了Tarjan算法的标记部分) 来代替Kosaraju算法的第二次深搜, 所以只用一次深搜, 效率比Kosaraju算法要高.*/
