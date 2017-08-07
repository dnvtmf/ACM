/*
树被定义为没有圈的连通图.
树的性质:
	1. 在树中去掉一条边后所得的图是不连通的.
	2. 在树中添加一条边后所得的图一定存在圈.
	3. 树的每一对顶点u和v之间有且仅有一条路径.
*/
/*基于点的分治
做法: 首先选取一个点将无根树转为有根树, 再递归处理每一颗以根结点的儿子为根的子树.
选点: 对于基于点的分治, 我们选取一个点, 要求将其删去后, 结点最多的树的结点个数最小, 这个点被称为"树的重心".
定理: 存在一个点使得分出的子树的结点个数均不大于 $\frac{N}{2}$.
*/
/**如何得到答案
1. 容斥: 先求出经过中心u的所有满足条件的答案, 在减去所有子树的答案(不经过点u)
2. 先处理中心一个的情况, 然后先得出该子树与前面子树的答案, 再将该子树的信息存储
*/
int Que[MAXV], tail, top;
int sz[MAXV], num[MAXV];
int fa[MAXV];
int ans[MAXV];
int vis[MAXV], Tt;
int getRoot(int u)//得到重心
{
	tail = top = 0;
	Que[top++] = u;
	fa[u] = -1;
	while(tail < top) {
		u = Que[tail++];
		for(int i = head[u]; ~i; i = e[i].next) {
			if(e[i].to == fa[u] || vis[e[i].to] == Tt) continue;
			Que[top++] = e[i].to;
			fa[e[i].to] = u;
		}
	}
	int root = -1;
	while(tail) {
		u = Que[--tail];
		sz[u] = 1, num[u] = 0;
		for(int i = head[u]; ~i; i = e[i].next) {
			if(e[i].to == fa[u] || vis[e[i].to] == Tt) continue;
			sz[u] += sz[e[i].to];
			num[u] = max(num[u], sz[e[i].to]);
		}
		num[u] = max(num[u], top - sz[u]);
		if(root < 0 || num[u] < num[root]) root = u;
	}
	return root;
}
void deal(int u, int pre)//处理u所属子树
{
	tail = top = 0;
	Que[top++] = u;
	fa[u] = pre;
	while(tail < top) {
		u = Que[tail++];
		for(int i = head[u]; ~i; i = e[i].next) {
			int v = e[i].to;
			if(v == fa[u] || vis[v] == Tt) continue;
			fa[v] = u;
			Que[top++] = v;
		}
	}
	for(int i = 0; i < top; ++i) {
		int u = Que[i];
		//求出答案
	}
	for(int i = 0; i < top; ++i) {
		int u = Que[i];
		//存储答案所需信息
	}
}
void solve(int u)
{
	u = getRoot(u);
	vis[u] = Tt;
	//处理中心一个点情况和存储信息
	for(int i = head[u]; ~i; i = e[i].next) {
		if(vis[e[i].to] == Tt) continue;
		deal(e[i].to, u);
	}
	for(int i = head[u]; ~i; i = e[i].next) {
		if(vis[e[i].to] == Tt) continue;
		solve(e[i].to);
	}
}


/*基于边的分治
在树中选取一条边, 将原树分成两棵不相交的树, 递归处理.
选边: 基于边的分治, 我们选取的边要满足所分离出来的两棵子树的结点个数尽量平均, 这条边称为"中心边".
定理: 如果一棵树中每个点的度均不大于 D, 那么存在一条边使得分出的两棵子树的结点个数在 $[ \frac{N}{D -1}, \frac{N D}{D -1 } ] (N \geq 2)$.
(?即树链剖分)
*/
