///矩阵 Matrix
/*定义:
	矩阵: m行n列.
	n阶方阵: n行n列的矩阵.
	行矩阵: $1 \times n$的矩阵.
	列矩阵: $n \times 1$的矩阵.
	零矩阵$O_{m \times n}$: 全为0的矩阵.
	单位矩阵$I_n$: 对角线全为1的n阶方阵.
	同型矩阵A, B: A, B的行数和列数都相同.
*/
/*操作和性质:
线性运算:
	两矩阵A, B相等: A, B是同型矩阵, 且对应元相等.
	矩阵的加法和减法: 当A, B是同型矩阵时可加减, 结果是对应元相加减的同型矩阵.
	A的负矩阵-A: A的每个元取反.
	矩阵的数乘kA: A的每个元乘以k.
线性运算的性质:
	1. (交换律) A + B = B + A
	2. (结合律) (A + B) + C = A + (B + C)
	3. A + O = A, A + (-A) = O
	4. 1A = A
	5. k(lA) = (kl)A
	6. k(A + B) = kA + kB
	7. (k + l)A = kA + lA
矩阵的乘法:
	$m \times p$矩阵$A = (a_{ij})_{m \times p}$, $p \times n$矩阵$B = (b_{ij})_{p \times n}$的乘积为$m \times n$矩阵$C = (c_{ij})_{m \times n}$, 其中@$$ c_{ij} = \sum_{k=1}^{p}{a_{ik} b_{kj}}$$@.
	要求A的列数等于B的行数时才能相乘
矩阵的乘法的性质:
	1. (结合律) (AB)C = A(BC)
	2. (数乘结合律) k(AB) = (kA)B = A(kB)
	3. (分配率) A(B + C) = AB + AC, (B + C)A = BA + CA
	4. 矩阵的乘法一般不满足交换律, 当AB = BA时, 称A与B可交换.
	5. 不满足消去率, 即由AB - AC = A(B - C) = O不能推出B - C = O
	6. $I_m A_{m \times n} = A_{m \times n} I_m = A_{m \times n} $
	7. n阶单位矩阵与任意n阶矩阵A是可交换的, 即IA = AI = A.
方阵的幂:
	设A是n阶方阵, k是正整数, 定义:@$$ \left\{ \begin{array}{l l}
		A^0 = I\\
		A^1 = A\\
		A^{k+1} = A^k A , &k = 1, 2, \cdots
	\end{array}\right.$$@
	对于n阶任意方阵A, 对于很大的整数t, 想在$Z_p$下求 $A^t$(就是求$A^t$的各项模p, 其中p为素数), 即$W(n, p) = \prod_{i = 0}^{n - 1}{p^n - p^i}$, 则有: $A^t \equiv A^{t \pmod{W(n, p)}}$.
方阵的幂的性质:
	1. $A^m A^k = A^{m + k}$
	2. $(A^m)^k = A^{mk}$
	3. 一般$(AB)^k \neq A^k B^k $, 当AB = BA时, $(AB)^k = A^k B^k = B^k A^k$, 其逆不真.
n阶方阵的循环节(关于质数p):
	$$A^{\prod_{i=0}^{n-1}{p^n - p^i}} \pmod{p} = I$$
矩阵的转置:
	将矩阵A的行列互换, 所得的矩阵称为A的转置, 即为$A_T$.
	$m \times n$矩阵的转置是$n \times m$矩阵
	对称矩阵A: $A^T = A$
	反对称矩阵A: $A^T = -A$
矩阵的转置的性质:
	1. $(A^T)^T = A$
	2. $(A + B)^T = A^T + B^T$
	3. $(kA)^T = kA^T, k$为数
	4. $(AB)^T = B^T A^T$
分块矩阵:
	将$m \times n$矩阵分为$r \times c$个子矩阵, 分块矩阵的乘法相当于将把各个子矩阵当作数是的乘法.
*/
const int Matrix_N = 55, Matrix_M = 55;
struct Matrix {
	int a[Matrix_N][Matrix_M];
	int n, int m;
	Matrix(int _n = 0, int _m = 0, bool I = false) {init(_n, _m, I);}
	void init(int _n = 0, int _m = 0, bool I = false)
	{
		memset(a, 0, sizeof(a));
		n = _n;
		m = _m;
		if(I) for(int i = 1; i <= n; ++i) a[i][i] = 1;
	}
	int *operator [](size_t _) {return a[_];}
	//C = A + B
	Matrix operator + (const Matrix &B) const
	{
		Matrix res(n, m);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m; ++j)
				res.a[i][j] = a[i][j] + B.a[i][j];
		return Matrix;
	}
	//C = A - B
	Matrix operator - (const Matrix &B) const
	{
		Matrix res(n, m);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m; ++j)
				res.a[i][j] = a[i][j] - B.a[i][j];
		return Matrix;
	}
	//A += B
	Matrix operator += (const Matrix &B) const
	{
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m; ++j)
				a[i][j] += B.a[i][j];
		return *this;
	}
	//C = AB
	Matrix operator * (const Matrix &B) const
	{
		Matrix res(n, B.m);
		int i, j, k;
		for(i = 1; i <= n; ++i)
			for(j = 1, res.a[i][j] = 0; j <= B.m; ++j)
				for(k = 1; k <= m; ++k)
					res.a[i][j] = a[i][k] * B.a[k][j];
//                    if((res.a[i][j] += a[i][k] * B.a[k][j] % mod) >= mod)
//                        res.a[i][j] -= mod;
		return res;
	}
	//方阵的k次幂
	Matrix operator ^(int k)
	{
		Matrix x = *this;
		Matrix res(x.n, x.n, true);
		while(k) {
			if(k & 1) res = res * x;
			x = x * x;
			k >>= 1;
		}
		return res;
	}
	void out()
	{
		printf("N = %d, M = %d\n", n, m);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				printf("%d%c", a[i][j], j == n ? '\n' : ' ');
	}
};

/*应用:
1. A是$1 \times n$的行矩阵, B是n阶方阵, 则@$$
	C_{1 \times n} = ABB \cdots B = A(B^m)$$@
2. 设A是$n \times 1$的列矩阵, B是n阶方阵, 求$\displaystyle \sum_{k=0}^{m-1}{AB^k}$
	做法: 令C为分块矩阵@$$\left[ \begin{matrix}
		B &A \\
		O &I
	\end{matrix}\right]$$@, 则@$$
	C^m = \left[ \begin{matrix}
		B^m & \displaystyle \sum_{k=1}^{m-1}{AB^k} \\
		O & I
	\end{matrix}\right]$$@
3. 若A是$n \times 1$的列矩阵, B是$1 \times n$的行矩阵, 则@$$
	(AB)^k = A(BA)^{k-1}B $$@
*/
