///快速沃尔什变换(Fast Wavelet Transform algorithm, FWT)
/*推导:
定义: 正变换tf(X)和逆变换utf(X), X, Y为大小为n一个向量
满足变换需要的性质: utf(tf(X)) = X, tf(X # Y) = tf(X) * tf(Y) (#是X与Y间的卷积运算, *是tf(X)和tf(Y)间的乘法运算)
变换方程: tf(A, B) = (A - B, A + B), (A, B是两个长度相同的向量)
则: tf(A, B) * tf(C, D) = (A - B, A + B) * (C - D, C + D) = tf(AC + BD, AD + BC) = tf((A, B) # (C, D))
所以若n为偶数, 则将X, Y分别拆分成两个相同长度的向量, 然后进行变换.
逆变换方程: utf(A, B) = ((A + B) / 2, (B -A) / 2)
参考: http://apps.topcoder.com/wiki/display/tc/SRM+518
*/
/*
Description: fwt()正变换, ifwt()逆变换
Param[In]: a要变换的数组, [l, r)要变换的区间
Notice: 数组a的大小要为2的幂
(或许)适用: C = A # B 为 C[i^j] += A[i] * A[j] $(0 \leq i, j < n)$
*/
void fwt(int a[], int l, int r)
{
    if(l == r) return ;
    int mid = (l + r) >> 1, len = mid - l + 1;
    fwt(a, l, mid);
    fwt(a, mid + 1, r);
    for(int i = l; i <= mid; ++i)
    {
        int u = a[i], v = a[i + len];
        a[i] = u - v;
        a[i + len] = u + v;
    }
}
void ifwt(int a[], int l, int r)
{
    if(l == r) return ;
    int mid = (l + r) >> 1, len = mid - l + 1;
    for(int i = l; i <= mid; ++i)
    {
        int u = a[i], v = a[i + len];
        a[i] = (v + u) / 2;
        a[i + len] = (v - u) / 2;
    }
    ifwt(a, l, mid);
    ifwt(a, mid + 1, r);
}
/*
题意: 求 $\displaystyle \mbox{XOR} _{i=1}^{2n+1}{(a_i + x)} = 0 (0 \leq a_i \leq m, L \leq x \leq R) $的方案数 (对1000000007取模)
来源: 2015北京网络赛D题
地址: http://hihocoder.com/problemset/problem/1230
*/
