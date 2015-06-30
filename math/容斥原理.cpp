/*容斥原理
 * 集合S中具有性质@$p_i(i=1,2,\cdots ,m)$@的元素所组成的集合为@$A_i$@,则S中不具有性质@$p_1, p_2, \cdots ,p_m$@的元素个数为
 * @$|\overline{A_1} \cap \overline{A_2} \cap \cdots \overline{A_m} = |S| - \sum_{i=1}^{m}{|A_i|} + \sum_{i\neq j}{A_i \cap A_j} - \sum_{i \neq j \neq k}{|A_i \cap A_j \cap A_k} + \cdots + (-1)^m|A_1 \cap A_2 \cap \cdots \cap A_m|$@
 */
/*重集的r-组合
 * 重集@$B = \{k_1\cdot a_1, k_2\cdot a_2, \cdots , k_n\cdot a_n  \}$@的r-组合数:
 * 利用容斥原理，求出重集@$B'=\{\infty \cdot a_1, \infty \cdot a_2, \cdots,\infty \cdot a_n\}$@的r-组合数F(n,r)
 * 在求出满足自少含@$k_i + 1$@个@$a_i(1\leq i \leq n)$@的r-组合数，等同于重集B'的@$r-k_i-1$@-组合数
 * ....
 * 右容斥原理得：重集B的r-组合数为：
 * @$$F(n,r) - \sum_{i=1}^{n}{F(n, r- k_i - 1)} + \sum_{i\neq j}{F(n, r - k_i - k_j - 2)} + \cdots + (-1)^nF(n, r - k_1 - k_2 - \cdots - k_n - n)$$@
 */
