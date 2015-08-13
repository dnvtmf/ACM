///三维几何
///点
inline int sgn(double x) {if(x < -EPS)return -1; return x > EPS ? 1 : 0;}
struct Point
{
    double x, y, z;
    Point(double _x = 0.0, double _y = 0.0, double _z = 0.0) {x = _x, y = _y, z = _z;}
    void in() {scanf("%lf%lf%lf", &x, &y, &z);}
    double operator *(const Point b)const {return x * b.x + y * b.y + z * b.z;} //点积
    Point operator ^(const Point b)const {return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);}//叉积
    Point operator *(const double b)const {return Point(x * b, y * b, z * b);}//标量乘
    Point operator + (const Point b)const {return Point(x + b.x, y + b.y, z + b.z);}//向量加
    Point operator - (const Point b)const {return Point(x - b.x, y - b.y, z - b.z);}//向量减
    Point rot(double ang){}
};
//判断四点共面(coplanar)
bool is_coplanar(Point p[4])
{
    Point normal = (p[0] - p[1]) ^ (p[1] - p[2]); //求前三点的法向量
    return sgn(normal * (p[3] - p[0])) == 0; //判断与第四点的连线是否与法向量垂直
}

///线
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
    //
//	Point res;
//	res.x = (a.x + b.x + c.x + d.x)/4.0;
//	res.y = (a.y + b.y + c.y + d.y)/4.0;
//	res.z = (a.z + b.z + c.z + d.z)/4.0;
//	return res;
    return (a + b + c + d) * 0.25;
}
//多面体的重心
//将多面体分解为若干个四面体, 重心为体积的加权和 zhongxin = (v1*zx1 + v2*zx2 + ... + vn*zxn)/(v1 + v2 + ... + v3)

//空间三角形的面积
double Area(Point a, Point b, Point c)
{
    return (a - b) * (a - c);
}
//点到平面的距离 h = 3.0*V/S
Point dis(Point p, Point a, Point b, Point c)
{
    return fabs(3.0 * V(p, a, b, c) / S(a, b, c));
}
