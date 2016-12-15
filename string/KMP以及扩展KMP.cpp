///KMP
//$O(n + m)$
/*
next[]的含义: $x[i-next[i] \cdots i] = x[0 \cdots next[i] - 1]$
next[i] 为满足$x[i - z \cdots i - 1] = x[0 \cdots z- 1]$的最大z值 (就是x的自身匹配)
*/
void pre_kmp(char x[], int m, int kmpNext[])
{
    int i, j;
    j = kmpNext[i = 0] = -1;
    while(i < m)
    {
        while(j != -1 && x[i] != x[j]) j = kmpNext[j];
        if(x[++i] == x[++j]) kmpNext[i] = kmpNext[j];
        else kmpNext[i] = j;
    }
}

//返回x在y中出现的次数, 可以重叠
//x是模式串, y是文本串
int KMP_Count(char x[], int m, char y[], int n, int next[])
{
    int i = 0, j = 0, ans = 0;
    pre_kmp(x, m, next);
    while(i < n)
    {
        while(j != -1 && y[i] != x[j]) j = next[j];
        ++i, ++j;
        if(j >= m)
        {
            ans++;
            j = next[j];//连续重复匹配
            //j = 0;// 连续不重复匹配
            //return true;//不连续匹配
        }
    }
    return ans;
}

///扩展KMP
/*
复杂度: $O(n + m)$
next[i]: $x[i \cdots m - 1]$与$x[0 \cdots m - 1]$的最长公共前缀
extend[i]: $y[i \cdots n - 1]$与$x[0 \cdots m - 1]$的最长公共前缀
*/
void pre_exkmp(const char x[], int m, int next[])
{
    for(int i = 1, j = -1, k, p; i < m; i++, j--)//i 从1开始, next[0] = m
        if(j < 0 || i + next[i - k] >= p)
        {
            if(j < 0) j = 0, p = i;
            while(p < m && x[p] == x[j]) j++, p++;
            next[k = i] = j;
        }
        else
            next[i] = next[i - k];
}
//x是模式串, y是文本串
void exkmp(char x[], int m, char y[], int n, int next[], int extend[])
{
    pre_exkmp(x, m, next);
    for(int i = 0, j = -1, k, p; i < n; i++, j--)
        if(j < 0 || i + next[i - k] >= p)
        {
            if(j < 0) j = 0, p = i;
            while(p < n && j < m && y[p] == x[j]) j++, p++;
            extend[k = i] = j;
        }
        else
            extend[i] = next[i - k];
}
