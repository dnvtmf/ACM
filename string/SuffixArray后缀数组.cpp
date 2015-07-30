///后缀数组(Suffix Array)
/*
后缀数组是指将某个字符串的所有后缀按字典序排序后得到的数组
*/
//计算后缀数组
//朴素做法 将所有后缀进行排序$O(n^2\log{n})$采用快排 适用于m比较大的时候
///Manber-Myers $O(n\log^2{n})$
int rk;
int sa[NUM], rank[NUM], height[NUM];
int cmp(int i, int j)
{
    if(rank[i] != rank[j])
        return rank[i] < rank[j];
    else
    {
        int ri = i + rk <= n ? rank[i + rk] : -1;
        int rj = i + rk <= n ? rank[j + rk] : -1;
        return ri < rj;
    }
}
void da(int *a, int n)
{
    int i;
    a[n] = -1;
    for(i = 0; i <= n; i++)
    {
        sa[i] = i;
        rank[i] = a[i];
    }
    for(m = 1; rank[n] < n; m <<= 1)
    {
        sort(sa, sa + n + 1, cmp);
        tmp[sa[0]] = 0;
        for(i = 1; i <= n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i], sa[i - 1] || cmp(sa[i - 1], sa[i])));
        for(i = 0; i <= n; i++)
            rank[i] = tmp[i];
    }
}

//应用
//基于后缀数组的字符串匹配
bool contain(string s, int *sa, string t)
{
    int a = 0, b = s.length();
    while(b - a > 1)
    {
        int c = (a + b) / 2;
        if(s.compare(sa[c], t.length(), t) < 0)a = c;
        else
            b = c;
    }
    return s.compare(sa[b], t.length(), t) == 0;
}

