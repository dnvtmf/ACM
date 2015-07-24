//manacher算法 $O(n)$
/*写法一
预处理：在字符串中加入一个分隔符（不在字符串中的符号），将奇数长度的回文串和偶数长度的回文串统一;
	在字符串之前再加一个分界符（如'&'），防止比较时越界*/

void manacher(char *s, int len, int p[])
{//s = &s[0]#s[1]#...#s[len]\0
	int i, mx = 0, id;
	for(i = 1; i <= len; i++)
	{
		p[i] = mx > i ? min(p[2*id - i], mx - i) : 1;
		while(s[i + p[i]] == s[i - p[i]]) ++p[i];
		if(p[i] + i > mx) mx = p[i] + (id = i);
		p[i] -= (i & 1) != (p[i] & 1);//去掉分隔符带来的影响
	}
	//此时, p[(2<<i) + 1]为以s[i]为中心的奇数长度的回文串的长度
	//p[(2<<i)]为以s[i]和s[i+1]为中心的偶数长度的回文串的长度
}

/*写法二
将位置在[i,j]的回文串的长度信息存储在p[i+j]上
*/
void manacher2(char *s, int len, int p[])
{
	p[0] = 1;
	for(int i = 1, j = 0; i < (len<<1) - 1; ++i)
	{
	    int u = i >> 1, v = i - u, r = ((j + 1) >> 1) + p[j] - 1;
	    int u = i >> 1, v = i - u, r = ((j + 1) >> 1) + p[j] - 1;
		p[i] = r < v ? 0 : min(r - v + 1, p[(j<<1) - 1]);
		while(u > p[i] - 1 && v + p[i] < len && s[u - p[i]] == s[u + p[i]]) ++p[i];
		if(u + p[i] - 1 > r) j = i;
	}
}
