//精度设置
const double EPS = 1e-6;
//点(向量)的定义和基本运算
/*
向量点积$a\cdot b = |a||b|\cos{\theta}$
点积>0, 表示两向量夹角为锐角
点积=0, 表示两向量垂直
点积<0, 表示两向量夹角为钝角
*/
/*
向量叉积 @$a\times b = |a||b|\sin{\theta} $@
叉积>0, 表示向量b在当前向量逆时针方向
叉积=0, 表示两向量平行
叉积<0, 表示向量b在当前向量顺时针方向
*/
inline int sgn(double x) {if(x < -EPS)return -1; return x > EPS ? 1 : 0;}
struct Point
{
    double x, y;
    Point(double _x = 0.0, double _y = 0.0): x(_x), y(_y) {}
    Point operator + (const Point &b)const {return Point(x + b.x, y + b.y);}//向量加法
    Point operator - (const Point &b)const {return Point(x - b.x, y - b.y);}//向量减法
    double operator * (const Point &b)const {return x * b.x + y * b.y;}//向量点积
    double operator ^ (const Point &b)const {return x * b.y - y * b.x;} //向量叉积
    Point operator * (double b) {return Point(x * b, y * b);}//标量乘法
    Point rot(double ang) {return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));}//旋转
    double norm() {return sqrt(x * x + y * y);}//向量的模
};
//直线 线段定义
//直线方程：两点式：@$(x_2 - x_1)(y - y_1) = (y_2 - y_1)(x - x_1)$@
struct Line
{
    Point s, e;
    //double k;
    Line() {}
    Line(Point _s, Point _e)
    {
        s = _s, e = _e;
        //k = atan2(e.y - s.y, e.x - s.x);
    }
    //求两直线交点
    //返回-1两直线重合, 0 相交, 1 平行
    pair<int, Point> operator &(Line b)
    {
        if(sgn((s - e) ^ (b.s - b.e)) == 0)
        {
            if(sgn((s - b.e) ^ (b.s - b.e)) == 0) return make_pair(-1, s);//重合
            else return make_pair(1, s);//平行
        }
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e));
        return make_pair(0, Point(s.x + (e.x - s.x) * t, s.y + (e.y - s.y) * t));
    }
};

//两点间距离
double dist(Point &a, Point &b) {return (a - b).norm();}

/*判断点p在线段l上
 * (p - l.s) ^ (l.s - l.e) = 0; 保证点p在直线L上
 * p在线段l的两个端点l.s,l.e为对角定点的矩形内
 */
bool isPointOnSegment(const Point &p,const Line &l)
{
    return sgn((p - l.s) ^ (l.s - l.e)) == 0 &&
           sgn((p.x - l.s.x) * (p.x - l.e.x)) <= 0 &&
           sgn((p.y - l.s.y) * (p.y - l.e.y)) <= 0;
}
//判断点p在直线l上
bool isPointOnLine(Point &p, Line &l)
{
    return sgn((p - l.s) ^ (l.s - l.e)) == 0;
}

/*判断两线段l1, l2相交
 * 1. 快速排斥实验：判断以l1为对角线的矩形是否与以l2为对角线的矩形是否相交
 * 2. 跨立实验：l2的两个端点是否在线段l1的两端
 */
bool seg_seg_inter(Line seg1, Line seg2)
{
    return
        sgn(max(seg1.s.x, seg1.e.x) - min(seg2.s.x, seg2.e.x)) >= 0 &&
        sgn(max(seg2.s.x, seg2.e.x) - min(seg1.s.x, seg1.e.x)) >= 0 &&
        sgn(max(seg1.s.y, seg1.e.y) - min(seg2.s.y, seg2.e.y)) >= 0 &&
        sgn(max(seg2.s.y, seg2.e.y) - min(seg1.s.y, seg1.e.y)) >= 0 &&
        sgn((seg2.s - seg1.e) ^ (seg1.s - seg1.e)) * sgn((seg2.e - seg1.e) ^ (seg1.s - seg1.e)) <= 0 &&
        sgn((seg1.s - seg2.e) ^ (seg2.s - seg2.e)) * sgn((seg1.e - seg2.e) ^ (seg2.s - seg2.e)) <= 0;
}

//判断直线与线段相交
bool seg_line_inter(Line &line, Line &seg)
{
    return sgn((seg.s - line.e) ^ (line.s - line.e)) * sgn((seg.e - line.e) ^ (line.s - line.e)) <= 0;
}

//点到直线的距离, 返回垂足
Point Point_to_Line(Point p, Point l)
{
    double t = ((p - l.s) * (l.e - l.s)) / ((l.e - l.s) * (l.e - l.s));
    return Point(l.s.x + (l.e.x - l.s.x) * t, l.s.y + (l.e.y - l.s.y) * t);
}
//点到线段的距离
//返回点到线段最近的点
Point Point_to_Segment(Point p, Line seg)
{
    double t = ((p - seg.s) * (seg.e - seg.s)) / ((seg.e - seg.s) * (seg.e - seg.s));
    if(t >= 0 && t <= 1)
        return Point(seg.s.x + (seg.e.x - seg.s.x) * t, seg.s.y + (seg.e.y - seg.s.y) * t);
    else if(sgn(dist(p, seg.s) - dist(p, seg.e) <= 0))
        return seg.s;
    else
        return seg.e;
}

//求向量vA与vB的夹角(<= PI)
double angle(Point vA, Point vB)
{
    double tmp = vA.norm() * vB.norm();
    if(sgn(tmp) != 0) return acos((vA * vB) / tmp);
    else return 0.0;
}
