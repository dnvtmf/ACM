///最小生成树Minimum Spanning Tree
/*定义
	对于一个有边权的无向图, 其边权和最小的生成树称作最小生成树.
*/
//kruskal算法 $O(|E|\log{|E|} + |E|)$
//可以用来求最大生成森林和最小生成树
const int MAXV = 1000, MAXE = 100000 * 2 + 10;
struct edge {
	int u, v;
	int cost;
	bool operator < (const edge &b) const { return cost < b.cost;}
};
//并查集
int fa[MAXV];
int dsu_init() {}
int find(int x) {}
//kruskal
int kruskal(edge e[], int n)
{
	sort(e, e + n);
	dsu_init();
	int res = 0, x, y;
	for(int i = 0; i < n; ++i) {
		x = find(e[i].u);
		y = find(e[i].v);
		if(x != y) {
			fa[x] = y;//union set x and y
			res += e[i].cost;
		}
	}
	return res;
}
//prim算法 $O(|V|^2)$
const int MAXV = 1000 + 10;
const int INF = 0x3f3f3f3f;
bool vis[MAXV];
int dist[MAXV];
int prim(int cost[MAXV][MAXV], int n)//0-based
{
	memset(vis, 0, sizeof(vis));
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	int ans = 0;
	while(true) {
		int v = -1;
		for(int u = 0; u < V; u++)
			if(!vis[u] && (v == -1 || dist[u] < dist[v]))
				v = u;
		if(v == -1) break;
		vis[v] = true;
		ans += dist[v];
		for(int u = 0; u < V; u++) m[u] = min(m[u], c[v][u]);
	}
	return ans;
}
//prim算法--优先队列优化 $O((|V| + |E|)\log{|V|})$
typedef pair <int, int > P;
const int MAXV = 100000 + 10, MAXE = 1000000 * 2 + 10;
struct edge {int next, to, cost;} e[MAXE];
int head[MAXV], etot;
void init() {}
void add_edge(int u, int v, int w) {}

int dist[MAX_V];
int prim(int n)//0-based
{
	priority_queue<P, vector<P>, greater<P> > que;
	fill(dist, dist + n, INF);
	dist[0] = 0;
	que.push(P(0, 0));
	int res = 0;
	while(!que.empty()) {
		P p = que.top();
		que.pop();
		int u = p.second();
		if(dist[u] < p.first) continue;
		res += dist[u];
		for(int i = head[u]; ~i; i = e[i].next) {
			if(dist[e[i].to] > e[i].cost) {
				dist[e[i].to] = e[i].cost;
				que.push(P(e[i].cost, e[i].to));
			}
		}
	}
	return res;
}

///次小生成树 $O(|E|\log{|E|} + |V|^2)$
//唯一最小生成树: 最小生成树权值和不等于次小生成树权值和
#define MAXV 1000
#define MAXE 10000
//并查集
int fa[MAXV];
int find(int x) {}
int merge(int x, int y) {}
//kruskal
struct Edge {int u, v, cost, sel;} e[MAXE];
bool cmp(Edge a, Edge b)
{
	if(a.cost != b.cost)return a.cost < b.cost;
	if(a.u != b.u)return a.u < b.u;
	return a.v < b.v;
}
struct edge {int next, to;} link[MAXV];
int head[MAXV], end[MAXV], tot;
//cost[][] 两顶点在最小生成树的路径中的最长边长(最大权值)
void kruskal(int cost[MAXV][MAXV], int V, int E)
{
	int k = 0;
	int i, x, y;
	int w, v;
	for(tot = 0; tot < V; tot++) {
		link[tot].to = tot + 1;
		link[tot].next = head[tot + 1];
		end[tot + 1] = tot;
		head[tot + 1] = tot;
	}
	sort(e + 1, e + 1 + E, cmp);
	for(i = 1; i <= E; i++) {
		if(k == n - 1)break;
		if(e[i].cost < 0)continue;
		x = find(e[i].u);
		y = find(e[i].v);
		if(x != y) {
			for(w = head[x]; w != -1; w = link[w].next) {
				for(v = head[y]; v != -1; v = link[v].next) {
					len[link[w].to][link[v].to] = len[link[v].to][link[w].to] = e[i].cost;
				}
			}
			link[end[y]].next = head[x];//合并两个邻接表g
			end[y] = end[x];
			merge(x, y);
			k++;
			e[i].sel = true;
		}
	}
}
void solve(int V, E)
{
	//初始化和建图
	int mst = 0, secmst = INF;
	kruskal(V, E);
	for(i = 1; i <= E; i++)
		if(e[i].sel) mst += e[i].w;
	for(i = 1; i <= E; i++)
		if(!e[i].sel) secmst = min(secmst, mst + e[i].cost - len[e[i].u][e[i].v]);
}


