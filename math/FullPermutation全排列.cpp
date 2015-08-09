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

///康托展开
//把一个整数X展开成如下形式: $X=a_n (n-1)! + a_{n-1} (n-2)! + \cdots +a_i (i-1)! + \cdots + a_2 \cdot 1! + a_1 \cdot 0!$
//其中, a为整数, 并且$0 \leq a_i < i (1 \leq i \leq n)$. 这就是康托展开.
//应用
//1~n的全排列中某一排列在所有排列中的位置
//字典序比排列P小的排列个数为：$\displaystyle X_P = \sum_{i=1}^{n}{count_{j=i+1}^{n}{a[j] < a[i]} \times (n - i - 1)!}$
//例: {1, 3, 2, 4}在1~4的所有全排列的位置为($X_P = 0 \times 3! + 1 \times 2! + 0 \times 1! + 0 \times 1!) + 1 = 3$
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
//第pos个排列，a[i]为排除$a[1 \cdots i - 1]$后第((pos - 1)%(n - i)!)/(n - i - 1)! + 1小的数字
//例：1~4中第3大的数为:2/3!=0...2, p[0] = 1(1, 2, 3, 4第1小的数); 2/2!=1...0, p[1]=3(2, 3, 4第2小的数; 0/1!=0...0, p[2]=2{2,4第1小的数}; 0/0!=0...0, p[3]=4{4第1小的数};　故第3个的排列为{1,3,2,4}
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
