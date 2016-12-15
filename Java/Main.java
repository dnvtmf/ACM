import java.io.*;
import java.util.*;
import java.math.*;
import java.BigInteger;
import java.text.DecimalFormat
public class Main{
	public static void main(String arg[]) throws Exception{
		Scanner cin = new Scnner(System.in);

		BigInteger a, b;
		a = new BigInteger("123");
		a = cin.nextBigInteger();
		a.add(b);//a + b
		a.subtract(b);// a - b
		a.multiply(b);// a * b
		a.divide(b);// a / b
		a.negate();// -a
		a.remainder(b);//a%b
		a.abs();//|a|
		a.pow(b);//$a^b$
		//.... and other math fuction, like log();
		a.toString();
		a.compareTo(b);//
		double c = 2.3659874;
		//小数格式化，引号中的0.000表示保留小数点后三位（第四位四舍五入）
		DecimalFormat df = new DecimalFormat("0.000");
		String num = df.format(a);
		System.out.println(num);

	}
}

//使用大数时注意
//java大数乘法使用FFT, 尽量时位数差不多的数相差, 这样可以节约许多时间
//例: 求n!, (....(((1*2)*3)*...*)*(n-1))*n 用了5.7s+, 而分治的方法用了0.6s+
