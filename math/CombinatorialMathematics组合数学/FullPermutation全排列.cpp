//全排列Full permutation
//排列数为n!
//求全排列
//next_permutation求下一个排列, 如果是最后一个排列则返回false
void FullPermutation()
{
    //求所有全排列需排好序
    do
    {
        //do someting
    }
    while(next_permutation(perm2, perm2 + n));
}
/*对于按字典的顺序给出的排列, 有一个排列生成下一个排列的算法如下:
1.  求满足关系式$p_{j-1} < p_j$的j的最大值, 设为i, 即: $i = \max{\{j | p_{j-1} < p_j\}}$
2.  求满足关系式$p_{i-1} < p_k$的k的最大值, 设为j, 即: $j = \max{\{k | p_{i-1} < p_k\}}$
3.  $p_{i-1}$与$p_j$互换位置, 得到$p' = p_1 p_2 \cdots p_n$
4.  将得到的排列$p' = p_1 p_2 \cdots p_{i-1} p_i p_{i+1} \cdots p_n$中$p_i p_{i+1} \cdots p_n$部分倒序, 所得排列$p'' = p_1 p_2 \cdots p_{i-1} p_n \cdots p_{i+1} p_i$就是所求排列.
例: 求p=3421的下一个排列
    1. $i = \max{\{j | p_{j-1} < p_j\}} = 2$
    2. $j = \max{\{k | p_{i-1} < p_k\}} = 2$
    3. p' = 4321
    4. p'' = 4123
*/
/*从集合$\{1, 2, \cdots n\}$的一个r-组合求出下一个r-组合:
1.  求满足不等式$C_j < n - r + j$的最大下标i, 即: $i = \max{\{j | C_j < n - r + j\}}$
2.  $C_i = C_i + 1$
3.  $C_{j+1} = C_j + 1, j = i + 1, i + 2, \cdots r$.
*/

///康托展开
//[0, n! - 1]之间的任意整数X, 都可唯一的表示为: $X = a_{n - 1} (n-1)! + a_{n-2} (n-2)! + \cdots +a_i i! + \cdots + a_2 \cdot 2! + a_1 \cdot 1!$
//其中, a为整数, 并且$0 \leq a_i \leq i (1 \leq i \leq n - 1)$. 这就是康托展开.
//应用
//1~n的全排列中某一排列在所有排列中的位置
//字典序比排列P小的排列个数为：$\displaystyle X_P = \sum_{i=1}^{n}{count_{j=i+1}^{n}{\{a[j] < a[i]} \times (n - i - 1)!\}}$
//例: {1, 3, 2, 4}在1~4的所有全排列的位置为 $(X_P = 0 \times 3! + 1 \times 2! + 0 \times 1! + 0 \times 1!) + 1 = 3$
const int PermSize = 12;
long long fac[PermSize] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};//n!
long long Cantor(int s[], int n)
{
    int i, j, temp;
    long long num = 0;
    for(i = 0; i < n; i++)
    {
        temp = 0;
        for(int j = i + 1; j < n; j++)
        {
            if(s[j] < s[i])
                temp++; //判断几个数小于它
        }
        num += fac[n - i - 1] * temp; //(或num=num+fac[n-i-1]*temp;)
    }
    return num + 1;
}


//逆运算 逆康托展开
//已知1~n的全排列中的某一排列permutation在所以全排列中的位置，求该排列
//第pos个排列，$a_i$为排除$a_1, \cdots, a_{i - 1}$后第$\frac{(pos - 1)\%(n - i)!}{(n - i - 1)!} + 1$小的数字
/*例：求1~4的排列中的第3个排列:
    $\frac{2}{3!}=0 \cdots 2, p_0 = 1$(1, 2, 3, 4第1小的数);
    $\frac{2}{2!}=1 \cdots 0, p_1 = 3$(2, 3, 4第2小的数);
    $\frac{0}{1!}=0 \cdots 0, p_2 = 2$(2, 4第1小的数);
    $\frac{0}{0!}=0 \cdots 0, p_3 = 4$(4第1小的数);
    故第3个的排列为{1,3,2,4}
*/
int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int perm[9];
void unContor(int pos, int n)
{
    int i, j;
    bool vis[12] = {0};
    pos--;
    for(i = 0; i < n; i++)
    {
        int t = sum / fac[n - i - 1];
        for(j = 1; t && j <= n; j++)
            if(!vis[j]) t--;
        vis[perm[i] = j] = 1;
        sum %= fac[n - i - 1];
    }
}
