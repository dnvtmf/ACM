//半平面交
inline int sgn(double x)
{
    if(x < -EPS) return -1;
    return x > EPS ? 1 : 0;
}
struct Point
{
    double x, y;
    Point(double xx = 0.0, double yy = 0.0): x(xx), y(yy) {}
    void in()
    {
        scanf("%lf%lf", &x, &y);
    }
    Point operator + (Point b)
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (Point b)
    {
        return Point(x - b.x, y - b.y);
    }
    Point operator *(double b)
    {
        return Point(x * b, y * b);
    }
    double operator *(Point b)
    {
        return x * b.x + y * b.y;
    }
    double operator ^(Point b)
    {
        return x * b.y - y * b.x;
    }
} p[NUM], ans[NUM];
struct Line
{
    Point s, e;
    double k;
    Line() {}
    Line(Point _s, Point _e): s(_s), e(_e) {k = atan2(e.y - s.y, e.x - s.x);}
    void K()
    {
        k = atan2(e.y - s.y, e.x - s.x);
    }
    Point operator &(Line &b)
    {
        return s + (e - s) * (((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e)));
    }
} L[NUM], que[NUM];
int ln;

inline bool HPIcmp(Line a, Line b)
{
    if(sgn(a.k - b.k) != 0)return sgn(a.k - b.k) < 0;
    return ((a.s - b.s) ^ (b.e - b.s)) < 0;
}
void HPI(Line line[], int n, Point res[], int &resn)
{
    int tot = n;
    sort(line, line + n, HPIcmp);
    tot = 1;
    for(int i = 1; i < n; i++)
    {
        if(sgn(abs(line[i].k - line[i - 1].k)) != 0)
            line[tot++] = line[i];
    }
    int head = 0, tail = 1;
    que[0] = line[0];
    que[1] = line[1];
    resn = 0;
    for(int i = 2; i < tot; i++)
    {
        if(sgn((que[tail].e - que[tail].s) ^ (que[tail - 1].e - que[tail - 1].s)) == 0 ||
                sgn((que[head].e - que[head].s) ^ (que[head + 1].e - que[head + 1].s)) == 0)
            return ;
        while(head < tail && sgn(((que[tail]&que[tail - 1]) - line[i].s) ^ (line[i].e - line[i].s)) > 0)
            tail--;
        while(head < tail && sgn(((que[head]&que[head + 1]) - line[i].s) ^ (line[i].e - line[i].s)) > 0)
            head++;
        que[++tail] = line[i];
    }
    while(head < tail && sgn(((que[tail]&que[tail - 1]) - que[head].s) ^ (que[head].e - que[head].s)) > 0)
        tail--;
    while(head < tail && sgn(((que[head]&que[head + 1]) - que[tail].s) ^ (que[tail].e - que[tail].s)) > 0)
        head++;
    if(tail <= head + 1) return ;
    for(int i = head; i < tail; i++)
        res[resn++] = que[i] & que[i + 1];
    if(head < tail - 1)
        res[resn++] = que[head] & que[tail];
}
