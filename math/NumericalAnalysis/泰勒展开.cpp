///泰勒展开 Taylor's formula
/*
泰勒公式是将一个在 $x = x_0$ 处具有 $n$ 阶导数的函数 $f(x)$ 利用关于 $(x-x_0)$ 的 $n$ 次多项式来逼近函数的方法.
若函数 $f(x)$ 在包含 $x_0$ 的某个闭区间 $[a, b]$ 上具有 $n$ 阶导数, 且在开区间 $(a, b)$ 上具有 $(n+1)$ 阶导数, 则对闭区间 $[a, b]$ 上任意一点 $x$, 下式成立: @$$
f(x) = \frac{f(x_0)}{0!} + \frac{f'(x_0)}{1!}(x - x_0) + \frac{f''(x_0)}{2!}(x-x_0)^2 + \cdots + \frac{f^{(n)}(x_0)}{n!}(x-x_0)^n + R_n(x)
$$@
其中, $f^{(n)}(x)$ 表示 $f(x)$ 的 $n$ 阶导数, 等号后的多项式称为函数$f(x)$ 在$x_0$ 处的泰勒展开式, 剩余的 $R_n(x)$ 是泰勒公式的余项, 是 $(x-x_0)^n$ 的高阶无穷小.
*/
/*麦克劳林展开
函数的麦克劳林展开是指上面泰勒公式中 $x_0$ 取 0 的情况, 即使泰勒公式的特殊形式, 若 $f(x)$ 在 $x = 0$处 $n$ 阶连续可导, 则下式成立: @$$
f(x) = f(0) + \frac{f'(0)}{1!} + \frac{f''(0)}{2!}x^2 + \frac{f'''(0)}{3!}x^3 + \cdots + \frac{f^{(n)}(0)}{n!}x^n + R_n(x)
$$@
其中, $f^{(n)}(x)$ 表示 $f(x)$ 的 $n$ 阶导数.
*/
/**常用函数的泰勒公式(麦克劳林展开)
1. $\disp \frac {1}{1-x} = 1 + x + x^2 + \cdots + x^n + \cdots = \sum_{n=0}^{\infty}{x^n},\, (|x| < 1)$
2. $\disp \frac {1}{1+x} = 1 - x + x^2 - \cdots + (-1)^n x^n + \cdots = \sum_{n=0}^{\infty}{(-1)^n x^n},\, (|x| < 1)$
3. $\disp e^x = 1 + x + \frac {1}{2!} x^2 + \cdots + \frac {1}{n!}x^n + \cdots = \sum_{n=0}^{\infty}{\frac{z^n}{n!}},\,(|x| < \infty)$
4. $\disp \sin{x} = x - \frac {1}{3!}x^3 + \frac {1}{5!} x^5 + \cdots + (-1)^n \frac {1}{(2n + 1)!} x^{2n + 1} + \cdots ,\, (|x| < \infty)$
5. $\disp \cos{x} = 1 - \frac {1}{2!} x^2 + \frac {1}{4!} x^4 + \cdots + (-1)^n \frac {1}{(2n)!} x^{2n} + \cdots ,\, (|x| < \infty)$
6. $\disp \ln {(1+x)} = x - \frac {1}{2} x^2 + \frac {1}{3} x^3 + \cdots + (-1)^{n - 1} \frac {1}{n} x^n + \cdots = \sum_{n=0}^{\infty}{(-1)^n \frac {x^{n+1}}{n + 1}},\, (|x| < 1)$
7. $\disp (1 + x)^ {\alpha} = 1 + \alpha x + \frac {\alpha (\alpha - 1)}{2!} x^2 + \cdots + \frac {\alpha (\alpha - 1) \cdots (\alpha - n + 1)}{n!} x^n + \cdots,\, (|x| < 1)$
*/
