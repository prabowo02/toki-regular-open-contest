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

	public long max(long A, long B){
		if(A < B) return B;
		return A;
	}

	int a[];
	long L[], r[];
	public void solution(int testcase){
		int n = fs.Int();
		a = new int[100005];
		L = new long[100005];
		r = new long[100005];
		for(int i = 1; i <= n; i ++)
			a[i] = fs.Int();

		for(int i = 2; i <= n; i ++)
			L[i] = L[i - 1] + (long)a[i - 1] + 1;

		int z = -1;
		for(int i = 1; i <= n; i ++)
			if(a[i] >= L[i]) z = i;

		r[z + 1] = 0;
		for(int i = z + 2; i <= n; i ++){
			r[i] = r[i - 1];
			if(a[i - 1] <= r[i - 1])
				r[i] ++;
		}

		long R = 0;
		for(int i = z + 1; i <= n; i ++)
			R += max(0, a[i] - r[i]);

		if(L[z] + R >= a[z])
			out.println("YES");
		else
			out.println("NO");
	}
}