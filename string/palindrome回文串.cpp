//manacher算法 $O(n)$
/*写法一
预处理:在字符串中加入一个分隔符(不在字符串中的符号),将奇数长度的回文串和偶数长度的回文串统一;
	在字符串之前再加一个分界符(如'&')防止比较时越界*/

void manacher(char* s, int len, int p[])
{
    //s = &s[0]#s[1]#...#s[len]\0
    int i, mx = 0, id;
    for(i = 1; i <= len; i++)
    {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while(s[i + p[i]] == s[i - p[i]]) ++p[i];
        if(p[i] + i > mx) mx = p[i] + (id = i);
        p[i] -= (i & 1) != (p[i] & 1);//去掉分隔符带来的影响
    }
    //此时, p[(i << 1) + 1]为以s[i]为中心的奇数长度的回文串的长度
    //p[(i << 1) + 2]为以s[i]和s[i+1]为中心的偶数长度的回文串的长度
}

/*写法二
将位置在[i,j]的回文串的长度信息存储在p[i+j]上
*/
void manacher2(char* s, int len, int p[])
{
    p[0] = 1;
    for(int i = 1, j = 0; i < (len << 1) - 1; ++i)
    {
        int u = i >> 1, v = i - u, r = ((j + 1) >> 1) + p[j] - 1;
        int u = i >> 1, v = i - u, r = ((j + 1) >> 1) + p[j] - 1;
        p[i] = r < v ? 0 : min(r - v + 1, p[(j << 1) - 1]);
        while(u > p[i] - 1 && v + p[i] < len && s[u - p[i]] == s[u + p[i]]) ++p[i];
        if(u + p[i] - 1 > r) j = i;
    }
}


///回文树 Palindromic Tree
/*功能:
1. 求串s前缀0~i内本质不同的回文串个数
2. 求串是内每一个本质不同的回文串出现的次数
3. 求串s内回文串的个数
4. 求以下标i结尾的回文串个数
空间复杂度: $O(N*字符集大小)$
时间复杂度: $O(N \log{(字符集大小)})$
*/
const int MAXN = 1005;
const int N = 26;
char s[MAXN];
struct PalindromicTree
{
    int next[MAXN][N];//next指针, next指针和字典树类似, 指向的串为当前串两端加上同一个字符构成
    int fail[MAXN];//fail指针, 失配后跳转到fail指针指向的节点
    int cnt[MAXN];//count之后为每种本质不同回文串的方案数
    int num[MAXN];//当前节点通过fail指针到达0节点或1节点的步数(fail指针的深度)
    int len[MAXN];//len[i]表示节点i表示的回文串的长度
    int s[MAXN];//存放添加的字符
    int last;//指向上一个字符所在的节点, 方便下一次add
    int n;//字符数组指针
    int p;//节点指针, p - 2为本质不同的回文串数
    int newnode(int l)     //新建节点
    {
        for(int i = 0; i < N; ++i) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }
    void init()   //初始化
    {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = '#';//开头放一个字符集中没有的字符,减少特判
        fail[0] = 1;
    }
    int get_fail(int x)     //和KMP一样,失配后找一个尽量最长的
    {
        while(s[n - len[x] - 1] != s[n]) x = fail[x];
        return x;
    }
    void add(char c)
    {
		s[++n] = c;
        c -= 'a';
        int cur = get_fail(last);   //通过上一个回文串找这个回文串的匹配位置
        if(!next[cur][c])     //如果这个回文串没有出现过,说明出现了一个新的本质不同的回文串
        {
            int now = newnode(len[cur] + 2);   //新建节点
            fail[now] = next[get_fail(fail[cur])][c];   //和AC自动机一样建立fail指针,以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
		last = next[cur][c];
        cnt[last] ++;
    }
    void count()
    {
        for(int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt,因为如果fail[v]=u,则u一定是v的子回文串!
    }
} run;
//题目:
/*
1. [hdu 5658 CA Loves Palindromic](http://acm.hdu.edu.cn/showproblem.php?pid=5658)
	给出一个长度<= 1000的字符串, 和m(<=10^5)个询问, 每个询问求区间[l,r]中本质不同的回文串数.
	题解: 利用回文树, 对于每个子串S[l, |S|], 建立一次回文树, 建立的过程中就可以求出本质不同的回文串数.
		也可以用manacher算法, 然后求出每个回文串, 用hash去重.
*/
