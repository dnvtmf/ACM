/*常系数线性齐次递归关系
定义: 序列$(a_0, a_1, \cdots, a_n, \cdots)$中相邻的k+1项之间的关系@$$
	a_n = b_1 a_{n - 1} + b_2 a_{n - 2} + \cdots + b_k a_{n - k} (n \geq k) $$@
	称作序列$(a_0, a_1, \cdots, a_n, \cdots)$的k阶常系数线性齐次递归关系. 其中$b_i(i = 1, 2, \cdots, k)$是常数且 $b_k \neq 0$.
	$a_0 = h_0, a_1 = h_1, \cdots, a_{k-1} = h_{k-1}$ 称为递归关系式的初值条件.
方程 $x^k - b_1 x^{k-1} - b_2 x^{k-2} - \cdots - b_k = 0$ 称做上面的递归关系式的特征方程, 方程的根称作递归关系式的特征根.

特征方程式拥有相异的根:
定理: 若 $q \neq 0, a_n = q^n$是递归关系式的解, 当且仅当q是特征方程式的根.
定理: 若 $q_1, q_2, \cdots q_k$是递归关系式的特征根, $c_1, c_2, \cdots, c_k$ 是任意常数, 则$a_n = c_1 q_1^n + c_2 q_2^n + \cdots + c_k q_k^n$是递归关系式的解.
定理: 若 $q_1, q_2, \cdots q_k$是递归关系式的互不相同的特征根, 则$a_n = c_1 q_1^n + c_2 q_2^n + \cdots + c_k q_k^n$是递归关系式的通解.

特征方程式拥有相重的根:
定理: 若特征方程式有一个m重根q, 则 $q^n, nq^n, \cdots, n^{m-1}q^n$都是递归关系式的解.
定理: 设$q_1, q_2, \cdots, q_t$ 分别是特征方程式的相异的 $m_1, m_2, \cdots, m_t$ 重根, 且 $\displaystyle \sum_{i=1}^{t}{m_i} = k$, 则 $\displaystyle a_n = \sum_{i=1}^{t}{\sum_{j=1}^{m_i}{c_{ij} n^{j-1} q_i^n}}$ 是递归关系式的通解.

通解与初值联立可求得各待定系数, 然后得到递归关系.
*/

/*常系数线性非齐次递归关系
略
*/
/*母函数法
	母函数法可以用来求解常系数线性齐次, 非齐次递归关系, 也可以用来求解非线性递归关系和非常系数递归关系.

*/

///常见递归关系
/*Catalan数
递归关系式:	@$$\left\{ \begin{array}{l l}
	\displaystyle a_{n + 1} = \sum_{i=0}^{n}{a_i a_{n-i}}, &(n \geq 2)\\
	a_0 = 1
	\end{array} \right.$$@
满足该递归关系式的序列 $(a_0, a_1, \cdots, c_n, \cdots)$ 称为Catalan序列.
称 @$$a_n = {2n \choose n} - {2n \choose n+1} = \frac{1}{n+1}{2n \choose n} = \frac{(2n)!}{(n+1)!n!}$$@ 为Catalan数.
前几项为1, 1, 2, 5, 14, 42, 132, 429, 1430, $\cdots$.
另类递归关系式: @$$\left\{ \begin{array}{l l}
	\displaystyle a_n = \frac{4n - 2}{n+1} a_{n-1} &(n \geq 2)\\
	a_0 = 1
	\end{array} \right.$$@
卡塔兰数的渐近增长为@$$C_n \sim \frac{4^n}{n^{3/2}\sqrt{\pi}}$$@
它的含义是当 $n \to \infty$时, 左式除以右式的商趋向于1.
所有的奇卡塔兰数 $a_n$ 都满足 $n = 2^k-1$. 所有其他的卡塔兰数都是偶数.
无论n的取值为多少, $n \times n$的汉克尔矩阵:$A_{i,j} = a_{i + j - 2}$ 的行列式为1.

Catalan的应用:
	1. 表示包含n组括号的合法运算是的个数.
	2. 表示有n个节点组成不同构二叉树的方案数.
	3. 表示有2n+1个节点组成不同构满二叉树(full binary tree)的方案数.
	4. 表示所有在 $n \times n$ 格点中不越过对角线的单调路径的个数.
	5. 表示通过连结顶点而将n + 2边的凸多边形分成三角形的方法个数.
	6. 表示对$1, \cdots, n$依序进出栈的置换个数.
	7. 表示集合{1, ..., n}的不交叉划分的个数.

*/

