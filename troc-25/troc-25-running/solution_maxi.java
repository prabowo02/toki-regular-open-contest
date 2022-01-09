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

	public void solution(int testcase){
		int t = fs.Int(), k = fs.Int();
		long res = k;
		for(int i = 0; i < t - k; i ++)
			res *= 2;
		if(t < k) res = t;
		out.println(res);
	}
}