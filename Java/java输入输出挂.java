import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
	public static void main(String[] args)
	{
		InputReader in = new InputReader();
		PrintWriter out = new PrintWriter(System.out);
		out.close();
	}
}
class InputReader
{
	BufferedReader buf;
	StringTokenizer tok;
	InputReader()
	{
		buf = new BufferedReader(new InputStreamReader(System.in));
	}
	boolean hasNext()
	{
		while(tok == null || !tok.hasMoreElements()) 
		{
			try
			{
				tok = new StringTokenizer(buf.readLine());
			} 
			catch(Exception e) 
			{
				return false;
			}
		}
		return true;
	}
	String next()
	{
		if(hasNext()) return tok.nextToken();
		return null;
	}
	int nextInt()
	{
		return Integer.parseInt(next());
	}
	long nextLong()
	{
		return Long.parseLong(next());
	}
	double nextDouble()
	{
		return Double.parseDouble(next());
	}
	BigInteger nextBigInteger()
	{
		return new BigInteger(next());
	}
	BigDecimal nextBigDecimal()
	{
		return new BigDecimal(next());
	}
}