/*斐波那契数列Fibonacci
递归关系式: @$$\left\{ \begin{array}{l l}
	F_n = F_{n-1} + F_{n-2} &(n \geq 2)\\
	F_0 = 1, F_1 = 1
	\end{array} \right.$$@
Fibonacci序列 $(F_0, F_1, F_2, \cdots, F_n, \cdots) = (1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, \cdots)$

性质:
	1. $\displaystyle \sum_{i=0}^{n}{F_i} = F_{n+2} - 1$
	2. $\displaystyle \sum_{i=1}^{n}{F_{2i - 1}} = F_{2n} - 1$
	3. $\displaystyle \sum_{i=0}^{n}{F_i^2} = F_n F_{n+1}$
	4. $F_{n+1} \cdot F_{n-1} - F_n^2 = (-1) ^ {n+1}$
*/

/*第一类Stirling数
令 $[x]_n = x(x-1)(x-2)\cdots(x - n + 1)$,
定义: 若 $\displaystyle [x]_n = \sum_{k=0}^{n}{S_1(n, k) x^k}$, 则称 $S_1(n, k)$ 为第一类Stirling数. 即 $S_1(n, k)$ 为多项式 $[x]_n$ 中的 $x^k$ 的系数.
满足递归关系: @$$\left\{ \begin{array}{l l}
	S_1(n + 1, k) = S_1(n, k - 1) - n S_1(n, k) &(n \geq 0, k > 0)\\
	S_1(0, 0) = 1, S_1(n, 0) = 0
	\end{array} \right.$$@

第一类Stirling数是有正负的, 其绝对值是包含n个元素的集合分作k个环排列的方式数.
性质:
	1. $S_1(n, n) = 1$
	2. $S_1(n, n - 1) = -{n \choose 2}$
	3. $S_1(n, k) = (-1)^{n+k}|S_1(n, k)|$
	4. $|S_1(n, 1)| = (n-1)!$

*/
/*无符号第一类Stirling数
组合学解释是: 将p个物体排成k个非空循环排列的方法数.
群论解释:  n元集合 $\{1, 2, \cdots, n\}$ 恰有k个循环的置换的个数.
满足递归关系: @$$\left\{ \begin{array}{l l}
	S_1(n + 1, k) = S_1(n, k - 1) + n S_1(n, k) &(1 \leq k \leq n)\\
	S_1(n, n) = 1, S_1(n, 0) = 0 &(n > 0)
	\end{array} \right.$$@
性质:
	1. $S_1(n, n) = 1$
	2. $S_1(n, n - 1) = {n \choose 2}$
	3. $S_1(n, 1) = (n-1)!$
*/
/*第二类Stirling数
定义: 若 $\displaystyle x^n = \sum_{k=0}^{n}{S_2(n, k)[x]_k}$, 则称 $S_2(n, k)$ 是第二类Stirling数.
满足递归关系:@$$\left\{ \begin{array}{l l}
	S_2(n + 1, k) = S_2(n, k - 1) + k S_2(n, k) &(n \geq 0, k > 0)\\
	S_2(0, 0) = 1, S_2(n, 0) = 0 &(n > 0) \\
	S_2(n, k) = 0 & (n < k)
	\end{array} \right.$$@
定理: 第二类Stirling数 $S_2(n, k)$ 就是n个元素的集合划分成k个不相交的非空子集的方式数目.
性质:
	1. $S_2(n, n) = 1$
	   $S_2(n, k) = 0, (n < k $或$k = 0 < n)$
	2. $S_2(n, 2) = 2^{n-1} - 1$
	3. $S_2(n, n - 1) = {n \choose 2}$
$\displaystyle S_2(n, m) = \frac{1}{m!}\sum_{i=0}^{m}{(-1)^i{m \choose i}(m - i)^n}$
设m, n 都是正整数, $m \leq n$, 有 $\displaystyle m^n = \sum_{k=1}^{\infty}{{m \choose k} S_2(n, k) k!}$
*/

/*Bell数
定义: 若 $\displaystyle B_n = \sum_{k=0}^{n}{S_2(n, k)}$, 则称 $B_n$ 为Bell数.
满足递归关系:@$$\left\{ \begin{array}{l}
	\displaystyle B_{n+1} = \sum_{k=0}^{n}{{n \choose k} B_k} \\
	B_0 = 1
	\end{array} \right.$$@
Bell数 $B_n$ 是包含n个元素的集合的划分方法的数目.
*/