///有向图的最小树形图
/*定义
以vi为根的树形图:
	有向图G=(V,E)中无环, 且存在一个顶点vi不是任何弧的终点, 其他顶点恰是唯一一条弧的终点.
最小树形图: 权值和最小的树形图.
朱刘Edmonds算法 $O(|V|^3)$
	基于贪心和缩点
	求以 $v_0$ 为根的最小树形图
	1. 求最短弧集合 $E_0$: 所有以 $v_i(i \neq 0)$ 为终点的弧选最短的, 若不存在则无最小树形图;
	2. 检查: $E_0$, $E_0$ 中无环且无收缩点, $E_0$ 就是最小树形图, 有环转入3, 无环但有收缩点转入4;
	3. 缩环: 将有向环C收缩成点u, 点v在环中, 点w不在环中, 则权值 $W_{<w, u>} = W_{<w, v>} - W$(环C中指向v的弧), 以环C为起点的边<v, w>, $W_{<u, w>} = W_{<v, w>}$, 转向1;
	4. 展开环: 将收缩点u展开是环C, 从C中去掉与T1中弧有相同终点的弧, 其余弧属于T;
	图G和图G1最小树形图的差值为被缩掉的环的权值和, 只求最小树形图的权值和时不必展开环.
*/
//采用邻接矩阵
const int MAXV = 100 + 10, MAXE = 10000 + 10;
const int Inf = 1e9;
struct edge {
	int u, v;
	int cost;
	void add(int from, int to, int w) {u = from, v = to, cost = w;}
} e[MAXE];
int pre[MAXV], ID[MAXV], vis[MAXV];
int In[MAXV];
int Directed_MST(int root, int V, int E)//0-based
{
	int res = 0;
	while(true) {
		for(int i = 0; i < V; ++i) In[i] = Inf;
		for(int i = 0; i < E; ++i) {
			int u = e[i].u;
			int v = e[i].v;
			if(e[i].cost < In[v] && u != v) {
				pre[v] = u;
				In[v] = e[i].cost;
			}
		}
		for(int i = 0; i < V; ++i) {
			if(i == root) continue;
			if(In[i] == Inf) return -1;
		}
		int cntnode = 0;
		memset(ID, -1, sizeof(ID));
		memset(vis, -1, sizeof(vis));
		In[root] = 0;
		for(int i = 0; i < V; ++i) {
			res += In[i];
			int v = i;
			while(vis[v] != i && ID[v] == -1 && v != root) {
				vis[v] = i;
				v = pre[v];
			}
			if(v != root && ID[v] == -1) {
				for(int u = pre[v]; u != v; u = pre[u]) ID[u] = cntnode;
				ID[v] = cntnode++;
			}
		}
		if(cntnode == 0) break;
		for(int i = 0; i < V; ++i)
			if(ID[i] == -1)
				ID[i] = cntnode++;
		for(int i = 0; i < E; ++i) {
			int v = e[i].v;
			e[i].u = ID[e[i].u];
			e[i].v = ID[e[i].v];
			if(e[i].u != e[i].v)
				e[i].cost -= In[v];
		}
		V = cntnode;
		root = ID[root];
	}
	return res;
}

///求最小树形图的方案
//1-based
const int MAXV = 500 + 10, MAXE = 10000 + 10;
struct edge {
	int u, v, c, id;
};
void Directed_MST(int V, vector<edge> &e, int root, int []used)
{
	VI In(V + 10, INF), ID(V + 10, -1), vis(V + 10, -1), pre(V + 10, -1);
	int m = e.size();
	for(int i = 0; i < m; ++i) {
		int u = e[i].u;
		int v = e[i].v;
		if(e[i].c < In[v]) {
			pre[v] = i;
			In[v] = e[i].c;
		}
	}
	int VV = 0;
	In[root] = 0;
	for(int i = 1; i <= V; ++i) {
		int v = i;
		while(vis[v] != i && ID[v] == -1 && v != root) {
			vis[v] = i;
			v = e[pre[v]].u;
		}
		if(v != root && ID[v] == -1) {
			++VV;
			for(int u = e[pre[v]].u; u != v; u = e[pre[u]].u)
				ID[u] = VV;
			ID[v] = VV;
		}
	}
	if(VV == 0) {
		for(int i = 1; i <= V; ++i) {
			if(i != root) {
				used[e[pre[i]].id] = 1;
			}
		}
		return ;
	}
	for(int i = 1; i <= V; ++i)
		if(ID[i] == -1)
			ID[i] = ++VV;
	vector<edge> newe;
	for(edge x : e) {
		int v = x.v;
		x.u = ID[x.u];
		x.v = ID[x.v];
		if(x.u != x.v) {
			x.c -= In[v];
			newe.PB(x);
		}
	}
	Directed_MST(VV, newe, ID[root], used);
	int T = V + 1;
	for(int i = 0; i < m; ++i) {
		if(used[e[i].id]) {
			vis[e[i].v] = T;
		}
	}
	for(int i = 1; i <= V; ++i) {
		if(i != root && vis[i] != T) {
			myans[e[pre[i]].id] = true;
		}
	}
}
