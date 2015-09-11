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
*/

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
