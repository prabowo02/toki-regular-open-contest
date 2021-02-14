import java.io.*;
import java.util.*;
import java.lang.*;

public class SolutionHocky{


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static final int MAXN = 40;
    static final int MOD = 998244353;

    static int n, m, a, b, c;
    static int[][] memoC = new int[MAXN + 5][MAXN + 5];
    static int C(int n, int k){
        if (memoC[n][k] != -1) return memoC[n][k];
        if (k == 0 || k == n) return memoC[n][k] = 1;
        return memoC[n][k] = (C(n - 1, k - 1) + C(n - 1, k)) % MOD;
    }

    static int[][] memoPower = new int[MAXN + 5][MAXN + 5];
    static int power(int n, int m){
        if(memoPower[n][m] != -1) return memoPower[n][m];
        if(m == 0) return 1;
        return memoPower[n][m] = (int)((long) n * power(n, m-1) % MOD);
    }

    static int[][] memoCount = new int[MAXN + 5][MAXN + 5];
    static int count(int n, int m){
        if(memoCount[n][m] != -1) return memoCount[n][m];
        if(m == 0) return 1;
        return memoCount[n][m] = (int)((long) n * (n + 1) / 2 * count(n, m-1) % MOD);
    }

    static int[][] memoCc = new int[MAXN + 5][MAXN + 5];
    static int countCc(int n, int m){
        if(memoCc[n][m] != -1) return memoCc[n][m];
        int ret = count(n, m);
        for(int i = 1;i < n;i++) for(int j = i-1;j <= m;j++){
            ret = (int)(((long)ret - (long) countCc(i, j) * count(n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j)) % MOD);
        }
        if(ret < 0) ret += MOD;
        return memoCc[n][m] = ret;
    }

    static int[][][][] memoCcs = new int[MAXN + 5][2][MAXN + 5][MAXN + 5];
    static int countCcs(int num, int nopar, int n, int m) {
        if(memoCcs[num][nopar][n][m] != -1) return memoCcs[num][nopar][n][m];
        if(num == 0){
            if(nopar == 1) return memoCcs[num][nopar][n][m] = count(n, m);
            return memoCcs[num][nopar][n][m] = (n == 0 && m == 0 ? 1 : 0);
        }
        int ret = 0;

        for (int i = 1; i <= n; ++i) for (int j = 0; j <= m; ++j) {
            if (j < m) {
                ret = (int)(((long) ret + (long) countCc(i, j) * countCcs(num - 1, nopar, n - i, m - j - 1) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * (m - j) * i) % MOD);
            }
            if (nopar == 1) {
                ret = (int)(((long) ret + (long) count(i, j) * countCcs(num, 0, n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j)) % MOD);
            }
        }
        return memoCcs[num][nopar][n][m] = ret;
    }

