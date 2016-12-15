///拉格朗日插值法 Lagrange polynomial
/**拉格朗日插值法
对某个多项式函数, 已知有给定的k + 1个取值点: @$${\displaystyle (x_{0},y_{0}),\ldots ,(x_{k},y_{k})}$$@
其中 $x_j$ 对应着自变量的位置, 而 $y_j$ 对应着函数在这个位置的取值.
假设任意两个不同的 $x_j$ 都互不相同, 那么应用拉格朗日插值公式所得到的拉格朗日插值多项式为:
@$${\displaystyle L(x):=\sum _{j=0}^{k}y_{j}\ell _{j}(x)}$$@
其中每个 ${\displaystyle \ell _{j}(x)}$ 为拉格朗日基本多项式(或称插值基函数), 其表达式为:
@$${\displaystyle \ell _{j}(x):=\prod _{i=0,\,i\neq j}^{k}{\frac {x-x_{i}}{x_{j}-x_{i}}}={\frac {(x-x_{0})}{(x_{j}-x_{0})}}\cdots {\frac {(x-x_{j-1})}{(x_{j}-x_{j-1})}}{\frac {(x-x_{j+1})}{(x_{j}-x_{j+1})}}\cdots {\frac {(x-x_{k})}{(x_{j}-x_{k})}}.} $$@
拉格朗日基本多项式 ${\displaystyle \ell _{j}(x)}$ 的特点是在 ${\displaystyle x_{j}}$ 上取值为1, 在其它的点 ${\displaystyle x_{i},\,i\neq j}$ 上取值为0.
*/
/**重心拉格朗日插值法
重心拉格朗日插值法是拉格朗日插值法的一种改进. 在拉格朗日插值法中, 运用多项式 @$${\displaystyle \ell (x)=(x-x_{0})(x-x_{1}) \cdots (x-x_{k})}$$@
可以将拉格朗日基本多项式重新写为: @$${\displaystyle \ell _{j}(x)={\frac {\ell (x)}{x-x_{j}}}{\frac {1}{\prod _{i=0,i\neq j}^{k}(x_{j}-x_{i})}}}$$@
定义重心权 @$${\displaystyle w_{j}={\frac {1}{\prod _{i=0,i\neq j}^{k}(x_{j}-x_{i})}}}$$@
上面的表达式可以简化为: @$${\displaystyle \ell _{j}(x)=\ell (x){\frac {w_{j}}{x-x_{j}}}}$$@
于是拉格朗日插值多项式变为: @$${\displaystyle L(x)=\ell (x)\sum _{j=0}^{k}{\frac {w_{j}}{x-x_{j}}}y_{j}}$$@
即所谓的重心拉格朗日插值公式(第一型)或改进拉格朗日插值公式. 它的优点是当插值点的个数增加一个时, 将每个 $w_j$ 都除以 ${\displaystyle (x_{j}-x_{k+1})}$, 就可以得到新的重心权 $w_{k+1}$ , 计算复杂度为 ${\mathcal {O}}(n)$, 比重新计算每个基本多项式所需要的复杂度 ${\mathcal {O}}(n^{2})$ 降了一个量级.
将以上的拉格朗日插值多项式用来对函数 $g(x) \equiv 1$ 插值, 可以得到: @$$ \forall x,\,g(x)= \ell (x) \sum _{j=0}^{k}{ \frac {w_{j}}{x-x_{j}}}$$@
因为 $g(x) \equiv 1$ 是一个多项式.
因此, 将 $L(x)$ 除以 $g(x)$ 后可得到: @$$L(x) = { \frac { \sum _{j=0}^{k}{ \frac{w_{j}}{x-x_{j}}}y_{j}}{ \sum _{j=0}^{k}{ \frac {w_{j}}{x-x_{j}}}}}$$@
这个公式被称为重心拉格朗日插值公式(第二型)或真正的重心拉格朗日插值公式. 它继承了前式容易计算的特点, 并且在代入x值计算 $L(x)$ 的时候不必计算多项式 $ \ell(x)$
*/
