/*Baby-step Griant-step算法
分块, 暴力, 空间换时间
给定大小为 $n$ 的有限群$G$, 一个生成式 $\alpha$ 和 一个群中元素 $\beta$, 求一个整数 $x$ 使得 $$\alpha ^ {x} = \beta$$
令 $x = im - j, m = \lceil \sqrt{n} \rceil, 1 \leq i \leq m, 1 \leq j \leq m$, 因此有: $(\alpha ^{m}) ^ i = \beta \alpha ^ j$.
算法流程:
1. $m = \lceil \sqrt{n} \rceil$
2. 对所有$j(0 \leq j < m)$, 将 $(\beta \alpha^j, j)$存在哈希表中
3. 计算 $\alpha ^ {m}$
4. 对于 $i(1 \leq i \leq m)$, 如果能在哈希表中找到$\alpha^{m} = \gamma = \beta (\alpha ^ j) ^ i$, 则$im - j$是所求的$x$.
复杂度: $O(\sqrt{n})$
*/
//求最小的x, 是$\alpha^x \equiv beta \pmod{p}$
//[2417:Discrete Logging](2417:Discrete Logging)
int BSGS(int a, int b, int p)
{
	int m = ceil(sqrt(p));
	unordered_map<int, int> mp;
	int baj = b, am = 1;
	for(int j = 1; j <= m; ++j) {
		baj = 1ll * baj * a % p;
		am = 1ll * am * a % p;
		mp[baj] = j;
	}
	int ami = 1;
	for(int i = 1; i <= m; ++i) {
		ami = 1ll * ami * am % p;
		auto it = mp.find(ami);
		if(it != mp.end()) {
			return i * m - it->SE;
		}
	}
	return -1;
}
