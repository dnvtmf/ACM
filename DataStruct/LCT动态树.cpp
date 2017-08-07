///动态树问题(Dynamic Tree Problems)
///数据结构: (Link-cut Tree LCT)
//LCT = 树链剖分 + Splay
//功能: 支持对树的分割, 合并, 对某个点到它的根的路径的某些操作, 以及对某个点的子树进行的某些操作. (同时维护树的形态)
/*定义:
    如果刚刚执行了对某个点的Access操作, 则称一个点被访问过;
    结点v的子树中, 如果最后被访问访问的结点在子树w中, 这里w是v的儿子, 那么称w是v的Preferred Child. 如果最后被访问的结点是v本身, 则v没有Preferred Child.
    每个结点到它的Preferred Child的边称作Preferred Edge.
    由Preferred Edge连接成的不可再延伸的路径称为Preferred Path.
    这棵树就被划分成若干条Preferred Path, 对于每一条Preferred Path, 用其结点的深度做关键字, 用Splay Tree树维护它, 称这棵树为 Auxiliary Tree.
    用 Path Parent 来记录每棵 Auxiliary Tree 对应的 Preferred Path 中的最高点的父亲结点, 如果这个 Preferred Path 的最高点就是根结点, 那么令这棵 Auxiliary Tree 的 Path Parent 为 null.
    Link-Cut Trees 就是将要维护的森林中的每棵树 T 表示为若干个 Auxiliary Tree, 并通过 Path Parent 将这些 Auxiliary Tree 连接起来的数据结构.
操作:
    Access(x): 使结点x到根结点的路径成为新的Preferred Path.
    FindRoot(x): 返回结点x所在树的根结点.
    Link(x, y): 使结点x成为结点y的新儿子. 其中x是一棵树的根结点, 且x和y属于两棵不同的子树.
    Cut(x): 删除x与其父亲结点间的边.
    LCA(x, y): 返回x, y的最近公共祖先(x, y在同一颗树中)
*/
//根不确定
const int NUM = 100010;
#define LC(x) ch[x][0]
#define RC(x) ch[x][1]
#define DIR(x) (x == RC(fa[x]))
#define IsRoot(x) (!fa[x] || (x != LC(fa[x]) && x != RC(fa[x])))
struct LCT {
	int ch[NUM][2], fa[NUM], size;
	int stk[NUM], top;
	bool rev[NUM];
	int sz[NUM];
	int tag[NUM];
	LL ans[NUM];
	inline void push_up(int x)
	{
	}
	inline void Rev(int x) {rev[x] ^= 1, swap(LC(x), RC(x));}
	inline void push_down(int x)
	{
		if(tag[x]) {
			if(LC(x)) sz[LC(x)] += tag[x], tag[LC(x)] += tag[x];
			if(RC(x)) sz[RC(x)] += tag[x], tag[RC(x)] += tag[x];
			tag[x] = 0;
		}
		if(rev[x]) {
			Rev(x);
			rev[LC(x)] ^= 1, rev[RC(x)] ^= 1;
			rev[x] = 0;
		}
	}
	inline void Change(int x, int y, int d) {ch[x][d] = y; fa[y] = x;}
	inline int New()
	{
		size++;
		LC(size) = RC(size) = fa[size] = 0;
		sz[size] = 1;
		tag[size] = 0;
		return size;
	}
	inline void Rot(int x)
	{
		int y = fa[x], z = fa[y], d = DIR(x);
		if(!IsRoot(y)) Change(z, x, DIR(y));
		else fa[x] = z;
		Change(y, ch[x][!d], d);
		Change(x, y, !d);
		fa[0] = LC(0) = RC(0) = 0;
		push_up(y);
	}
	void push_path(int x)
	{
		for(top = 0; !IsRoot(x); x = fa[x]) stk[++top] = x;
		stk[++top] = x;
		for(int i = top; i; --i) push_down(stk[i]);
	}
	void Splay(int x)
	{
		push_path(x);
		int y, z;
		while(!IsRoot(x)) {
			y = fa[x], z = fa[y];
			if(IsRoot(y)) {Rot(x); break;}
			Rot(DIR(x) == DIR(y) ? y : x), Rot(x);
		}
		push_up(x);
	}
	int Access(int x)
	{
		int p;
		for(p = 0; x; p = x, x = fa[x]) {
			Splay(x), RC(x) = p, push_up(x);
		}
		return p;
	}
	void MakeRoot(int x)
	{
		Access(x), Splay(x);
		rev[x] = 1;
		push_down(x);
	}
	void Link(int x, int y)
	{
		MakeRoot(x);
		fa[x] = y;
		Access(x);
		Splay(x);
		if(LC(x)) {
			++sz[LC(x)];
			++tag[LC(x)];
		}
	}
	void Cut(int x, int y)
	{
		MakeRoot(y);
		Access(x);
		Splay(x);
		LC(x) = fa[y] = 0;
		push_up(x);
	}
	int FindRoot(int x)
	{
		Access(x);
		Splay(x);
		while(LC(x)) x = LC(x);
		return x;
	}
	int LCA(int x, int y)
	{
		Access(x);
		return Access(y);
	}
} lct;

//根确定
const int NUM = 200010;
#define LC(x) ch[x][0]
#define RC(x) ch[x][1]
#define DIR(x) (x == RC(fa[x]))
#define IsRoot(x) (!fa[x] || (x != LC(fa[x]) && x != RC(fa[x])))
struct LCT {
	int ch[NUM][2], fa[NUM], size;
	inline void Change(int x, int y, int d) {ch[x][d] = y; fa[y] = x;}
	inline int New()
	{
		size++;
		LC(size) = RC(size) = fa[size] = 0;
		return size;
	}
	void init(int n)
	{
		size = 0;
		for(int i = 1; i <= n; ++i) New();
	}
	inline void Rot(int x)
	{
		int y = fa[x], z = fa[y], d = DIR(x);
		if(!IsRoot(y)) Change(z, x, DIR(y));
		else fa[x] = z;
		Change(y, ch[x][!d], d);
		Change(x, y, !d);
		fa[0] = LC(0) = RC(0) = 0;
	}

	void Splay(int x)
	{
		int y, z;
		while(!IsRoot(x)) {
			y = fa[x], z = fa[y];
			if(IsRoot(y)) {Rot(x); break;}
			Rot(DIR(x) == DIR(y) ? y : x), Rot(x);
		}
	}
	int Access(int x)
	{
		int p;
		for(p = 0; x; p = x, x = fa[x]) {
			Splay(x), RC(x) = p;
		}
		return p;
	}

	void Link(int x, int y)
	{
		Access(x);
		Splay(y);
		fa[x] = y;
	}
	void Cut(int x)
	{
		Splay(x);
		if(!fa[x]) {
			fa[ch[x][0]] = 0;
			ch[x][0] = 0;
		}
		else {
			fa[ch[x][0]] = fa[x];
			ch[x][0] = 0;
		}
		fa[x] = 0;
	}
	int FindRoot(int x)
	{
		int u = x;
		while(fa[x]) x = fa[x];
		while(ch[x][0]) x = ch[x][0];
		Access(u);
		return x;
	}
} lct;
