/// 多边形
//*判断点在凸多边形内
//点形成一个凸包, 而且按逆时针排序 (如果是顺时针把里面的 < 0改为 > 0)
//点的编号: 0~n-1
//返回值: -1: 点在凸多边形外; 0: 点在凸多边形边界上; 1: 点在凸多边形内
int inConvexPoly(Point a, Point p[], int n)
{
    p[n] = p[0];
    for(int i = 0; i < n; i++)
    {
        if(sgn((p[i] - a) ^ (p[i + 1] - a)) < 0)return -1;
        else if(OnSeg(a, Line(p[i], p[i + 1])))return 0;
    }
    return 1;
}
//*判断点在任意多边形内
//射线法, poly[]的顶点数要大于等于3,点的编号0~n-1
//返回值
//-1:点在凸多边形外
//0:点在凸多边形边界上
//1:点在凸多边形内
int inPoly(Point p, Point poly[], int n)
{
    int cnt;
    Line ray, side;
    cnt = 0;
    ray.s = p;
    ray.e.y = p.y;
    ray.e.x = -100000000000.0;//-INF,注意取值防止越界
    for(int i = 0; i < n; i++)
    {
        side.s = poly[i];
        side.e = poly[(i + 1) % n]; //*判断点在任意多边形内
        if(OnSeg(p, side))return 0;
        //如果平行轴则不考虑
        if(sgn(side.s.y - side.e.y) == 0)
            continue;
        if(OnSeg(side.s, ray))
        {
            if(sgn(side.s.y - side.e.y) > 0)cnt++;
        }
        else if(OnSeg(side.e, ray))
        {
            if(sgn(side.e.y - side.s.y) > 0)cnt++;
        }
        else if(inter(ray, side))
            cnt++;
    }
    if(cnt % 2 == 1)return 1;
    else return -1;
}

//判断凸多边形
//允许共线边
//点可以是顺时针给出也可以是逆时针给出
//点的编号1~n-1
bool isconvex(Point poly[], int n)
{
    bool s[3];
    memset(s, false, sizeof(s));
    for(int i = 0; i < n; i++)
    {
        s[sgn((poly[(i + 1) % n] - poly[i]) ^ (poly[(i + 2) % n] - poly[i])) + 1] = true;
        if(s[0] && s[2])return false;
    }
    return true;
}
//多边形的面积: 分解为多个三角形的面积和
double CalArea(vector<Point> p)
{
    double res = 0;
    p.push_back(p[0]);
    for(int i = 1; i < (int)p.size(); i++)
        res += (p[i] ^ p[i - 1]);//计算由原点, p[i], p[i-1]构成的三角形的有向面积
    return fabs(res * 0.5);//三角面积需乘以0.5, 以及取正
}
//多边形的质心: 三角质心坐标的的面积加权和
Point Centroid(vector<Point> p)//按顺时针方向或逆时针方向排列
{
    Point c = Point(0.0, 0.0);
    double S = 0.0, s;
    for(int i = 2; i < (int)p.size(); i++)
    {
        s = ((p[i] - p[0]) ^ (p[i] - p[i - 1]));//求三角形面积(*0.5)
        S += s;
        c = c + (p[0] + p[i - 1] + p[i]) * s;//求三角形质心(/3.0)
    }
    c = c * (1.0 / (3.0 * S));
    return c;
}
