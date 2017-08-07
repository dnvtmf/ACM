/// 圆
/*
圆心(x, y), 半径r
面积: $\pi r^2$, 周长: $2\pi r$
弧长: $\theta r$
三点圆方程: @$$\left| \begin{array}{c c c c }
    x^2 + y^2       &x      &y      &1 \\
    x_1^2 + y_1^2   &x_1    &y_1    &1  \\
    x_2^2 + y_2^2   &x_2    &y_2    &1  \\
    x_3^2 + y_3^2   &x_3    &y_3    &1  \\
    \end{array}\right| = 0$$@
四边形的内切圆和外切圆:
    不是所有的四边形都有内切圆, 拥有内切圆的四边形称为圆外切四边形. 凸四边形ABCD有内切圆当且仅当两对对边之和相等: AB + CD = AD + BC. 圆外切四边形的面积和内切圆半径的关系为: $S_{ABCD} = rs$, 其中s 为半周长.
    同时拥有内切圆和外接圆的四边形称为双心四边形. 这样的四边形有无限多个. 若一个四边形为双心四边形, 那么其内切圆在两对对边的切点的连线相互垂直. 而只要在一个圆上选取两条相互垂直的弦, 并过相应的顶点做切线, 就能得到一个双心四边形.
    正多边形必然有内切圆, 而且其内切圆的圆心和外接圆的圆心重合, 都在正多边形的中心. 边长为a 的正多边形的内切圆半径为:
    $r_n = \frac{a}{2} \cot \left(\frac{\pi}{n} \right)$
其内切圆的面积为:
$s_n =\pi r_n^2 = \frac{ \pi a^2}{4} \cot^2 \left(\frac{\pi}{n} \right)$
内切圆面积$s_n$与正多边形的面积$S_n$之比为:
$\varphi_n = \frac{s_n } { S_n } =  \frac{ \frac{ \pi a^2}{4} \cot^2 \left(\frac{\pi}{n} \right) } { \frac{ n a }{2} \left[ \frac{a}{2} \cot\left( \frac{\pi}{n} \right)\right] } = \frac{\pi}{n} \cot \left(\frac{\pi}{n} \right)$
故此, 当正多边形的边数n趋向无穷时, @$$
    \lim_{n \to \infty} \varphi_n = \lim_{n\to \infty} \frac{ \pi} {n} \cot \left( \frac{ \pi} { n } \right) = \lim_{n \to \infty} \cos^2 \left( \frac{ \pi } { n } \right) = 1$$@
(婆罗摩笈多公式)若圆内接四边形的四边边长分别是a, b, c, d, 则其面积为$\displaystyle S =\sqrt{(p-a)(p-b)(p-c)(p-d)}$, 其中p为半周长:$\displaystyle p = \frac{a + b + c + d}{2}$. 在所有周长为定值2p的圆内接四边形中, 面积最大的是正方形.
四边形外接圆的半径为, $\displaystyle R = \frac{\sqrt{(ac + bd) (ad + bc) (ab + cd)}}{4S}$
(泰勒斯定理)若A, B, C是圆周上的三点, 且AC是该圆的直径, 那么∠ABC必然为直角. 或者说, 直径所对的圆周角是直角.
泰勒斯定理的逆定理同样成立, 即: 直角三角形中, 直角的顶点在以斜边为直径的圆上.

所有的正多边形都有外接圆, 外接圆的圆心和正多边形的中心重合. 边长为a 的n 边正多边形外接圆的半径为: @$$
    R_n = \frac{a}{2 \sin \left(\frac{\pi}{n} \right)} = \frac{a}{2} \csc \left(\frac{\pi}{n} \right)$$@
面积为: @$$
    A_n = \pi R_n^2 = \frac{\pi a^2}{4 \sin^2 (\frac{\pi}{n})} = \frac{\pi a^2}{4}\csc^2 (\frac{\pi}{n} )$$@
正n 边形的面积$s_n$与其外接圆的面积$A_n$之比为@$$
\rho_n  = \frac{S_n}{A_n}
        = \frac{ \frac{n a^2}{4}\cot \left(\frac{\pi}{n} \right) } { \frac{\pi a^2}{4}\csc^2 \left(\frac{\pi}{n} \right) }
        = \frac{n}{\pi} \cos \left(\frac{\pi}{n} \right) \sin \left(\frac{\pi}{n} \right)
        = \frac{ n }{ 2\pi}\sin \left( \frac{ 2 \pi}{ n } \right)$$@
故此, 当n趋向无穷时, @$$
\lim_{n\to\infty} \rho_n = \lim_{n\to \infty} \frac{n}{2\pi}\sin\left( \frac{2 \pi}{n} \right) = 1$$@
另外, 其内切圆的面积$S_n$与其外接圆的面积$A_n$之比为: @$$
\tau_n  = \frac{s_n}{A_n}
        = \frac{s_n}{S_n} \cdot \frac{S_n}{A_n}
        = \varphi_n \rho_n
        = \left[ \frac{ \pi }{ n} \cot\left( \frac{ \pi}{ n} \right) \right]\left[ \frac{n}{\pi} \cos\left(\frac{\pi}{n} \right) \sin\left(\frac{\pi}{n} \right) \right]
        = \cos^2 \left( \frac{ \pi } { n } \right) $$@
*/
//圆与(直线)线段的相交
//num表示圆O(o, r)与线段(s, e)的交点数, res里存储的是交点
void Circle_cross_Segment(Point s, Point e, Point o, double r, Point res[], int &num) {
  double dx = e.x - s.x, dy = e.y - s.y;
  double A = dx * dx + dy * dy;
  double B = 2.0 * dx * (s.x - o.x) + 2.0 * dy * (s.y - o.y);
  double C = sqr(s.x - o.x) + sqr(s.y - o.y) - r * r;
  double delta = B * B - 4.0 * A * C;
  num = 0;
  if (sgn(delta) < 0) return ;
  delta = sqrt(max(0.0, delta));
  double k1 = (-B - delta) / (2.0 * A);
  double k2 = (-B + delta) / (2.0 * A);
  //if(sgn(k1 - 1.0) <= 0 && sgn(k1) >= 0) //圆与线段相交条件判断
  res[num++] = Point(s.x + k1 * dx, s.y + k1 * dy);
  //if(sgn(k2 - 1.0) <= 0 && sgn(k2) >= 0)
  res[num++] = Point(s.x + k2 * dx, s.y + k2 * dy);
}

