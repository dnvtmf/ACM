///莫队算法
//复杂度: $O(n\sqrt{n} \cdot \mbox{转移的复杂度})$
//n个数, q次区间查询
/*使用条件:
已知区间[l, r]的答案, 可在O(1) 或O(log n) 内得到[l + 1, r], [l - 1, r], [l, r + 1], [l, r - 1]的答案
查询可以离线*/
/*做法:
	将查询以l所在的块为第一关键字, 以r为第二关键字排序, 然后从一个初始状态开始转移
注意: 	1. 转移的时候, 要先转移使l减小, 和使r增大的部分, 后转移使l增大和使r减小的部分, 避免l > r
		2. 转移的时候注意先加减l, r, 后加减l, r的问题.
*/
int qst;//每块的大小
struct Query {
	int l, r, id;
} qry[NUM];
LL ans[NUM];
bool operator < (const Query &a, const Query &b)
{
	if((a.l / sqt) == (b.l / sqt)) return a.r < b.r;
	return a.l < b.l;
}
int update(int l, int r);//转移[l, r]到答案的改变
void solve(int n)
{
	sqt = sqrt(1.0 * n);
	sort(qry, qry + Q);
	int l = 0, r = 0;
	int res = a[0];
	for(i = 0; i < Q; i++) {
		while(l > qry[i].l) res += update(--l, r);
		while(r < qry[i].r) res += update(l, ++r);
		while(r > qry[i].r) res -= update(l, r--);
		while(l < qry[i].l) res -= update(l++, r);
		ans[qry[i].id] = res;
	}
}
//分块 $O(N\sqrt{N})$
