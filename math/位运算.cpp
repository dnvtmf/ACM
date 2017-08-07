///异或Xor
/*
性质:   1. $0 \xor 1 = 0, 1 \xor 0 = 1, 0 \xor 0 = 0, 1 \xor 1 = 1$
        2. (交换律) $a \xor b = b \xor a$
        3. (结合律) $(a \xor b) \xor c = a \xor (b \xor c)$
        4. $a \xor a = 0$
        5. $0 \xor a = a$
        6. (二进制分解) $\displaystyle a \xor b = \sum_{i=0}^{\infty}{a_i \xor b_i}$, 其中 $a_i, b_i$是数a, b的二进制表达的第i位
            不同位置上运算互不影响
        7. 若a为偶数, 则 $a \xor (a + 1) = 1, a \xor 1 = (a + 1), (a + 1) \xor 1 = a$

应用:
    1.  从N个M位的二进制数中选出两个数, 是XOR和最大.
        解法:  建立二进制树, 枚举第一个数, 在二进制树中找到最大值. $O(MN)$
    2.  N个边带权的树, 找到一条路径是XOR和最大.
        解法:  设根root到点u的路径的XOR和为$XOR_u$, 点x和点y间路径的XOR和为 $XOR_x \xor XOR_y$. 然后转化为应用1.
    3.  从N个M位的二进制数中选出任意多个数, 使异或和最大.
        解法:  列N个进行高斯消元, 得出答案. $O(MN)$
    4.  从N个M位的二进制数中选出任意多个数, 使他们与K的异或和最大.
        解法:  转化为应用3(应用3中K= 0)
    5.  给一个赋权无向图, 求其从s点到t点的所有路径中最大的权值异或和.
        解法:  令K=任意一条从s到t的路径的权值异或和, 求出所有基本环的异化和, 转化为应用4.
*/
//应用4:
LL gauss(LL N, LL M, LL Xor[], LL K)
{
	int ret = 0;
	for(int i = M; i >= 0; i--) {
		int idx = -1;
		for(int j = ret; j < N; j++) if((Xor[j] >> i) & 1) {
				idx = j;
				break;
			}
		if(idx == -1) continue;
		swap(XorSum[idx], XorSum[ret]);
		for(int j = ret + 1; j < N; j++) if((Xor[j] >> i) & 1)
				XorSum[j] ^= XorSum[ret];
		ret++;
	}
	LL ans = K;
	for(int i = 0; i < ret; ++i) ans = max(ans, ans ^ XorSum[i]);
	return ans;
}
///求所有子集
//枚举 (1<<n)-1的所有子集的子集, 复杂度 $O(3^n)$
//如:  101的子集有 101, 100, 001, 000
void SubSet(int x)
{
	for(int i = x; ; i = (i - 1) & x) {
		//do someting
		if(!i) break;
	}
}
///求最右边一个1至最低位的部分
//如lowbit(10010) = 10
void lowbit(int x)
{
	return x & (-x);
}
//提取末尾连续的1
//如提取 0x0f00f0ffu 末尾的1得: 0xffu
int lastbit_1(int x)
{
	return x & (x ^ (x + 1));
}
///枚举${1, 2, \cdots, (1<<n) - 1}$中1的个数为k的所有元素$(k \neq 0)$
void kSubSet(int n, int k)
{
	int x = (1 << k) - 1;
	while(x < (1 << n)) {
		//do something
		int tx = x & -x, ty = tx + x;
		x = (((x ^ ty) >> 2) / tx) | ty;
	}
}

//位压缩
/*已声明32bit变量x(压缩至多32个布尔变量到x中)
读第k($0 \leq k < 32$)位:	((x>>k)&1)
读第k位并取反:              (~x>>k&1)
第k位清零:                 	x &= ~(1<<k)
第k位置1:                   x |= 1<<k
第k位取反:                  x ^= 1<<K
将第k1-k2位取反:           	x ^= ((1<<(k2-k1+1))-1)<<k1
是否恰好只有一个 true:      !(x&(x-1))&&x
判断是否有两个相邻的 true:  x>>1&x
是否有三个相邻的 true:      x>>1&x>>2&x
*/
/*位统计
(1)统计 true 的个数的奇偶性:
	x^=x>>1;x^=x>>2;
	x^=x>>4;x^=x>>8;
	x^=x>>16;
运算结果的第 i 位表示在原始数据中从第 i 位到最高位 true 数目的奇偶性, 有了这个
结果, 我们就可以很方便地得到任意一段的奇偶性: 如果想要得到 k1~k2 位中 true 个数的
奇偶性, 直接计算(x>>k1^x>>(k2+1))&1 即可.
(2)统计 1 的数目:*/
int bit_count(unsigned x)//__builtin_popcount(unsigned x);  __builtin_popcountll();
{
	x -= ((x & 0xAAAAAAAAu) >> 1);
	x = ((x & 0xCCCCCCCCu) >> 2) + (x & 0x33333333u);
	x = ((x >> 4) + x) & 0x0F0F0F0Fu;
	x = (x * 0x1010101u) >> 24;
	return x;
}
/*
又是一个基于二分思想的算法, 需要特别注意, 传入的参数 x 的类型是 unsigned.
在进行位运算的子程序中, 推荐全部使用无符号数据类型.
查表法: 预处理0~65535之间的每个数的答案，使用的时候，将x分为高半部分和低半部分查表后相加.
(3)反转位的顺序:*/
unsigned  rev(unsigned  x)
{
	x = ((x & 0xAAAAAAAAu) >> 1) | ((x & 0x55555555u) << 1);
	x = ((x & 0xCCCCCCCCu) >> 2) | ((x & 0x33333333u) << 2);
	x = ((x & 0xF0F0F0F0u) >> 4) | ((x & 0x0F0F0F0Fu) << 4);
	x = ((x & 0xFF00FF00u) >> 8) | ((x & 0x00FF00FFu) << 8);
	x = ((x & 0xFFFF0000u) >> 16) | ((x & 0x0000FFFFu) << 16);
	return x;
}
//前缀0的个数 如: 0x0000fff0u 有16个前缀0
//内建函数 int __builtin_clz (unsigned int x);(x!=0)
int countLeadingZeros_1(unsigned x)
{
	int ans = 0;
	if(x >> 16) x >>= 16;
	else ans |= 16;
	if(x >> 8) x >>= 8;
	else ans |= 8;
	if(x >> 4) x >>= 4;
	else ans |= 4;
	if(x >> 2) x >>= 2;
	else ans |= 2;
	if(x >> 1) x >>= 1;
	else ans |= 1;
	return ans + !x;;
}
//后缀0的个数 如: 0x0000fff0u 有4个前缀0
//内建函数 int __builtin_ctz (unsigned int x); (x!=0)
int countTrailingZeros_1(unsigned x)
{
	int ans = 0;
	if(!(x & 65535u)) x >>= 16, ans |= 16;
	if(!(x & 255u)) x >>= 8, ans |= 8;
	if(!(x & 15u)) x >>= 4, ans |= 4;
	if(!(x & 3u)) x >>= 2, ans |= 2;
	if(!(x & 1u)) x >>= 1, ans |= 1;
	return ans + !x;
}
//__builtin_ffs (unsigned int x) 返回x的最后一位1的是从后向前第几位，比如7368（1110011001000）返回4。

