///异或Xor
/*
性质:	1. $0 \xor 1 = 0, 1 \xor 0 = 1, 0 \xor 0 = 0, 1 \xor 1 = 1$
		2. (交换律) $a \xor b = b \xor a$
		3. (结合律) $(a \xor b) \xor c = a \xor (b \xor c)$
		4. $a \xor a = 0$
		5. $0 \xor a = a$
		6. (二进制分解) $\displaystyle a \xor b = \sum_{i=0}^{\infty}{a_i \xor b_i}$, 其中 $a_i, b_i$是数a, b的二进制表达的第i位
			不同位置上运算互不影响
		7. 若a为偶数, 则 $a \xor (a + 1) = 1, a \xor 1 = (a + 1), (a + 1) \xor 1 = a$

应用:
	1.	从N个M位的二进制数中选出两个数, 是XOR和最大.
		解法: 建立二进制树, 枚举第一个数, 在二进制树中找到最大值. $O(MN)$
	2.	N个边带权的树, 找到一条路径是XOR和最大.
		解法: 设根root到点u的路径的XOR和为$XOR_u$, 点x和点y间路径的XOR和为 $XOR_x \xor XOR_y$. 然后转化为应用1.
	3. 	从N个M位的二进制数中选出任意多个数, 使异或和最大.
		解法: 列N个进行高斯消元, 得出答案. $O(MN)$
	4.	从N个M位的二进制数中选出任意多个数, 使他们与K的异或和最大.
		解法: 转化为应用3(应用3中K= 0)
	5.	给一个赋权无向图, 求其从s点到t点的所有路径中最大的权值异或和.
		解法: 令K=任意一条从s到t的路径的权值异或和, 求出所有基本环的异化和, 转化为应用4.
*/
//应用4:
LL gauss(LL N, LL M, LL Xor[], LL K)
{
    int ret = 0;
    for(int i = M; i >= 0; i--)
    {
        int idx = -1;
        for(int j = ret; j < N; j++) if((Xor[j] >> i) & 1)
            {
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
//如: 101的子集有 101, 100, 001, 000
void SubSet(int x)
{
    for(int i = x; ; i = (i - 1) & x)
    {
        //do someting
        if(!i) break;
    }
}
///求最后一个1所在的位置
//如lowbit(10010) = 10
void lowbit(int x)
{
    return x & (-x);
}
///枚举${1, 2, \cdots, (1<<n) - 1}$中1的个数为k的所有元素$(k \neq 0)$
void kSubSet(int n, int k)
{
    int x = (1 << k) - 1;
    while(x < (1 << n))
    {
        //do something
        int tx = x & -x, ty = tx + x;
        x = (((x ^ ty) >> 2) / tx) | ty;
    }
}
