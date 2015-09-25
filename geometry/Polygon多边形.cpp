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
/*
Description: 判断点在任意多边形内
Algorithm: 射线法, poly[]的顶点数要大于等于3,点的编号0~n-1
Return:  -1, 点在凸多边形外; 0, 点在凸多边形边界上; 1, 点在凸多边形内
Notice: ray.e.x的取值要注意, 要小于最小的x坐标, 如果是整数, 防止爆int或LL;
*/
int isPointInPolygon(Point p, Point poly[], int n)
{
    int cnt = 0;
    Line ray, side;
    ray.s = p;
    ray.e.y = p.y;
    ray.e.x = -100000000000.0;//-INF, 注意取值防止越界
    for(int i = 0; i < n; ++i)
    {
        side.s = poly[i];
        side.e = poly[(i + 1) % n]; //判断点在任意多边形内
        if(isPointOnSegment(p, side)) return -1;
        if(sgn(side.s.y - side.e.y) == 0) continue;//如果平行轴则不考虑
        if(isPointOnSegment(side.s, ray))
        {
            if(sgn(side.s.y - side.e.y) > 0) cnt = !cnt;
        }
        else if(isPointOnSegment(side.e, ray))
        {
            if(sgn(side.e.y - side.s.y) > 0) cnt = !cnt;
        }
        else if(seg_seg_inter(ray, side)) cnt = !cnt;
    }
    return cnt;
}
/*
Description: 判断点是否在多边形内
Algorithm: 射线法, $O(n)$
Param[in]: p, 要判断的点; poly, 多边形(边不自交); n, 多边形顶点数
Return: -1, 点在多边形上; 0, 点在多边形外; 1, 点在多边形内
Notice: 复制p[0]到p[n]
*/
int isPointInPolygon(Point p, Point poly[], int n)
{
    int wn = 0;
    for(int i = 0; i < n; ++i)
    {
        if(isPointOnSegmet(p, poly[i], poly[i + 1])) return -1;
        int k = sgn((poly[i + 1] - poly[i]) ^ (p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[i + 1].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if(k < 0 && d1 > 0 && d2 <= 0) --wn;
    }
    return wn != 0;
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
