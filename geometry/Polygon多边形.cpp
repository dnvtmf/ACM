///三角形
/*
设三角形$\triangle ABC$的三个顶点A, B, C (对应内角角度为$A, B, C$); 对应的三条边为a, b, c (对应边长为a, b, c).
三点坐标对应为: $A(x_1, y_1)$, $B(x_2, y_2)$, $C(x_3, y_3)$
性质:
    三角形不等式: 三角形两边之和大于第三边, 两边之差的绝对值小于第三边.
        三角形任意一个外角大于不相邻的一个内角.
    勾股定理: 三角形是直角三角形($C=90^{\circ}$), 则$a^2 + b^2 = c^2$. 反之亦然.
    正弦定理: (R为三角形外接圆半径)@$$\frac{a}{\sin A } = \frac{b}{\sin B} = \frac{c}{\sin C} = 2R$$@
    余弦定理:
        $a^2 = b^2 + c^2 - 2bc \cdot \cos A$
        $b^2 = a^2 + c^2 - 2ac \cdot \cos B$
        $c^2 = a^2 + b^2 - 2ab \cdot \cos C$
角度:
	三角形两内角之和, 等于第三角的外角.
	三角形的内角和为$180^{\circ}$.
	三角形分类: 钝角三角形(其中一角是钝角($>90^{\circ}$)的三角形), 直角三角形(其中一角是直角($=90^{\circ}$)的三角形), 和锐角三角形(三个角都是锐角($<90^{\circ}$)的三角形.
	等边三角形的内角均为$60^{\circ}$.
	等腰三角形两底角相等.
面积:
	设a, b为已知的两边, C为其夹角, 三角形面积$\triangle =\displaystyle \frac{1}{2}ab \sin{C}$
	已知三角形的三边, 有:
		海伦公式: 令$\displaystyle p = \frac{a + b + c}{2}$, 则$\displaystyle \triangle = \sqrt{p(p-a)(p-b)(p-c)}$
		秦九韶的三斜求积法:$\displaystyle \triangle = \sqrt{\frac{1}{4} \big[c^2 a^2 - \big(\frac{c^2 + a^2 - b^2}{2}\big)^2\big]}$
		幂和: $\displaystyle \triangle = \frac{1}{4} \sqrt{(a^2 + b^2 + c^2)^2 - 2(a^4 + b^4 + c^4)}$
	已知一边a, 和该边上的高$h_a$, 则$\displaystyle \triangle = \frac{ah_a	}{2}$
	已知三点坐标, 面积为下列行列式的绝对值:@$$
	\frac{1}{2}\left| \begin{array}{c c c}
	x_1 & y_1 &1 \\
	x_2 & y_2 &1 \\
	x_3 & y_3 &1
	\end{array}\right|
	$$@
三角的五心:
	重心(形心 Centroid)
		定义: 三条中线的交点.
		坐标: 三点坐标的算术平均, 即$\displaystyle \left(\frac{x_1+x_2+x_3}{2}, \frac{y_1 + y_2 + y_3}{2} \right)$.
		三角形的重心与三顶点连线, 所形成的六个三角形面积相等.
		顶点到重心的距离是中线的$\frac{2}{3}$.
		重心到三角形3个顶点距离的平方和最小.
		以重心为起点, 以三角形三定点为终点的三条向量之和等于零向量.
*/
Point MassCenter(Point A, Point B, Point C)
{
    return (A + B + C) * (1.0 / 3.0);
}
/*
	内心I(Inner Center)
		定义: 三个内角的角平分线的交点.
		坐标: 三点坐标的面积加权平均, 即$\displaystyle \left( \frac{ax_1 + bx_2 + cx_3}{a + b + c}, \frac{ay_1 + by_2 + cy_3}{a + b + c} \right)$.
		内心到三角形三边的距离相等, 等于内切圆半径r.
		内心是三角形内切圆的圆心, 内切圆半径r, 有$\displaystyle \triangle = \frac{1}{2}(a + b + c)r$.
		直角三角形两股和等于斜边长加上该三角形内切圆直径, 即a + b = c + 2r,
		由此性质再加上勾股定理$ a^2 + b^2 = c^2$, 可推得: $\triangle = r(r+c)$
*/
Point InnerCenter(Point A, Point B, Point C)
{
    double a = dist(B, C), b = dist(A, C), c = dist(A, B);
    return (A * a + B * b + C * c) * (1.0 / (a + b + c));
}
/*
	外心(Circum Center)
		定义: 三条边垂直平分线的交点.
		坐标: @$$\left(  \frac{ \left| \begin{array}{c c c}
				x_1^2 + y_1^2	&1	&y_1 \\
				x_2^2 + y_2^2	&1	&y_2 \\
				x_3^2 + y_3^2	&1	&y_3
			\end{array} \right|}{2 \left| \begin{array}{c c c}
				x_1	&y_1 &1 \\
				x_2 &y_2 &1 \\
				x_3 &y_3 &1
			\end{array} \right|},\frac{ \left| \begin{array}{c c c}
				x_1^2 + y_1^2	&x_1	&1\\
				x_2^2 + y_2^2	&x_2	&1\\
				x_3^2 + y_3^2	&x_3	&1
			\end{array} \right|}{2 \left| \begin{array}{c c c}
				x_1	&y_1 &1 \\
				x_2 &y_2 &1 \\
				x_3 &y_3 &1
			\end{array} \right|}\right)$$@
		外心到三个顶点的距离都相等, 等于外接圆的半径R.
		直角三角形的外心是斜边的中点, 外接圆半径R为斜边的一半; 钝角三角形的外心在三角形外, 靠近最长边; 锐角三角形的外心在三角形内.
		外心是三角形外接圆的圆心, 外接圆半径R, 有$\displaystyle \triangle = \frac{abc}{4R}$
*/
//采用求垂直平分线相交的方法
Point CircumCenter(Point A, Point B, Point C)
{
    return	(Line((A + B) * 0.5, (A - B).rot(PI * 0.5) + ((A + B) * 0.5)) &
             Line((B + C) * 0.5, (B - C).rot(PI * 0.5) + ((B + C) * 0.5))).second;
}
//公式法
Poiny CircumCenter(Point A, Point B, Point C)
{
    Point t1 = B - A, t2 = C - A, t3((t1 * t1) * 0.5, (t2 * t2) * 0.5);
    swap(t1.y, t2.x);
    return A + Point(t3 ^ t2, t1 ^ t3) * (1.0 / (t1 ^ t2));
}
/*
	垂心H(Ortho Center)
		定义: 三条高的交点.
		坐标:@$$\left(  \frac{ \left| \begin{array}{c c c}
				x_2x_3 + y_2y_3	&1	&y_1 \\
				x_3x_1 + y_3y_1	&1	&y_2 \\
				x_1x_2 + y_1y_2	&1	&y_3
			\end{array} \right|}{\left| \begin{array}{c c c}
				x_1	&y_1 &1 \\
				x_2 &y_2 &1 \\
				x_3 &y_3 &1
			\end{array} \right|},\frac{ \left| \begin{array}{c c c}
				x_2x_3 + y_2y_3	&x_1	&1\\
				x_3x_1 + y_3y_1	&x_2	&1\\
				x_1x_2 + y_1y_2	&x_3	&1
			\end{array} \right|}{\left| \begin{array}{c c c}
				x_1	&y_1 &1 \\
				x_2 &y_2 &1 \\
				x_3 &y_3 &1
			\end{array} \right|}\right)$$@
		垂心分每条高线的两部分乘积相等, 即$AH \times HH_A = BH \times HH_B = CH \times HH_C$.
		直角三角形垂心为C($\angle C = 90^{\circ}$, 锐角三角形的垂心在三角形内部, 钝角三角形的垂心在三角形外部.
		垂心到三角形一顶点距离为此三角形外心到此顶点对边距离的2倍.
		一个三角形ABC的三个顶点A, B, C和它的垂心H构成一个垂心组: A, B, C, H. 也就是说, 这四点中任意的三点的垂心都是第四点.
		由海伦公式和三角形面积公式, 可以推出各边上的高的长度.
		反海伦公式
		如果设$\displaystyle h_s = \frac{h_a^{-1} + h_b^{-1} + h_c^{-1})}{2}($, 那么有以下类似于海伦公式的三角形面积公式@$$
			S^{-1} = 4 \sqrt{h_s (h_s-h_a^{-1}) (h_s-h_b^{-1}) (h_s-h_c^{-1})}$$@.
*/
Point OrthoCenter(Point A, Point B, Point C)
{
    return MassCenter(A, B, C) * 3.0 - CircumCenter(A, B, C) * 2.0;
}
/*
	旁心J
		定义: 三角形一内角平分线和另外两顶点处的外角平分线的点.
		旁心是三角形旁切圆(与三角形的一边和其他两边的延长线相切的圆)的圆心, 每个三角形有三个旁心, 而且一定在三角形外.
		旁心到三边的距离相等.
		旁切圆与三角形的边(或其延长线)相切的点称为旁切点.
		某顶点和其对面的旁切点将三角形的圆周等分为两半.
		三个旁心与内心组成一个垂心组, 也就是说内心是三个旁心所组成的三角形的垂心, 而相应的三个垂足则是旁心所对的顶点.
		旁心坐标和旁切圆半径:@$$
		J_A = \left( \frac{bx_2 + cx_3 - ax_1}{b + c - a}, \frac{by_2 + cy_3 - ay_1}{b + c - a} \right), r_A = \frac{2\triangle}{b + c - a}$$,$$
		J_B = \left( \frac{ax_1 + cx_3 - bx_2}{a + c - b}, \frac{ay_1 + cy_3 - by_2}{a + c - b} \right), r_B = \frac{2\triangle}{a + c - b}$$,$$
		J_C = \left( \frac{bx_2 + ax_1 - cx_3}{a + b - c}, \frac{by_2 + ay_1 - cy_3}{a + b - c} \right), r_C = \frac{2\triangle}{a + b - c}$$@
	关系:
		等边三角形四心(除旁心)重合.
		等腰三角形重心, 中心和垂心都位于顶点向底边的垂线.
		欧拉线: 三角形的垂心, 外心, 重心和九点圆圆心的一条直线. 欧拉线上的四点中九点圆圆心到垂心和外心的距离相等, 而且重心到外心的距离是重心到垂心距离的一半. 注意内心一般不在欧拉线上, 除了等腰三角形外.
		重心, 内心, 奈格尔点, 类似重心四点共线.
		三角形的外接圆半径R, 内切圆半径r 以及内外心间距OI 之间有如下关系: $R^2 - OI^2 = 2Rr$.
		内切圆在一边上的切点与旁切圆在该边的切点之间的距离恰好是另外两边的差(绝对值).
		对于一个顶点 (比如A) 所对的旁切圆, 三角形ABC的外接圆半径R, A所对旁切圆半径$r_A$以及内外心间距$OJ_A$之间关系: $OJ_A^2 - R^2 = 2Rr_A$
		内心I, B, C, $J_A$四点共圆, 其中$IJ_A$是这个圆的直径, 而圆心$P_A$在三角形ABC的外接圆上, 并且过BC的中垂线, 即等分劣弧BC. 对其它两边也有同样的结果.
		三角形内切圆的半径r与三个顶点上的高$h_a, h_b, h_c$有如下的关系:
			$\displaystyle \frac{1}{r}=\frac{1}{ h_a }+\frac{1}{ h_b }+\frac{1}{ h_c }$
		三个旁切圆的半径也和高有类关系:
			$\displaystyle \frac{1}{r_A} = -\frac{1}{ h_a } + \frac{1}{ h_b } + \frac{1}{ h_c }$.
			$\displaystyle \frac{1}{r_B} =  \frac{1}{ h_a } - \frac{1}{ h_b } + \frac{1}{ h_c }$.
			$\displaystyle \frac{1}{r_C} =  \frac{1}{ h_a } + \frac{1}{ h_b } - \frac{1}{ h_c }$.
	费马点:
		三角形内到三角形的三个顶点A, B, C的距离之和PA+PB+PC最小的点P.
		每个三角形只有一个费马点.
		费马点求法:
			当有一个内角不小于$120^{\circ}$时, 费马点为此角对应顶点.
			当三角形的内角都小于$120^{\circ}$时, 以三角形的每一边为底边, 向外做三个正三角形$\triangle ABC'$, $\triangle BCA'$, $\triangle CAB'$, 连接CC', BB', AA', 则三条线段的交点就费马点. (此时$\angle{APB} = \angle{APC} = \angle{BPC} = 120^{\circ}$)
	九点圆(又称欧拉圆, 费尔巴哈圆), 在平面几何中, 对任何三角形, 九点圆通过三角形三边的中点, 三高的垂足, 和顶点到垂心的三条线段的中点.
		九点圆定理指出对任何三角形, 这九点必定共圆;
		九点圆的半径是外接圆的一半. 且九点圆平分垂心与外接圆上的任一点的连线;
		圆心在欧拉线上. 且在垂心到外心的线段的中点;
		九点圆和三角形的内切圆和旁切圆相切(费尔巴哈定理), 切点称为费尔巴哈点;
		圆周上四点任取三点做三角形, 四个三角形的九点圆圆心共圆(库利奇－大上定理).
	奈格尔点:
		旁切点$J_A, J_B, J_C$分别是三旁切圆和三条边的切点, 直线$AJ_A, BJ_B, CJ_C$共点交于三角形ABC的奈格尔点N.
		另一种方法构造$J_A$, 从点A出发沿着三角形ABC的边走到半周长位置, 类似的得到$J_B$和$J_C$. 因为这个构造, 奈格尔点有时也被称为平分周长点(或译界心).

半角定理: 三角形的三个角的半角的的正切和三边有如下关系:
	$\displaystyle \tan \frac{A}{2} = \frac{p}{b + c - a}$, $\displaystyle \tan \frac{B}{2} = \frac{p}{a + c - b}$, $\displaystyle \tan \frac{C}{2} = \frac{p}{a + b - c}$
	其中, $\displaystyle p = \sqrt{\frac{(b + c - a)(a + c - b)(a + b - c)}{a + b + c}}$.
角平分线长度
	设在三角形ABC中, 已知三边a, b, c, 若三个角A, B, C的角平分线分别为$t_a, t_b, t_c$ 则用三边表示三条内角平分线长度公式为@$$
	t_a = \frac{1}{b+c} \sqrt{(b + c + a)(b + c - a)bc}$$$$
	t_b = \frac{1}{a+c} \sqrt{(a + c + b)(a + c - b)ac}$$$$
	t_c = \frac{1}{a+b} \sqrt{(a + b + c)(a + b - c)ab}$$@
等角共轭
	几何学中, 设点 P 是三角形 ABC 平面上一点, 作直线 PA, PB 和 PC 分别关于角 A, B 和 C 的平分线的反射, 这三条反射线必然交于一点, 称此点为 P 关于三角形 ABC 的等角共轭. (这个定义只对点, 不是对三角形 ABC 的边.)
	内心I的等角共轭点是自身. 垂心H的等角共轭点是外心O. 重心的等角共轭点是类似重心K.
*/

