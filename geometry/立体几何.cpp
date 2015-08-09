///三维几何
struct Point
{
    double x, y, z;
    Point() {x = y = z = 0;}
    Point(double _x, double _y, double _z) {x = _x, y = _y, z = _z;}
    double operator *(const Point a)const//点积
    {
        return x * a.x + y * b.y + z * b.z;
    }
    Point operator ^(const Point a)const //叉积
    {
        return Point(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.z);
    }
    Point operator *(const double a)const
    {
        x *= a, y *= a, z *= a;
        return *this;
    }
    Point operator /(const double a)const
    {
        x /= a, y /= a, z /= a;
        return *this;
    }
    Point operator + (const Point a)const {return Point(x + a.x, y + a.y, z + a.z);}
    Point operator - (const Point a)const {return Point(x - a.x, y - a.y, z - a.z);}
    double length()
    {
        return sqrt(x * x + y * y + z * z);
    }
};
//四面体体积
double V(Point a, Point b, Point c, Point d)
{
    return ((a - b) ^ (a - c)) * (a - d) / 6.0;
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
    return (a + b + c + d) / 4.0;
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
