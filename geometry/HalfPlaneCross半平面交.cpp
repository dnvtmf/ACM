///半平面交 Half Plane Cross
/*
半平面: 一条直线$ax + by + c = 0$将一个平面分为两个部分, 这两个部分称为半平面, 表示为$ax + by + c \leq 0$和$ax + by + c > 0$. 默认向量的左侧是所需的半平面.
定理: n个半平面的交或者是一个开放的无穷平面, 或者是一个封闭的凸多边形.
求半平面交:
方法一: 增量法 $O(n^2)$
    假设已经求得前面n - 1个半平面的交, 对于第n个半平面, 用它来切割前n-1个半平面交出来的多边形.
方法二: 分治法 $O(n\log{n})$
    将n个半平面分为两个部分, 分别求完交后再将两部分的交合并求交集. 而两个凸多边形可以在$O(n)$时间内求交.
方法三: 排序增量法 $O(n\log{n})$
    算法类似于求取凸包的Graham-Scan算法. 先求所有半平面交, 按照半平面边界直线与x轴正半轴的夹角排序 $O(n\log{n})$, 然后扫描所有半平面 $O(n)$.
*/
/*半平面$ax + by + c \leq 0$转向量法(两点式)表示
*/
Line ToLine(double a, double b, double c)
{
    if(sgn(b))
    {
        if(sgn(b) < 0) return Line(Point(0.0, c / b), Point(1.0, (c - a) / b));
        else return Line(Point(1.0, (c - a) / b), Point(.0, c / b));
    }
    else
    {
        if(sgn(a) > 0) return  Line(Point(c / a, 0.0), Point(c / a, 1.0));
        else return Line(Point(c / a, 1.0), Point(c / a, 0.0));
    }
}

/*排序增量法求半平面交
    1. 将所有的半平面按照极角排序, (排序过程中还要将平行的半平面去重)
    2. 使用一个双端队列deque, 加入极角最小的两个半平面
    3. 扫描过程每次考虑一个新的半平面
        while deque顶端的两个半平面的交点在当前半平面外: 删除deque顶端的半平面
        while deque底部的两个半平面的交点在当前半平面外: 删除deque底部的半平面
        将当前半平面加入deque顶端
    4. 删除deque两端延伸出来的多余的半平面
        while deque顶端的两个半平面的交点在当前半平面外: 删除deque顶端的半平面
        while deque底部的两个半平面的交点在当前半平面外: 删除deque底部的半平面
    5. 按照顺序求取deque中两个相邻半平面的交点, 得到n个半平面交出的凸多边形.
*/
inline int sgn(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
struct Point
{
    double x, y;
    Point(double xx = 0.0, double yy = 0.0): x(xx), y(yy) {}
    void in() {scanf("%lf%lf", &x, &y);}
    Point operator + (const Point &b) const {return Point(x + b.x, y + b.y);}
    Point operator - (const Point &b) const {return Point(x - b.x, y - b.y);}
    Point operator * (double b) {return Point(x * b, y * b);}
    double operator * (const Point &b) const {return x * b.x + y * b.y;}
    double operator ^ (const Point &b) const {return x * b.y - y * b.x;}
} ans[NUM];
struct Line
{
    Point s, e;
    double k;
    Line() {}
    Line(Point _s, Point _e): s(_s), e(_e) {k = atan2(e.y - s.y, e.x - s.x);}
    void K() { k = atan2(e.y - s.y, e.x - s.x);}
    Point operator & (const Line &b) const {return s + (e - s) * (((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e)));}
} L[NUM], que[NUM];
int ln;
inline bool HPIcmp(Line a, Line b)
{
    if(sgn(a.k - b.k) != 0)return sgn(a.k - b.k) < 0;
    return ((a.s - b.s) ^ (b.e - b.s)) < 0;
}
void HPI(Line line[], int n, Point res[], int &resn)
{
    sort(line, line + n, HPIcmp);
    int tot = 1;
    for(int i = 1; i < n; ++i)
    {
        if(sgn(abs(line[i].k - line[i - 1].k)) != 0)
            line[tot++] = line[i];
    }
    int head = 0, tail = 1;
    que[0] = line[0];
    que[1] = line[1];
    resn = 0;
    for(int i = 2; i < tot; ++i)
    {
        if(sgn((que[tail].e - que[tail].s) ^ (que[tail - 1].e - que[tail - 1].s)) == 0 ||
                sgn((que[head].e - que[head].s) ^ (que[head + 1].e - que[head + 1].s)) == 0)
            return ;
        while(head < tail && sgn(((que[tail]&que[tail - 1]) - line[i].s) ^ (line[i].e - line[i].s)) > 0)
            --tail;
        while(head < tail && sgn(((que[head]&que[head + 1]) - line[i].s) ^ (line[i].e - line[i].s)) > 0)
            ++head;
        que[++tail] = line[i];
    }
    while(head < tail && sgn(((que[tail]&que[tail - 1]) - que[head].s) ^ (que[head].e - que[head].s)) > 0)
        --tail;
    while(head < tail && sgn(((que[head]&que[head + 1]) - que[tail].s) ^ (que[tail].e - que[tail].s)) > 0)
        ++head;
    if(tail <= head + 1) return ;
    for(int i = head; i < tail; ++i)
        res[resn++] = que[i] & que[i + 1];
    if(head < tail - 1)
        res[resn++] = que[head] & que[tail];
}
