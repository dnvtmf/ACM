/*1. 三角形
 * 顶点A,B,C,边a，b，c
 * 内接圆半径r，外接圆半径R
 * 三角形面积: @$$S_{\Delta ABC} = \frac{1}{2} ab \sin{\alpha} = \frac{1}{2} \times |\overrightarrow{AB} \times \overrightarrow{AC}|$$
		$$S_{\Delta ABC} = \frac{1}{2}hc$$
		$$S_{\Delta ABC} = \frac{abc}{4R} = \frac{(a+b+c)r}{2}$$
		$$S_{\Delta ABC} = \sqrt{p(p-a)(p-b)(p-c)}\ \ \ (p=\frac{1}{2}(a+b+c))$$@
 * 外接圆：圆心（外心）：三条边上垂直平分线的交点，半径R：外心到顶点距离
 * 两条垂直平分线：@$(x - \frac{x_A+x_B}{2})(x_A - x_B) = -(y_A-y_B)(y-\frac{y_A+y_B}{2})$@
 *			和	@$(x - \frac{x_B+x_C}{2})(x_B - x_C) = -(y_B-y_C)(y-\frac{y_B+y_C}{2})$@
 *			外心坐标：@$$x = \frac{\displaystyle \frac{(x_A - x_B)(x_A + x_B)}{2y_A - 2y_B} - \frac{(x_B - x_C)(x_B + x_C)}{2y_B - 2y_C} + \frac{y_A + y_B}{2} - (y_B + y_C)}{\displaystyle \frac{x_A-x_B}{y_A - y-B} - \frac{x_B - x_C}{y_B - y_C}}$$
 			$$y = \frac{\displaystyle \frac{(y_A-y_B)(y_A+y_B)}{2x_A - 2x_B} - \frac{(y_B-y_C)(y_B+y_C)}{2x_B-2x_C} + \frac{x_A + x_B}{2} - (x_B+x_C)}{\displaystyle \frac{y_A-y_B}{x_A - x_B} - \frac{y_B-y_C}{x_B-x_C}}$$@
 * 外心:Line((A+B)*0.5, (A-B).rot(PI*0.5)+(A+B)*0.5)&Line((B+C)*0.5,(B-C).rot(PI*0.5)+(B+C)*0.5);
 * 内切圆：内心：角平分线的交点，半径r:内心到边的距离
 *
 * 三角形的质心：三条高的交点: Q = (A+B+C)*(1.0/3.0)
 */

 //2. 多边形
 /*判断点在多边形内外
 */
 /*4. 圆
 */
