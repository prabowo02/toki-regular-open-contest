// Don't place your source in a package
import javax.swing.*;
import java.lang.reflect.Array;
import java.text.DecimalFormat;
import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;
import java.util.stream.Stream;

public class solution_maxi{
	static FastScanner fs = new FastScanner();
	static class FastScanner{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer("");
		public String next(){
			while(!st.hasMoreElements())
				try{
					st = new StringTokenizer(br.readLine());
				}catch(IOException e){
					e.printStackTrace();
				}
			return st.nextToken();
		}
		int Int(){
			return Integer.parseInt(next());
		}
		long Long(){
			return Long.parseLong(next());
		}
		String Str(){
			return next();
		}
	}

	public static void main(String[] args) throws java.lang.Exception{
		PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		//reading /writing file
		//Scanner sc=new Scanner(new File("src/text.txt"));
		//PrintWriter pr=new PrintWriter("output.txt");
		//File file = new File("src/text.txt");

		int T = 1;
		for(int t = 0; t < T; t ++){
			Solution sol1 = new Solution(out,fs);
			sol1.solution(t);
		}
		out.flush();
	}

	public static int[] Arr(int n){
		int A[] = new int[n];
		for(int i=0; i < n; i ++) A[i] = Int();
		return A;
	}
	public static int Int(){
		return fs.Int();
	}
	public static long Long(){
		return fs.Long();
	}
	public static String Str(){
		return fs.Str();
	}
}

class Solution{
	PrintWriter out;
	int INF = Integer.MAX_VALUE;
	int NINF = Integer.MIN_VALUE;
	solution_maxi.FastScanner fs;
	public Solution(PrintWriter out, solution_maxi.FastScanner fs){
		this.out = out;
		this.fs = fs;
	}

	int a[], b[];
	public void solution(int testcase){
		int n = fs.Int(), m = fs.Int(), k = fs.Int();
		a = new int[n];
		b = new int[m];
		for(int i = 0; i < n; i ++)
			a[i] = fs.Int();
		for(int i = 0; i < m; i ++)
			b[i] = fs.Int();

		int mna = n + 1, mxa = -1, cra = 0;
		for(int i = 0; i < k - 1; i ++)
			cra += a[i];
		for(int i = k - 1; i < n; i ++){
			cra += a[i];
			if(mna > cra) mna = cra;
			if(mxa < cra) mxa = cra;
			cra -= a[i + 1 - k];
		}

		int mnb = m + 1, mxb = -1, crb = 0;
		for(int i = 0; i < k - 1; i ++)
			crb += b[i];
		for(int i = k - 1; i < m; i ++){
			crb += b[i];
			if(mnb > crb) mnb = crb;
			if(mxb < crb) mxb = crb;
			crb -= b[i + 1 - k];
		}

		long resa = (long)mxa * (k - mnb) + (long)(k - mxa) * mnb;
		long resb = (long)mxb * (k - mna) + (long)(k - mxb) * mna;
		long resc = (long)mxa * (k - mxb) + (long)(k - mxa) * mxb;
		long resd = (long)mnb * (k - mna) + (long)(k - mnb) * mna;

		long get = -1;
		if(get < resa) get = resa;
		if(get < resb) get = resb;
		if(get < resc) get = resc;
		if(get < resd) get = resd;
		out.println(get);
	}
}