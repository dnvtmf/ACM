///矩阵的初等变换和矩阵的逆
const int Matrix_N = 1010, Matrix_M = 1010;
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
struct Matrix {
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
			for(int j = 0; j < b.m; j++) {
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
		for(in i = 0; i < n; i++) {
			for(int j = i; j < n; j++)
				if(fabs(a[j][i]) > 0) {
					swap(a[i], a[j]);
					swap(c[i], c[j]);
					break;
				}
			c[i] = c[i] * (1.0 / a[i][i]);
			a[i] = a[i] * (1.0 / a[i][i]);
			for(int j = 0; j < n; j++)
				if(j != i && fabs(a[j][i]) > 0) {
					c[j] = c[j] - a[i] * a[j][i];
					a[j] = c[j] - a[i] * a[j][i];
				}
		}
	}
};
//Gauss消元
///解n元一次方程: $\vec{A}_{n \times m} \vec{x}_{1 \times n} = \vec{y}_{1 \times m}$
///其中$\vec{A}$是系数矩阵, $\vec{x}$是变量, $\vec{y}$ 是方程的常数项
int Gauss(double a[][MAXN], bool l[], double ans[], int n)
{
	//l, ans储存解, l[]表示是否是自由元
	int res = 0, r = 0;
	for(int i = 0; i < n; i++) l[i] = false;
	for(int i = 0; i < n; i++) {
		for(int j = r; j < n; j++)
			if(fabs(a[j][i]) > EPS) {
				for(int k = i; k <= n; k++)
					swap(a[j][k], a[r][k]);
				break;
			}
		if(fabs(a[r][i]) < EPS) {
			++res;
			continue;
		}
		for(int j = 0; j < n; j++)
			if(j != r && fabs(a[j][i]) > EPS) {
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

