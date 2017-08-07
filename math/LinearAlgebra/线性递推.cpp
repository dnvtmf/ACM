///常系数线性齐次递推
//已知 $f_{x} = a_{1} f_{x-1} + a_{2} f_{x-2} + \cdots a_{n} f_{x-n}$ 和 $f_{1}, f_{2}, \cdots, f_{n}$, 求$f_t$
/*矩阵快速幂方法: $O(n^3 \log{t})$
f的递推可以看做是一个$n\times n$的矩阵A乘以一个n维列向量$\beta$, 即
@$$A = \left[ \begin{matrix}
0 &1 &0 &\cdots &0 \\
0 &0 &0 &\cdots &0 \\
&\vdots & &\ddots &\vdots \\
0 &0 &0 &\cdots &1 \\
a_{n} &a_{n-1} &a_{n-2} &\cdots &a_1
\end{matrix}\right],
\beta_n = \left[ \begin{matrix}
f_{x-n} \\ f_{x - n + 1} \\ \vdots \\ f_{x-2} \\ f_{x-1}
\end{matrix}\right]$$@
则$\beta_{t} = A^{t-n+1} \beta_{0}(t \geq n)$
*/

/*系数表示方法: $O(n^2 \log{t})$
将第 $x$ 项表示为前 $n$ 项的线性表示, 即: $\disp f_{x} = \sum_{i=1}^{n}{s_{x,i} f_{i}}$
将表示向左移动 $y$ 项任然成立, 即: $\disp f_{x+y} = \sum_{i=1}^{n}{s_{x,i} f_{i+y}}$
展开得: $\disp f_{x+y}
= \sum_{i=1}^{n}{s_{x, i} \sum_{j=1}^{n}{s_{y, j} f_{x+j}}}
= \sum_{k=1}^{2 n}{f_{k} \sum_{i + j = k}{s_{x, i} s_{y, j}}}
$
得到 $2n$ 项, 然后用转移方程化简掉最后$k$ 项.
卷积和化简(多项式取模)为 $O(n^2)$, 可用FFT降低为 $O(n\log{n})$
*/
/*
常系数线性齐次递推求第k项
复杂度: $O(n^2 \log{k})$
*/
class LinearRecursion
{
private:
	int mod = 1e9 + 7; //模数
	void conv(int x[], int y[], int z[], int n)
	{
		for(int i = 0; i <= n + n; ++i) z[i] = 0;
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				z[i + j] = (z[i + j] + 1ll * x[i] * y[j]) % mod;
	}
	void add_ploy(int c[], int si[], int sj[], int res[], int n)
	{
		//多项式卷积
		conv(si, sj, res, n);
		//多项式化简
		for(int i = n; i > 0; --i) {
			for(int j = 0; j <= n; ++j) {
				res[i + j - 1] = (res[i + j - 1] + 1ll * res[i + n] * c[j]) % mod;;
			}
		}
	}
public:
	int get(int a[], int s[], int n)
	{
		//已知齐次递推的前n项a(包括常数项)和系数s, 求第n+1项
		int res = 0;
		for(int i = 0; i <= n; ++i) {
			res = (res + 1ll * a[i] * s[i]) % mod;
		}
		return res;
	}
	//已知齐次递推的前n项a(包括常数项)和系数s, 求第k项
	//s, res, tmp为临时数组, 要求数组大小至少为2n+1
	int get_k(int k, int a[], int c[], int s[], int res[], int tmp[], int n)
	{
		for(int i = 0; i <= n; ++i) res[i] = s[i] = 0;
		res[0] = 1;
		s[1] = 1;
		for(; k; k >>= 1) {
			if(k & 1) {
				add_ploy(c, res, s, tmp, n);
				swap(res, tmp);
			}
			add_ploy(c, s, s, tmp, n);
			swap(s, tmp);
		}
		return get(a, res, n);
	}
} LR;
