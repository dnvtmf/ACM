///二分图Bipartite Graph
/*
*/
///二分图的判定
//染色法 $O(|V| + |E|)$
int color[MAXV];//顶点颜色(1, -1)
bool dfs(int u, int c)
{
    color[u] = c;//将顶点u染为颜色c
    for(int i = head[u]; ~i; i = e[i].next)
    {
        if(color[e[i].to] == c)
            return false;
        else if(color[e[i].to] == 0 && !dfs(e[i].to, -c))
            return false;
    }
    return true;
}
bool IsBG(int V)//0-based
{
    //memset(color, 0, sizeof(color));
    for(int i = 0; i < V; ++i)
        if(!color[i] && !dfs(i, 1))
            return false;
    return true;
}

///二分图的匹配
//|最大匹配| + |最小边覆盖| = |V| (没有孤立点的图) (二分图 |最大匹配| = |最小顶点覆盖|)
//|最大独立集| + |最小顶点覆盖| = |V|
///匈牙利算法 $O(|V| \times |E|)$
int match[MAXV];
bool vis[MAXV];
bool dfs(int u)//通过dfs寻找增广路
{
    vis[u] = true;
    for(int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to, w = match[v];
        if(!vis[v] && (w < 0 || (!vis[w] && dfs(w))))
        {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

//求最大匹配数
int bipartite_matching(int V)//0-based
{
    int res = 0;
    memset(match, -1, sizeof(match));
    for(int v = 0; v < V; v++)
    {
        if(match[v] < 0)
        {
            memset(vis, 0, sizeof(vis));
            if(dfs(v)) ++res;
        }
    }
    return res;
}

///Hopcroft Karp算法 $O(\sqrt{|V|} \times |E|)$
int nx, ny;//顶点数
vector<int> g[NUM];//二分图 1-based
bool vis[NUM];
int matchx[NUM], matchy[NUM];//匹配数组
int dx[NUM], dy[NUM];//到源点的距离
int dis;
bool searchpath()
{
    queue<int> que;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for(int i = 1; i <= nx; i++)
        if(matchx[i] < 0)
        {
            que.push(i);
            dx[i] = 0;
        }
    int u, v, w;
    while(!que.empty())
    {
        u = que.front();
        que.pop();
        if(dx[u] > dis) break;
        for(int i = 0; i < g[u].size(); i++)
        {
            v = g[u][i];
            if(dy[v] < 0)
            {
                w = matchy[v];
                dy[v] = dx[u] + 1;
                if(w < 0)
                    dis = dy[v];
                else
                {
                    dx[w] = dy[v] + 1;
                    que.push(w);
                }
            }
        }
    }
    return dis != INF;
}
bool findpath(int u)
{
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i], w = matchy[v];
        if(!vis[v] && dy[v] == dx[u] + 1)
        {
            vis[v] = 1;
            if(w >= 0 && dy[v] == dis) continue;
            if(w < 0 || findpath(w))
            {
                matchx[u] = v;
                matchy[v] = u;
                return true;
            }
        }
    }
    return false;
}
int max_match()
{
    int ans = 0;
    memset(matchx, -1, sizeof(matchx));
    memset(matchy, -1, sizeof(matchy));
    while(searchpath())
    {
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= nx; i++)
            if(matchx[i] < 0)
            {
                ans += findpath(i);
            }
    }
    return ans;
}
///最大(小)权匹配  Kuhn-Munkras KM算法 $O(n^3)$
/*其实在求最大 最小的时候只要用一个模板就行了, 把边的权值去相反数即可得到另外一个. 求结果的时候再去相反数即可*/
/*最大最小有一些地方不同..*/
#include <iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
const int maxn = 101;
const int INF = (1 << 31) - 1;
int w[maxn][maxn];//邻接矩阵表权值
int lx[maxn], ly[maxn]; //顶标
int linky[maxn];
int visx[maxn], visy[maxn];
int slack[maxn];
int nx, ny;
bool find(int x)
{
    visx[x] = true;
    for(int y = 0; y < ny; y++)
    {
        if(visy[y])
            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if(t == 0)
        {
            visy[y] = true;
            if(linky[y] == -1 || find(linky[y]))
            {
                linky[y] = x;
                return true;        //找到增广轨
            }
        }
        else if(slack[y] > t)
            slack[y] = t;
    }
    return false;   //没有找到增广轨(说明顶点x没有对应的匹配, 与完备匹配(相等子图的完备匹配)不符)
}

int KM()                //返回最优匹配的值
{
    int i, j;
    memset(linky, -1, sizeof(linky));
    memset(ly, 0, sizeof(ly));
    for(i = 0; i < nx; i++)
        for(j = 0, lx[i] = -INF; j < ny; j++)
            if(w[i][j] > lx[i])
                lx[i] = w[i][j];
    for(int x = 0; x < nx; x++)
    {
        for(i = 0; i < ny; i++) slack[i] = INF;
        while(true)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(find(x))                     //找到增广轨, 退出
                break;
            int d = INF;
            for(i = 0; i < ny; i++)          //没找到, 对l做调整(这会增加相等子图的边), 重新找
            {
                if(!visy[i] && d > slack[i])
                    d = slack[i];
            }
            for(i = 0; i < nx; i++)
            {
                if(visx[i]) lx[i] -= d;
            }
            for(i = 0; i < ny; i++)
            {
                if(visy[i]) ly[i] += d;
                else slack[i] -= d;
            }
        }
    }
    int result = 0;
    for(i = 0; i < ny; i++)
        if(linky[i] > -1)
            result += w[linky[i]][i];
    return result;
}
