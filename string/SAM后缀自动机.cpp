///后缀自动机(Suffix Automatic, SAM)
/*
定义:
    字符串S的后缀自动机是一个能识别S的所有后缀(子串)的自动机. 即SAM(x) = true, 当且仅当x是S的后缀.
性质:
	1. 从根出发的任意结点p的每条路径上的字符组成的字符串, 都是当前串t的子串.
	2. 如果当前结点p是可以接受新后缀的结点, 那么从根到任意结点p的每条路径上的字符组成的字符串, 都必定是当前串t的后缀.
	3. 如果结点p可以接受新的后缀, 那么p的par指向的结点也可以接受后缀, 反过来就不行.
	4. 对于SAM的每个状态s, 令r为Right(s)中任意的一个元素, 它代表的是结束位置在r的, 长度在 $[\min{(s)}, \max{(s)}]$ 之间的所有子串.
空间复杂度: $O(n)$
时间复杂度: $O(n)$
*/
/*SAM_node:
par: Parent树上该结点的父节点
val: Max(x)
*/
///指针版
const int NUM = 250000 + 10;
struct SamNode {
	SamNode *par, *ch[26];
	int val;
	SamNode()
	{
		val = 0;
		par = 0;
		memset(ch, 0, sizeof(ch));
	}
};
struct SAM {
	SamNode node[NUM * 2], *last, *root;
	int size;
	void init() {last = root = &node[size = 0];}
	void insert(int w)
	{
		SamNode *p = last, *np = &node[++size];
		np->val = p->val + 1;
		while(p && !p->ch[w])
			p->ch[w] = np, p = p->par;
		if(!p) np->par = root;
		else {
			SamNode *q = p->ch[w];
			if(q->val == p->val + 1) np->par = q;
			else {
				SamNode *nq = &node[++size];
				memcpy(nq->ch, q->ch, sizeof(q->ch));
				nq->val = p->val + 1;
				nq->par = q->par;
				q->par = np->par = nq;
				while(p && p->ch[w] == q)
					p->ch[w] = nq, p = p->par;
			}
		}
		last = np;
	}
} sam;
//数组版
/*
build(s): 建立字符串s的后缀自动机
Right(): 计算每个状态的|Right|
*/
struct SAM {
	int par[NUM * 2], ch[NUM * 2][26];
	int val[NUM * 2];
	int r[NUM * 2];
	int deg[NUM * 2];
	int sz, root, last;
	void init()
	{
		//memset(ch, 0, sizeof(ch));
		//memset(r, 0, sizeof(r));
		root = last = sz = 1;
	}
	void insert(int w)
	{
		int p = last, np = ++sz;
		val[np] = val[p] + 1;
		r[np] = 1;
		for(; p && !ch[p][w]; p = par[p])
			ch[p][w] = np;
		if(p == 0) par[np] = root;
		else {
			int q = ch[p][w];
			if(val[q] == val[p] + 1) par[np] = q;
			else {
				int nq = ++sz;
				memcpy(ch[nq], ch[q], sizeof(ch[q]));
				val[nq] = val[p] + 1;
				par[nq] = par[q];
				par[q] = par[np] = nq;
				for(; p && ch[p][w] == q; p = par[p])
					ch[p][w] = nq;
			}
		}
		last = np;
	}
	void build(char s[])
	{
		init();
		for(int i = 0; s[i]; ++i)
			insert(s[i] - 'a');
	}
	void Right()
	{
		int p = root;
		for(int i = root + 1; i <= sz; ++i) ++deg[par[i]];
		queue<int> que;
		for(int i = 1; i <= sz; ++i)
			if(!deg[i])
				que.push(i);
		while(!que.empty()) {
			p = que.front();
			que.pop();
			if(!par[p]) continue;
			r[par[p]] += r[p];
			if((--deg[par[p]]) == 0) que.push(par[p]);
		}
	}
} sam;
/*应用:
求Right集合的大小:
    从root给定按照字符串节点走到last节点经过的所有状态的r都是1. 其余状态的r为所有儿子的和.
最长连续子串: 用母串A构造SAM, 用SAM读入串B;
    令当前状态为s, 最大匹配长度为len;
    下面读入字符x, 如果s有标号为x的边, 那么, s = trans(s, x), ++len;
    否则我们找到s的第一个具有标号为x的边的祖先a, 令s = trans(a,x), len = max(a) + 1;
    如果没有这样的祖先, 那么令s = root, len = 0;
子串出现次数:
    等于trans(init, substr)状态到end状态的路径数, 将自动机结点按拓扑排序后dp实现
最小循序串:
    要求循环字符串S的字典序最小的状态: 构造SS的SAM, 从init开始, 每次走标号最小的转移
*/
/*题目:
1. SPOJ NSUBSTR
    题意: 给一个字符串S, 求长度为$i(1 \leq i \leq |S|)$的子串出现的最多的次数.
    分析: 令 $f_i$ 为长度为i的子串出现的最多的次数. 首先建立后缀自动机, 对于每一个节点s, 假设控制的子串长度为 $[\min{(s)}, \max{(s)}]$, Right集合个数为r, 那么它可以去更新$f_{max(s)} = \max{(f_{max(s)}, r)}$. 但是最后不要忘记用 $f_i$ 去更新 $f_{i−1}$.
*/