    static int[][] memo2Edge = new int[MAXN + 5][MAXN + 5];
    static int count2Edge(int n, int m) {
        if (memo2Edge[n][m] != -1) return memo2Edge[n][m];
        int ret = countCc(n, m);
        for (int i = 1; i < n; ++i) for (int j = 0; j <= m; ++j) for (int k = 1; k <= n - i; ++k) {
            ret = (int)(((long) ret - (long) count2Edge(i, j) * countCcs(k, 0, n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * power(i, k)) % MOD);
            }
        if (ret < 0) ret += MOD;
        return memo2Edge[n][m] = ret;
    }

    static int[][] memo2Cc = new int[MAXN + 5][MAXN + 5];
    static int count2Cc(int n, int m){
        if(memo2Cc[n][m] != -1) return memo2Cc[n][m];
        int ret = 0;
        for (int i = 1; i < n; ++i) for (int j = i - 1; j <= m; ++j) {
            ret = (int)(((long) ret + (long) countCc(i, j) * countCc(n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * i * (n - i)) % MOD);
        }
        return memo2Cc[n][m] = ret;
    }

    static int solve(int n, int m) {
        int ret = (int)((long) count(n, m) * c % MOD * m % MOD);
        // out.println(count(n, m) * c );
        for (int edge = 0; edge < m; ++edge) {
            for (int i = 2; i <= n; ++i) for (int j = i - 2; j <= edge; ++j) {
                ret = (int)(((long) ret + (long) count2Cc(i, j) * count(n - i, edge - j) % MOD * C(n, i) % MOD * C(edge, j) % MOD * count(n, m - edge - 1) % MOD * (a - c)) % MOD);
            }

            for (int i = 1; i <= n; ++i) for (int j = 0; j <= edge; ++j) for (int k = 0; k <= n - i; ++k) {
                ret = (int)(((long) ret + (long) count2Edge(i, j) * countCcs(k, 1, n - i, edge - j) % MOD * C(n, i) % MOD * C(edge, j) % MOD * power(i, k) % MOD * i * (i + 1) / 2 % MOD * count(n, m - edge - 1) % MOD * (b - c)) % MOD);
            }
        }
        if (ret < 0) ret += MOD;
        return ret;
    }


    static int inv(int x){
        int ret = 1;
        for(int y = MOD - 2; y > 0; y >>= 1){
            if((y & 1) != 0) ret = (int)((long)ret * x % MOD);
            x = (int)((long) x * x % MOD);
        }
        return ret;
    }

    public static void main(String[] args) throws IOException{
        n = in.nextInt(); m = in.nextInt();
        a = in.nextInt(); b = in.nextInt(); c = in.nextInt();
        for(int[] i : memoC) Arrays.fill(i, -1);
        for(int[] i : memoPower) Arrays.fill(i, -1);
        for(int[] i : memoCount) Arrays.fill(i, -1);
        for(int[] i : memoCc) Arrays.fill(i, -1);
        for(int[] i : memo2Edge) Arrays.fill(i, -1);
        for(int[][][] i : memoCcs) for(int[][] j : i) for(int[] k : j) Arrays.fill(k, -1);
        for(int[] i : memo2Cc) Arrays.fill(i, -1);
        out.println((long) solve(n, m) * inv(count(n, m)) % MOD);
        out.close();
    }
    
    static class Reader {
        // BUFFER_SIZE must be good enough to support all of your input
        final private int BUFFER_SIZE = 1 << 20;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
        public Reader() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public String next(int maxlen) throws IOException {
            byte[] buf = new byte[maxlen]; // line length
            int cnt = 0;
            byte c = read();
            while ((c==' '||c=='\n'||c=='\r'||c=='\t'||c==-1)) c = read();
            do {
                buf[cnt++] = c; c = read();
            } while (!(c==' '||c=='\n'||c=='\r'||c=='\t'||c==-1));
            return new String(buf, 0, cnt);
        }

        public char nextChar() throws IOException {   
            byte c = read();
            while ((c==' '||c=='\n'||c=='\r'||c=='\t'||c==-1)) c = read();
            return (char)c;
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[1 << 10]; // line length
            int cnt = 0; byte c;
            do {
                c = read(); buf[cnt++] = c;
            } while (!(c=='\n'||c=='\r'||c==-1));
            return new String(buf, 0, cnt);
        }
        
        public int nextInt() throws IOException {
            int ret = 0; boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9'){
                if(c == '-') sgn = true;
                c = read();
            }
            do { ret = (ret << 3) + (ret << 1) + c - '0'; } while ((c = read()) >= '0' && c <= '9');
            return (sgn ? -ret : ret);
        }

        public long nextLong() throws IOException {
            long ret = 0; boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9'){
                if(c == '-') sgn = true;
                c = read();
            }
            do { ret = (ret << 3) + (ret << 1) + c - '0'; } while ((c = read()) >= '0' && c <= '9');
            return (sgn ? -ret : ret);
        }
        
        public double nextDouble() throws IOException{
            double ret = 0; boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9'){
                if(c == '-') sgn = true;
                c = read();
            }
            do { ret = (ret * 10) + c - '0'; } while ((c = read()) >= '0' && c <= '9');
            if(c == '.'){
                double temp = 1; c = read();
                do { ret += (temp /= 10) * (c - '0'); } while ((c = read()) >= '0' && c <= '9');
            }
            return (sgn ? -ret : ret);

        }
        
        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null)
                return;
            din.close();
        }
    }
}
