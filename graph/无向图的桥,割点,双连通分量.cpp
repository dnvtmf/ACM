/*
无向连通图的点连通度: 使一个无向连通图变成多个连通块要删去的最少顶点数(及相连的边).
无向连通图的边连通度: 使一个无向连通图变成多个连通块要删去的最少边数.
当无向图的点连通度或边连通度大于1时, 称该图双连通图.
割点(关节点,割顶): (点连通度为1) 删去割点及其相连的边后, 该图由连通变为不连通;
割边(桥): (边连通度为1)删去割边后, 连通图变得不连通.
点双连通分量: 点连通度大于1的分量.
边双连通分量: 边连通度大于1的分量.
桥的两个端点是割点, 有边相连的两割点之间的边不一定是桥(重边).
*/
///Tarjan算法求割点或桥
/*
定义 dfn(u) 为无向图中在深度优先搜索中的遍历次序, low(u) 为顶点u或u的子树中的顶点经过非父子边追溯到的最早的结点 (dfn序号最小).

割点: 该点是根结点且有不止一棵子树, 或该结点的任意一个孩子结点, 没有到该结点祖先的反向边(存在 dfn(u) $\leq$ low(v))

桥: 当且仅当该边(u,v)是树枝边, 且dfn[u] < low[v]

缩点: 缩点后变成一棵k个点k-1条割边连接成的树, 而割点可以存在于多个块中.

将有桥的连通图加边变为边双连通图(加边数最少): 将边双连通分量缩点, 形成一棵树, 反复将两个最近公共祖先最远的两个叶子节点之间连一条边, (这样形成一个双连通分量, 可缩点), 刚好(leaf+1)/2条边.

点双连通分支: 建立一个栈, 存储当前双连通分支, 在搜索图时, 每找到一条树枝边或后向边(非横叉边), 就把这条边加入栈中. 如果遇到某时满足dfn[u] $\leq$ low[v], 说明u是一个割点, 同时把边从栈顶一个个取出, 直到遇到了边(u,v), 取出的这些边与其关联的点, 组成一个点双连通分支. 割点可以属于多个点双连通分支, 其余点和每条边只属于且属于一个点双连通分支. (树枝边: 搜索过程中遍历过的边).

边双连通分支: 求出所有的桥后, 把桥边删除, 原图变成了多个连通块 则每个连通块就是一个边双连通分支. 桥不属于任何一个边双连通分支, 其余的边和每个顶点都属于且只属于一个边双连通分支.
*/

//图
const int MAXV = 100010, MAXE = 100010;
struct edge {
	int next, to;
} e[MAXE];
int head[MAXV], htot;
int V, E;
void init()
{
	memset(head, -1, sizeof(head));
	htot = 0;
}
void add_edge(int u, int v)
{
	e[htot].to = v;
	e[htot].next = head[u];
	head[u] = htot++;
}

int dfn[MAXV], low[MAXV];
int stk[MAXV], top;//栈 -DCC

//割点 点双连通分量
int cp[MAXV];//记录割点
int id[MAXE], cnt_dcc;//连通分量编号及总数 -DCC
int index;
void tarjan(int u, int root, int pree) //重边对应边的id，否则对应父亲结点fa
{
	dfn[u] = low[u] = index++;
	int num = 0;
	for(int i = head[u]; i != -1; i = e[i].next) {
		int v = e[i].to;
		if(!dfn[v]) {
			num++;
			stk[top++] = i;//-DCC
			tarjan(v, root, i);
			if(low[u] > low[v])
				low[u] = low[v];
			if((u == root && num >= 2) || (u != root && dfn[u] <= low[v])) {
				cp[u] = 1;//是割点
				//-DCC
				cnt_dcc++;
				do {
					id[stk[--top]] = cnt_dcc;
				}
				while(stk[top] != i);
			}
		}
		else if((i ^ 1) != pree) { //-DCC
			if(low[u] > dfn[v])
				low[u] = dfn[v];
			//-DCC
			if(dfn[u] > dfn[v])
				stk[top++] = i;
		}
	}
}
void DCC(int V)
{
	index = top = cnt_dcc = 0;// -DCC
	memset(dfn, 0, sizeof(dfn));
	memset(cp, 0, sizeof(cp));
	for(int i = 1; i <= V; i++)
		if(!dfn[i])
			tarjan(i, i, -1);
}

//桥 边双连通分量
//注释部分为求边的双连通分量
int ce[MAXE], num; //记录桥
//int id[MAXE << 1], cnt_dcc; //连通分量编号及总数
int dfn[MAXV], low[MAXV];
//int stk[MAXV], top;
void tarjan(int u, int order, int pree)
{
	dfn[u] = low[u] = order++;
//    stk[top++] = u;
	for(int i = head[u]; ~i; i = e[i].next) {
		if(!e[i].inpath || (i ^ 1) == pree) continue;
		int v = e[i].to;
		if(!dfn[v]) {
			tarjan(v, order, i);
			if(low[v] < low[u]) low[u] = low[v];
			if(dfn[u] < low[v]) {
				ce[num++] = (i >> 1) + 1;
//                ++cnt_dcc;
//                do
//                {
//                    id[stk[--top]] = cnt_dcc;
//                }
//                while(stk[top] != v);
			}
		}
		else if(dfn[v] < low[u])
			low[u] = dfn[v];
	}
}
void DCC()
{
	memset(dfn, 0, sizeof(dfn));
	num = 0;
//   top = cnt_dcc = 0;
	for(int u = 1; u <= V; ++u) if(!dfn[u]) tarjan(u, 1, -1);
}
//缩点
//为连通图
const int MAXV = 10000 + 10, MAXE = 2000000 + 10;
int dfn[MAXV], low[MAXV];
int Belong[MAXV];
struct Graph {
	struct edge {
		int next, to;
		bool isBridge;
	} e[MAXE];
	int head[MAXV], htot;
	int V, E;
	void init()
	{
		memset(head, -1, sizeof(head));
		htot = 0;
	}
	void add_edge(int u, int v)
	{
		e[htot].to = v;
		e[htot].next = head[u];
		e[htot].isBridge = false;
		head[u] = htot++;
	}
	void tarjan(int u, int order, int pree)
	{
		dfn[u] = low[u] = order++;
		for(int i = head[u]; ~i; i = e[i].next) {
			if((i ^ 1) == pree) continue;
			int v = e[i].to;
			if(!dfn[v]) {
				tarjan(v, order, i);
				if(low[v] < low[u]) low[u] = low[v];
				if(dfn[u] < low[v]) {
					e[i].isBridge = e[i ^ 1].isBridge = true;
				}
			}
			else if(dfn[v] < low[u])
				low[u] = dfn[v];
		}
	}
	void ReBuild(Graph &g)
	{
		memset(dfn, 0, sizeof(dfn));
		tarjan(u, 1, -1);
		queue<int> que;
		int &n = g.V;
		Belong[1] = ++n;
		que.push(1);
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			for(int i = head[u]; ~i; i = e[i].next) {
				int &v = e[i].to;
				if(Belong[v]) continue;
				if(e[i].isBridge) {
					Belong[v] = ++n;
					g.add_edge(Belong[u], Belong[v]);
					g.add_edge(Belong[v], Belong[u]);
				}
				else Belong[v] = Belong[u];
				que.push(v);
			}
		}
	}
} g1, g2;
