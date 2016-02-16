///最小割Minimum Cut
/*
定义:
割: 网络(V,E)的割(cut)[S,T]将点集V划分为S和T(T=V-S)两个部分, 使得源s $\in$ S, 汇t $\in$ T. 符号[S,T]代表一个边集合{$<u,v>|<u,v> \in E, u \in S, v \in T$}. 穿过割[S,T]的净流(net flow)定义为f(S,T), 容量(capacity)定义为c(S,T).
最小割: 该网络中容量最小的割
(割与流的关系) 在一个流网络G(V, E)中, 设其任意一个流为f, 且[S, T]为G一个割. 则通过割的净流为f(S, T) = |f|.
(对偶问题的性质) 在一个流网络G(V, E)中, 设其任意一个流为f, 任意一个割为[S, T], 必有$|f| \leq c[S, T]$.
(最大流最小割定理) 如果f是具有源s和汇t的流网络G(V,E)中的一个流,则下列条件是等价的:
		(1) f是G的一个最大流
		(2) 残留网络$G_f$不包含增广路径
		(3) 对G的某个割[S,T], 有|f|=c[S,T]
		即最大流的流值等于最小割的容量
*/
/*
性质:
    性质1(不连通): 在给定的流网络中, 去掉割的边集, 则不存在任何一条从源到汇的路径.
    性质2(两类点): 在给定的流网络中, 任意一个割将点集划分成两部分. 割为两部分点之间的"桥梁".
技巧:
    技巧1 用正无限容量排除不参与决策的边.
    技巧2 使用割的定义式来分析最优性.
    技巧3 利用与源或汇关联的边容量处理点权.
*/
/*
最小割的求法:
	1. 先求的最大流
	2. 在得到最大流f后的残留网络$G_f$中,从源s开始深度优先遍历(DFS),所有被遍历的点, 即构成点集S
	注意: 虽然最小割中的边都是满流边, 但满流边不一定都是最小割的边.
	注意: 如果在无向图中从汇点遍历求点集T, 需要看反向边的容量是否为0, 即e[i^1].cap > 0
最小割唯一性判断(zoj2587): 遍历得到的点集|S| + |T| == V
*/
int max_flow(int s, int t) {}
int getST(int s, int t, int vis[])
{
    int mincap = max_flow(s, t);
    memset(nd, 0, sizeof(nd));
    queue<int> que;
    que.push(s);
    vis[s] = 1;
    while(!que.empty())
    {
        int u = que.front(); que.pop();
        for(int i = 0; i < (int)g[u].size(); i++)//travel v
            if(g[u][i].cap > 0 && !vis[g[u][i].to])
            {
                vis[g[u][i].to] = 1;
                que.push(g[u][i].to);
            }
    }
    return mincap;
}
///无向图全局最小割 Stoer-Wagner算法
/*定理: 对于图中任意两点s和t来说, 无向图G的最小割要么为s到t的割, 要么是生成图G/{s,t}的割(把s和t合并)
算法的主要部分就是求出当前图中某两点的最小割, 并将这两点合并
快速求当前图某两点的最小割:
	1. 维护一个集合A, 初始里面只有$v_1$(可以任意)这个点
	2. 区一个最大的w(A, y)的点y放入集合A(集合到点的权值为集合内所有点到该点的权值和)
	3. 反复2,直至A集合G集相等
	4. 设后两个添加的点为s和t, 那么w(G-{t}, t)的值, 就是s到t的cut值
*/
//$O(|V|^3)$
const int MAXV = 510;
int n;
int g[MAXV][MAXV];//g[u][v]表示u,v两点间的最大流量
int dist[MAXV];//集合A到其他点的距离
int vis[MAXV];
int min_cut_phase(int &s, int &t, int mark) //求某两点间的最小割
{
    vis[t] = mark;
    while(true)
    {
        int u = -1;
        for(int i = 1; i <= n; i++)
            if(vis[i] < mark && (u == -1 || dist[i] > dist[u])) u = i;
        if(u == -1) return dist[t];
        s = t, t = u;
        vis[t] = mark;
        for(int i = 1; i <= n; i++) if(vis[i] < mark) dist[i] += g[t][i];
    }
}

int min_cut()
{
    int i, j, res = INF, x, y = 1;
    for(i = 1; i <= n; i++)
        dist[i] = g[1][i], vis[i] = 0;
    for(i = 1; i < n; i++)
    {
        res = min(res, min_cut_phase(x, y, i));
        if(res == 0) return res;
        //merge x, y
        for(j = 1; j <= n; j++) if(vis[j] < n) dist[j] = g[j][y] = g[y][j] = g[y][j] + g[x][j];
        vis[x] = n;
    }
    return res;
}

/*
*/