//2. 多边形
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
/*4. 圆
圆心(x, y), 半径r
面积: $\pi r^2$, 周长: $2\pi r$
弧长: $\theta r$
三点圆方程:@$$\left| \begin{array}{c c c c }
	x^2 + y^2		&x		&y		&1 \\
	x_1^2 + y_1^2	&x_1	&y_1	&1	\\
	x_2^2 + y_2^2	&x_2	&y_2	&1	\\
	x_3^2 + y_3^2	&x_3	&y_3	&1	\\
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
\rho_n 	= \frac{S_n}{A_n}
		= \frac{ \frac{n a^2}{4}\cot \left(\frac{\pi}{n} \right) } { \frac{\pi a^2}{4}\csc^2 \left(\frac{\pi}{n} \right) }
		= \frac{n}{\pi} \cos \left(\frac{\pi}{n} \right) \sin \left(\frac{\pi}{n} \right)
		= \frac{ n }{ 2\pi}\sin \left( \frac{ 2 \pi}{ n } \right)$$@
故此, 当n趋向无穷时, @$$
\lim_{n\to\infty} \rho_n = \lim_{n\to \infty} \frac{n}{2\pi}\sin\left( \frac{2 \pi}{n} \right) = 1$$@
另外, 其内切圆的面积$S_n$与其外接圆的面积$A_n$之比为: @$$
\tau_n	= \frac{s_n}{A_n}
		= \frac{s_n}{S_n} \cdot \frac{S_n}{A_n}
		= \varphi_n \rho_n
		= \left[ \frac{ \pi }{ n} \cot\left( \frac{ \pi}{ n} \right) \right]\left[ \frac{n}{\pi} \cos\left(\frac{\pi}{n} \right) \sin\left(\frac{\pi}{n} \right) \right]
		= \cos^2 \left( \frac{ \pi } { n } \right) $$@
*/
