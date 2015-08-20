///最小表示法 Minimum Representation
//对于一个字符串S, 求S的循环的同构字符串S’中字典序最小的一个
//$O(|S|)$
int MinimumRepresentation(char *s, int len)
{
    int i = 0, j = 1, k = 0, t;
    while(i < len && j < len && k < len)
    {
        t = s[(i + k) >= len ? i + k - len : i + k] - s[(j + k) >= len ? j + k - len : j + k];
        if(!t) k++;
        else
        {
            if(t > 0) i = i + k + 1;
            else j = j + k + 1;
            if(i == j) ++j;
            k = 0;
        }
    }
    return (i < j ? i : j);
}
