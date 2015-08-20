//1. 格雷码: (相邻码之间二进制只有一位不同), 构造方法: $a_i = i \ xor \ (i>>1)(a_i$为求第i个格雷码)
/*2. 多边形数: 可以排成正多边形的整数
	第n个s边形数的公式是: $\frac{n[(s-2)n - (s-4)]}{2}$
	费马多边形定理:每一个正整数最多可以表示成n个n-边形数之和
*/
//3. 四平方和定理: 每个正整数均可表示为4个整数的平方和。它是费马多边形数定理和华林问题的特例.
//4. 即对任意奇素数 p，同余方程$x^2+y^2+1 \equiv 0\pmod p $必有一组整数解x，y满足$0 \leq x < \frac{p}{2},0 \leq y < \frac{p}{2}$
///勾股数
/*
勾股数: 对正整数a, b, c, 如果有$a^2 + b^2 = c^2$, 称(a, b, c)为勾股数
性质: a, b中一个为奇数, 一个为偶数, c一定为奇数.
本原勾股数: 满足$\gcd{(a, b,c)} = 1$的勾股数
本原勾股数定理: 如果对奇数$s > t \geq 1$, 且$\gcd(s,t)=1$, 则有: $a = s \times t, b = \frac{s^2 - t^2}{2}, c = \frac{s^2 + t^2}{2}$, (a, b, c)是本原勾股数
*/
/*数组映射循环同构
	对于一个数组, 我们假设不关心它的每个数值得大小, 只关心它们是否相同, 而且它是循环的, 即从任意位置都可以看做是数组的起点. You are given a set of N vectors, each vector consists of K integers. Vector X is equivalent to Y (denoted $X \equiv Y$). if there exist a bijection $f : Z \to Z$ and an integer r, such that X[i] = f(Y [(i + r) mod K]) for each i in the range [0..K − 1]. For example, $(1, 2, 2, 3) \equiv (22, 3, 4, 22)$, with r = 2 and f(22) = 2, f(3) = 3 and f(4) = 1. But (22, 3, 22, 4) is not equivalent to (1, 2, 2, 3).
	我们将对于每个位置, 我们找出下一个相同数字的位置, 用它们的位置差表示该数组, 然后用最小表示法, 即可唯一的表示出该等价关系.
	例: 对(22, 3, 4, 22), 用位置差代替该数字, 得: (3, 4, 4, 1), 最小表示法得: (1, 3, 4, 4)这样所有等价的数组有且仅有这么一种表示方法.
*/
