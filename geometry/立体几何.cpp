///三维几何
///点
inline int sgn(double x)
{
	if(x < -EPS)return -1;
	return x > EPS ? 1 : 0;
}
struct Point {
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
	void in() {scanf("%lf%lf%lf", &x, &y, &z);}
	double operator *(const Point &b)const
	{
		return x * b.x + y * b.y + z * b.z;   //点积
	}
	Point operator ^(const Point &b)const
	{
		return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);   //叉积
	}
	Point operator *(const double &b)const
	{
		return Point(x * b, y * b, z * b);   //标量乘
	}
	Point operator + (const Point &b)const
	{
		return Point(x + b.x, y + b.y, z + b.z);   //向量加
	}
	Point operator - (const Point &b)const
	{
		return Point(x - b.x, y - b.y, z - b.z);   //向量减
	}
	double length()
	{
		return sqrt(x * x + y * y + z * z);
	}
	bool operator == (const Point &b) const
	{
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
	}
	Point rot(double ang) {}
};
/*点的坐标变换
平移: 点(x, y, z)平移(tx, ty, tz)到(x + tx, y + ty, z + tz)
    变换矩阵:   @$$\left[ \begin{matrix}{
    1   &0  &0  &0  \cr
    0   &1  &0  &0  \cr
    0   &0  &1  &0  \cr
    tx  &ty &tz &1
    } \end{matrix} \right]$$@
缩放: 坐标(x, y, z)缩放为 (ax, by, cz)
    缩放矩阵:   @$$\left[ \begin{matrix}{
    a   &0  &0  &0  \cr
    0   &b  &0  &0  \cr
    0   &0  &c  &0  \cr
    0   &0  &0  &1
    } \end{matrix} \right]$$@
旋转: 点$(x_0, y_0, z_0)$绕原点(0, 0, 0) 到 $(x, y, z)$ 的单位向量逆时针旋转 $\theta$ 弧度
    旋转矩阵:   @$$\left[ \begin{matrix}{
        \cos \theta + (1 - \cos \theta) x^2
    &   (1 - \cos \theta) y x + (\sin \theta) z
    &   (1 - \cos \theta) z x - (\sin \theta) y
    &   0
    \cr

        (1 - \cos \theta) x y - (\sin \theta) z
    &   \cos \theta + (1 - \cos \theta) y^2
    &   (1 - \cos \theta) z y + (\sin \theta) x
    &   0
    \cr
        (1 - \cos \theta) x z + (\sin \theta) y
    &   (1 - \cos \theta) y z - (\sin \theta) x
    &   \cos \theta + (1 - \cos \theta) z^2
    &   0
    \cr
        0
    &   0
    &   0
    &   1
    } \end{matrix} \right]$$@
使用: 行向量$[x, y, z, 1] \times A$, A为变换矩阵
*/
//混合积
double mul(Point &A, Point &B, Point &C)
{
	return A * (B ^ C);
}
//判断四点共面(coplanar)
bool is_coplanar(Point p[4])
{
	Point normal = (p[0] - p[1]) ^ (p[1] - p[2]); //求前三点的法向量
	return sgn(normal * (p[3] - p[0])) == 0; //判断与第四点的连线是否与法向量垂直
}

///线
//两直线AB与CD垂直
bool is_lines_vertical(Point A, Point B, Piont C, Point D)
{
	return sgn((B - A) * (D - C)) == 0;
}
//两直线共面
bool is_lines_in_plane(Point A, Point B, Point C, Point D)
{
	return sgn(mul(B - C, A - B, C - D)) == 0;
}
//两直线平行
bool is_lines_parallel(Point A, Point B, Point C, Point D)
{
	return sgn(((B - A) ^ (C - D)).length()) == 0;
}
//两直线交点
bool lines_cross(Point A, Point B, Point C, Point D, Point &res)
{
	if(!is_lines_in_plane(A, B, C, D))
		return false;
	if(is_lines_parallel(A, B, C, D))
		return false;
	Point AB = A - B;
	Point CD = C - D;
	double t1 = Cross(B - C, CD).length() / Cross(CD, AB).length();
	double t2 = Cross(C - B, AB).length() / Cross(AB, CD).length();
	Point P1 = A + AB * t1;
	Point P2 = A - AB * t1;
	Point P3 = C + CD * t2;
	Point P4 = C - CD * t2;
	if(P1 == P3 || P1 == P4)
		res = P1;
	else
		res = P2;
	return true;
}
///面Plane
//三点确定一个平面, 其法向量(normal vector)为:
Point getPlaneNormal(Point a, Point b, Point c)
{
	return (a - b) ^ (a - c);
}
///体
//四面体体积
double V(Point a, Point b, Point c, Point d)
{
	return ((a - b) ^ (a - c)) * (a - d) * (1.0 / 6.0);
}
//四面体重心
Point zhongxin(Point a, Point b, Point c, Point d)
{
//	Point res;
//	res.x = (a.x + b.x + c.x + d.x)/4.0;
//	res.y = (a.y + b.y + c.y + d.y)/4.0;
//	res.z = (a.z + b.z + c.z + d.z)/4.0;
//	return res;
	return (a + b + c + d) * 0.25;
}
//多面体的重心
//将多面体分解为若干个四面体, 重心为体积的加权和 $p = \frac{(V_1 p_1 + V_2 p_2 +\cdots + V_m p_n)}{V_1 + V_2 + \cdots + V_n}$

//空间三角形的面积
double Area(Point a, Point b, Point c)
{
	return (a - b) * (a - c);
}
//点到平面的距离 $h = 3.0 \frac{V}{S}$
Point dis(Point p, Point a, Point b, Point c)
{
	return fabs(3.0 * V(p, a, b, c) / S(a, b, c));
}