///倍增法模板: $O(n\log{n})$采用基数排数
//n为字符个数 r[n - 1] 要比所有a[0, n - 2]要小
//r 字符串对应的数组
//m为最大字符值+1
int sa[maxn];
int rank[maxn], height[maxn], sn[maxn], sv[maxn];
void da(char *r, int *sa, int n, int m)
{
    int i, j, p, *x = rank, *y = height, *t;
    for(i = 0; i < m; i++) sn[i] = 0;
    for(i = 0; i < n; i++) sn[x[i] = r[i]]++;
    for(i = 1; i < m; i++) sn[i] += sn[i - 1];
    for(i = n - 1; i >= 0; i--) sa[--sn[x[i]]] = i;
    for(j = 1, p = 1; p < n; j <<= 1, m = p)
    {
        for(p = 0, i = n - j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i = 0; i < n; i++) sv[i] = x[y[i]];
        for(i = 0; i < m; i++) sn[i] = 0;
        for(i = 0; i < n; i++) sn[sv[i]]++;
        for(i = 1; i < m; i++) sn[i] += sn[i - 1];
        for(i = n - 1; i >= 0; i--) sa[--sn[sv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) ? p - 1 : p++;
    }
}
///DC3模板: $O(3n)$
int sa[NUM * 3], r[NUM*3];//sa数组和r数组要开三倍大小的空间
int rank[NUM], height[NUM], sn[NUM], sv[NUM];
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
int cmp0(int r[], int a, int b)
{return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];}
int cmp12(int r[], int a, int b, int k)
{
    if(k == 2) return r[a] < r[b] || (r[a] == r[b] && cmp12(r, a + 1, b + 1, 1));
    else return r[a] < r[b] || (r[a] == r[b] && sv[a + 1] < sv[b + 1]);
}
void sort(int r[], int a[], int b[], int n, int m)//基数排序
{
    int i;
    for(i = 0; i < m; i++) sn[i] = 0;
    for(i = 0; i < n; i++) sn[sv[i] = r[a[i]]]++;
    for(i = 1; i < m; i++) sn[i] += sn[i - 1];
    for(i = n - 1; i >= 0; i--) b[--sn[sv[i]]] = a[i];
}
void dc3(int r[], int sa[], int n, int m)
{
    int *rn = r + n, *san = sa + n, *wa = height, *wb = rank;
    int i, j, p, ta = 0, tb = (n + 1) / 3, tbc = 0;
    r[n] = r[n + 1] = 0;
    for(i = 0; i < n; i++) if(i % 3 != 0) wa[tbc++] = i;
    sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for(p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = cmp0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if(p < tbc) dc3(rn, san, tbc, p);
    else for(i = 0; i < tbc; i++) san[rn[i]] = i;
    for(i = 0; i < tbc; i++) if(san[i] < tb) wb[ta++] = san[i] * 3;
    if(n % 3 == 1) wb[ta++] = n - 1;
    sort(r, wb, wa, ta, m);
    for(i = 0; i < tbc; i++) sv[wb[i] = G(san[i])] = i;
    for(i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = cmp12(r, wa[i], wb[j], wb[j] % 3) ? wa[i++] : wb[j++];
    for(; i < ta; p++) sa[p] = wa[i++];
    for(; j < tbc; p++) sa[p] = wb[j++];
}

///高度数组
//height[i] = suffix(sa[i])和suffix(sa[i - 1])的最长公共前缀lcp(sa[i],sa[i-1])
//rank[0..n-1]:rank[i]保存的是原串中suffix[i]的名次
//height数组性质:
//任意两个suffix(j)和suffix(k)(rank[j] < rank[k])的最长公共前缀: min(i=j+1-->k){height[rank[i]]}
//height[i] >= height[i - 1] - 1
int rank[maxn], height[maxn];
void calheight(char *r, int *sa, int n)
{
    int i, j, k = 0;
    for(i = 0; i < n; i++)rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i++]] = k)
        for(k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
}
///后缀数组应用
//询问任意两个后缀的最长公共前缀: RMQ问题, min(i=j+1-->k){height[rank[i]]}
//重复子串: 字符串R在字符串L中至少出现2次, 称R是L的重复子串
//可重叠最长重复子串: $O(n)$ height数组中的最大值
//不可重叠最长重复子串: $O(n\log{n})$变为二分答案, 判断是否存在两个长度为k的子串是相同且不重叠的. 将排序后后缀分为若干组, 其中每组的后缀的height值都不小于k, 然后有希望成为最长公共前缀不小于k的两个后缀一定在同一组, 然后对于每组后缀, 判断sa的最大值和最小值之差不小于k, 如果一组满足, 则存在, 否则不存在.
//可重叠的k次最长重复子串: $O(n\log{n})$ 二分答案, 将后缀分为若干组, 判断有没有一个组的后缀个数不小于k.
//不相同的子串个数: 等价于所有后缀之间不相同的前缀的个数O(n): 后缀按suffix(sa[1]), suffix(sa[2]), $\cdots$, suffix(n)的顺序计算, 新进一个后缀suffix(sa[k]), 将产生n - sa[k] + 1的新的前缀, 其中height[k]的和前面是相同的, 所以suffix(sa[k])贡献n - sa[k] + 1 - height[k]个不同的子串. 故答案是$\sum_{k=1}^{n}{n - sa[k] - 1 - height[k]}$.
//最长回文子串: 字符串S(长度n)变为字符串+特殊字符+反写的字符串, 求以某字符(位置k)为中心的最长回文子串(长度为奇数或偶数), 长度为: 奇数lcp(suffix(k), suffix(2*n + 2 - k)); 偶数lcp(suffix(k), suffix(2*n + 3 - k)) $O(n\log{n})$ RMQ:O(n)
//连续重复子串: 字符串L是有字符串S重复R次得到的.
//给定L, 求R的最大值: O(n), 枚举S的长度k, 先判断L的长度是否能被k整除, 在看lcp(suffix(1), suffix(k+1))是否等于n - k. 求解时只需预处理height数组中的每一个数到height[rank[1]]的最小值即可
//给定字符串, 求重复次数最多的连续重复子串$O(n\log{n})$: 先穷举长度L, 然后求长度为L的子串最多能连续出现几次. 首先连续出现1次是肯定可以的, 所以这里只考虑至少2次的情况. 假设在原字符串中连续出现2次, 记这个子字符串为S, 那么S肯定包括了字符r[0], r[L], r[L*2], r[L*3], $\cdots$中的某相邻的两个. 所以只须看字符r[L*i]和r[L*(i+1)]往前和往后各能匹配到多远, 记这个总长度为K, 那么这里连续出现了K/L+1次. 最后看最大值是多少.
//字符串A和B最长公共前缀O(|A|+|B|): 新串: A+特殊字符$+B, 答案为排名相邻且属于不同的字符串的height的最大值
//长度不小于k的公共子串的个数: 连接两串A+$+B, 对后缀数组分组(每组height值都不小于k), 每组中扫描到B时, 统计与前面的A的后缀能产生多少个长度不小于k的公共子串, 统计得结果.
//给定n个字符串, 求出现在不小于k个字符串中的最长子串$O(n\log{n})$: 连接所有字符串, 二分答案, 然后分组, 判断每组后缀是否出现在至少k个不同的原串中.
//给定n个字符串, 求在每个字符串中至少出现两次且不重叠的最长子串$O(n\log{n})$: 做法同上, 也是先将n个字符串连起来, 中间用不相同的且没有出现在字符串中的字符隔开, 求后缀数组. 然后二分答案, 再将后缀分组. 判断的时候, 要看是否有一组后缀在每个原来的字符串中至少出现两次, 并且在每个原来的字符串中, 后缀的起始位置的最大值与最小值之差是否不小于当前答案(判断能否做到不重叠, 如果题目中没有不重叠的要求, 那么不用做此判断).
//给定n个字符串, 求出现或反转后出现在每个字符串中的最长子串: 只需要先将每个字符串都反过来写一遍, 中间用一个互不相同的且没有出现在字符串中的字符隔开, 再将n个字符串全部连起来, 中间也是用一个互不相同的且没有出现在字符串中的字符隔开, 求后缀数组. 然后二分答案, 再将后缀分组. 判断的时候, 要看是否有一组后缀在每个原来的字符串或反转后的字符串中出现. 这个做法的时间复杂度为$O(n\log{n})$.
