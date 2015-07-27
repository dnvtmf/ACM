///异或Xor
/*
性质:	1. 0 xor 1 = 0, 1 xor 0 = 1, 0 xor 0 = 0, 1 xor 1 = 1
		2. (交换律) a xor b = b xor a
		3. (结合律) (a xor b) xor c = a xor (b xor c)
		4. a xor a = 0
		5. 0 xor a = a
		6. (二进制分解) $a xor b = \sum_{i=0}^{\infty}{a_i xor b_i}$, 其中 $a_i, b_i$是数a, b的二进制表达的第i位
			不同位置上运算互不影响
		7. 若a为偶数, 则 a xor (a + 1) = 1, a xor 1 = (a + 1), (a + 1) xor 1 = a
*/
