//自适应辛普森积分法
//令[a, b]为所需积分区间, F(x)为被积式
const double eps = 1e-6;//整体所需精度
//三点Simposn, w = b - a, c = a + w / 2, fa = F(a), fb = F(b), fc = F(c)
inline double simpson(double w, double fa, double fb, double fc)
{
	return (fa + 4.0 * fc + fb) * w / 6.0;
}
//自适应Simpson公式(递归过程), 已知整个区间[a,b]上的三点simpson值A
double asr(double F(double x), double a, double b, double eps, double A)
{
	double c = a + (b - a) / 2;
	double fa = F(a), fb = F(b), fc = F(c);
	double L = simpson(c - a, fa, fc, F((a + c) / 2));
	double R = simpson(b - c, fc, fb, F((c + b) / 2));
	if(fabs(L + R - A) <= 15.0 * eps)
		return L + R + (L + R - A) / 15.0;
	return asr(F, a, c, eps / 2, L) + asr(F, c, b, eps / 2, R);
}
// 自适应Simpson公式(主过程)
double asr(double F(double x), double a, double b, double eps)
{
	return asr(F, a, b, eps, simpson(b - a, F(a), F(b), F((a + b) / 2)));
}
