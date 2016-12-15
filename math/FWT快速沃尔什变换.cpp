///快速沃尔什变换(Fast Walsh-Hadamard Transform algorithm, FWT)
/**
应用: 用来实现快速逻辑位运算卷积
$A, B$ 为两个等长的向量, 求 $C = A \# B$, 即@$$C_k = \sum_{i \# j = k}{A_i \cdot B_i}$$@.
则 $\#$ 是A与B间的卷积运算.
将 $A$ 扩充到 $2^n$, 令 $A = (A_0, A_1)$, 则 $A_0$ 是前 $2^{n-1}$ 项, $A_1$ 是后 $2^{n-1}$ 项.
@$$tf_{xor}(A) = (tf_{xor}(A_0 + A_1), tf_{xor}(A_0 − A_1))$$@
@$$utf_{xor}(A) = (utf_{xor}(\frac{A_0 + A_1}{2}), utf_{xor}(\frac{A0 − A1}{2}))$$@
@$$tf_{and}(A) = (tf_{and}(A_0 + A_1), tf_{and}(A_1))$$@
@$$utf_{and}(A) = (utf_{and}(A_0 − A_1), utf_{and}(A_1))$$@
@$$tf_{or}(A) = (tf_{or}(A_0), tf_{or}(A_1 + A_0))$$@
@$$utf_{or}(A) = (utf_{or}(A_0), utf_{or}(A_1 − A_0))$$@
则 $C = utf(tf(A) \cdot tf(B))$
先递归再转换还是先转换再递归是对结果没有影响的, 所以可以把tf与utf写成一个函数.
* /
/*XOR推导:
定义: 正变换tf(X)和逆变换utf(X), X为大小为n一个向量
满足变换需要的性质: utf(tf(X)) = X, tf(X # Y) = tf(X) * tf(Y) (#是X与Y间的卷积运算, *是tf(X)和tf(Y)间的乘法运算)
变换方程: tf(A, B) = (A - B, A + B), (A, B是两个长度相同的向量)
则: $tf(A_0, A_1) * tf(B_0, B_1) = (A_0 - A_1, A_0 + A_1) * (B_0 - B_1, B_0 + B_1)$
	$= tf(A_0 B_0 + A_1 B_1, A_0 B_1 + A_1 B_0) = tf((A_0, A_1) \# (B_0, B_1))$
所以若n为偶数, 则将X, Y分别拆分成两个相同长度的向量, 然后进行变换.
逆变换方程: utf(A, B) = ((A + B) / 2, (B - A) / 2)
参考: http://apps.topcoder.com/wiki/display/tc/SRM+518*/
*/
/*
Description: fwt()正变换, ifwt()逆变换
Param[In]: a要变换的数组, [l, r)要变换的区间
Notice: 数组a的大小要为2的幂
(或许)适用: C = A # B 为 C[i^j] += A[i] * A[j] $(0 \leq i, j < n)$
*/
void fwt_xor(int a[], int l, int r)
{
	if(l == r) return ;
	int mid = (l + r) >> 1, len = mid - l + 1;
	fwt_xor(a, l, mid);
	fwt_xor(a, mid + 1, r);
	for(int i = l; i <= mid; ++i) {
		int u = a[i], v = a[i + len];
		a[i] = u - v;
		a[i + len] = u + v;
	}
}
void ufwt_xor(int a[], int l, int r)
{
	if(l == r) return ;
	int mid = (l + r) >> 1, len = mid - l + 1;
	for(int i = l; i <= mid; ++i) {
		int u = a[i], v = a[i + len];
		a[i] = (v + u) / 2;
		a[i + len] = (v - u) / 2;
	}
	ufwt_xor(a, l, mid);
	ufwt_xor(a, mid + 1, r);
}
/*
题意: 求 $\displaystyle \mbox{XOR} _{i=1}^{2n+1}{(a_i + x)} = 0 (0 \leq a_i \leq m, L \leq x \leq R) $的方案数 (对1000000007取模)
[2015北京网络赛D题](http://hihocoder.com/problemset/problem/1230)
*/