//三角形ABO与圆(O, r)的面积交
double Triangel_cross_Circle(Point a, Point b, Point o, double r) {
  double r2 = r * r;
  a = a - o;
  b = b - o;
  o = Point(0.0, 0.0);
  bool bAInC = sgn((a * a) - r2) < 0;
  bool bBInC = sgn((b * b) - r2) < 0;
  double sg = 0.5 * sgn(a ^ b), res = 0.0;
  Point tmp[2];
  int num;
  if (bAInC && bBInC) res = abs(a ^ b);
  else if (bAInC || bBInC) {
    if (bBInC) swap(a, b);
    Circle_cross_Segment(a, b, 0, r, tmp, num);
    res = fabs(a ^ tmp[0]) + r2 * angle(tmp[0], b);
  }
  else {
    Circle_cross_Segment(a, b, o, r, tmp, num);
    res = r2 * angle(a, b);
    if (num == 2) {
      res -= r2 * angle(tmp[0], tmp[1]);
      res += fabs(tmp[0] ^ tmp[1]);
    }
  }
  return sg * res;
}

//多边形与圆的面积交
double Polygon_intersect_Circle(Point ploy[], int n, Point O, double r) {
  ploy[n] = ploy[0];
  double res = 0.0;
  for (int i = 0; i < n; ++i)
    res += Triangel_cross_Circle(ploy[i], ploy[i + 1], O, r);
  return fabs(res);
}
