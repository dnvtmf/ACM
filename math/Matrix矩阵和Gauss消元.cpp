///矩阵 Matrix
const int Matrix_N = 1010, Matrix_M = 1010;
//矩阵类, 适用于递推关系式的快速求值
struct Matrix
{
	int n, m;//矩阵的行数和列数
	int a[Matrix_N][Matrix_M];
	void clear()//将矩阵清0
	{
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	void I()//将矩阵化为单位矩阵, 对方阵有效
	{
		memset(a, 0, sizeof(a));
		for(int i = 0; i < n; i++) a[i][i] = 1;
	}
	//实现矩阵加法$C = A + B, (A.n = B.n, A.m = B.m) O(n^2)$
	Matrix operator + (const Matrix &b) const
	{
		Matrix c;
		c.n = n;
		c.m = m;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				c.a[i][j] = a[i][j] + b.a[i][j];
		return c;
	}
	//实现矩阵的减法$C = A - B(A.n = B.n, A.m = B.m), O(n^2)$
	Matrix operator - (const Matrix &b) const 
	{
		Matrix c;
		c.n = n;
		c.m = m;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				c.a[i][j] = a[i][j] - b.a[i][j];
		return c;
	}
	//实现矩阵的乘法$C = A \times B, (A.m = B.n) O(n^3)$
	Matrix operator * (const Matrix &b) const
	{
		Matrix c;
		c.n = n;
		c.m = b.m;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < b.m; j++)
			{
				c.a[i][j] = 0;
				for(int k = 0; k < m; k++)
					c.a[i][j] += a[i][j] * b.a[i][j];//如果要取模， 要修改这里
			}
		return c;
	}
	//实现矩阵的快速幂$O(n^3\log(k)$, 要求是方阵
	Matrix operator ^(int k)
	{
		Matrix res, tmp = *this;
		res.n = res.m = n;
		res.I();
		while(k)
		{
			if(k&1) res = res * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return res;
	}
};
//矩阵类 适用与求矩阵的逆与高斯消元等场合
//行的初等变换
typedef vector<double> VD;
VD operator * (const VD &a, const double b)
{
	int _n = a.size();
	VD c(_n);
	for(int i = 0; i < _n; i++)
		c[i] = a[i] * b;
	return c;
}
VD operator - (const VD &a, const VD &b)
{
	int _n = a.size();
	VD c(_n);
	for(int i = 0; i < _n; i++)
		c[i] = a[i] - b[i];
	return c;
}
VD operator + (const VD &a, const VD &b)
{
	int _n = a.size();
	VD c(_n);
	for(int i = 0; i < _n; i++)
		c[i] = a[i] + b[i];
	return c;
}
struct Matrix
{
	int n, m;
	VD *a;
	void Matrix(int _n = Matrix_N, int _m = Matrix_M)
	{
		n = _n, m = _m;
		a = new VD[n];
		for(int i = 0; i < n; i++)
			a[i].resize(m, 0);
	}
	void ~Matrix()
	{
		delete []a;
	}
	void clear()//0矩阵
	{
		for(int i = 0; i < n; i++)
			a[i].assign(0);
	}
	void I()//单位矩阵
	{
		clear();
		for(int i = 0; i < n; i++)
			a[i][i] = 1;
	}
	//矩阵加法, 同上
	Matrix operator + (const Matrix &b) const
	{
		Matrix c(n, m);
		for(int i = 0; i < n; i++)
			c.a[i] = a[i] + b.a[i];
		return c;
	}
	Matrix operator - (const Matrix &b) const //矩阵减法
	{
		Matrix c(n, m);
		for(int i = 0; i < n; i++)
			c.a[i] = a[i] - b.a[i];
		return c;
	}
	Matrix operator * (const Matrix &b) const //矩阵乘
	{
		Matrix c(n, b.m);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < b.m; j++)
			{
				c[i][j] = 0;
				for(int k = 0; k < m; k++)
					c.a[i][j] += a[i][j] * b.a[i][j];
			}
		return c;
	}
	
	//实现求矩阵的逆$O(n^3)$
	//将原矩阵A和一个单位矩阵I做一个大矩阵$(A, I)$, 用行的初等变换将大矩阵中的A变为I, 将会的到$(I, A^{-1})$的形式
	//注意:  
	Matrix inverse()
	{
		Matrix c;
		c.I();
		for(in i = 0; i < n; i++)
		{
			for(int j = i; j < n; j++)
				if(fabs(a[j][i]) > 0)
				{
					swap(a[i], a[j]);
					swap(c[i], c[j]);
					break;
				}
			c[i] = c[i] * (1.0 / a[i][i]);
			a[i] = a[i] * (1.0 / a[i][i]);
			for(int j = 0; j < n; j++)
				if(j != i && fabs(a[j][i]) > 0)
				{
					c[j] = c[j] - a[i] * a[j][i];
					a[j] = c[j] - a[i] * a[j][i];
				}
		}
	}
};
//Guass消元
int Guass(double a[][MAXN], bool l[], double ans[], int n)
{//l, ans储存解, l[]表示是否是自由元
	int res = 0, r = 0;
	for(int i = 0; i < n; i++) l[i] = false;
	for(int i = 0; i < n; i++)
	{
		for(int j = r; j < n; j++)
			if(fabs(a[j][i]) > EPS)
			{
				for(int k = i; k <= n; k++)
					swap(a[j][k], a[r][k]);
				break;
			}
		if(fabs(a[r][i]) < EPS)
		{
			++res;
			continue;
		}
		for(int j = 0; j < n; j++)
			if(j != r && fabs(a[j][i]) > EPS)
			{
				double tmp = a[j][i] / a[r][i];
				for(int k = i; k <= n; k++)
					a[j][k] -= tmp * a[r][k];
			}
		l[i] = true;
		++r;
	}
	for(int i = 0; i < n; i++)
		if(l[i])
			for(int j = 0; j < n; j++)
				if(fabs(a[j][i]) > 0)
					ans[i] = a[j][n] / a[j][i];
	return res;//返回解空间的维数
}
//常系数线性齐次递推
/*已知$f_x = a_0 f_{x-1} + a_1 f_{x-2} + \cdots a_{n-1}f_{x-n}$和$f_0, f_1, \cdots, f_{n-1}$, 给定t, 求$f_t$
f的递推可以看做是一个$n\times n$的矩阵A乘以一个n维列向量$\beta$, 即
@$$A = \left[ \matrix{
0 &1 &0 &\cdots &0 \cr
0 &0 &0 &\cdots &0 \cr
&\vdots & &\ddots &\vdots \cr
0 &0 &0 &\cdots &1\cr
a_{n-1} &a_{n-2} &a_{n-3} &\cdots &a_0
}\right], 
\beta_n = \left[ \matrix{
f_{x-n} \cr f_{x - n + 1} \cr \vdots \cr f_{x-2} \cr f_{x-1}
}\right]$$@
则$\beta_{t} = A^{t-n+1} \beta_{0}(t \geq n)$
*/
