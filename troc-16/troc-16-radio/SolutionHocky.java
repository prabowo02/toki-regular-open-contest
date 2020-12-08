import java.io.*;
import java.util.*;
import java.lang.*;

public class SolutionHocky{


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static long[] x = new long[200005];
    static long[] y = new long[200005];
    static long[] u = new long[25];
    static long[] v = new long[25];
    static long[] c = new long[25];
    static int[] memo = new int[(1<<20)];
    static int[] mask = new int[200005];
    static long[] ans = new long[200005];
    public static void main(String[] args) throws IOException{
        int n = in.nextInt(), m = in.nextInt();
        long r = in.nextLong();
        for(int i = 1;i <= n;i++){
            x[i] = in.nextLong();
            y[i] = in.nextLong();
        }
        for(int i = 0;i < m;i++){
            u[i] = in.nextLong();
            v[i] = in.nextLong();
            c[i] = in.nextLong();
        }
        Arrays.fill(ans, Long.MAX_VALUE);
        for(int i = 1;i <= n;i++){
            for(int j = 0;j < m;j++){
                // Get distance, set mask if on
                if((x[i]-u[j])*(x[i]-u[j]) + (y[i]-v[j])*(y[i]-v[j]) > r*r){
                    mask[i] |= (1 << j);
                    // out.println(i + " " + j);
                    // out.flush();
                }
            }
            memo[(int)mask[i]]++;
        }
        for(int i = 0;i < m;i++) for(int curmask = 0; curmask < (1<<m); ++curmask){
            if((curmask & (1<<i)) == 0) memo[curmask] += memo[curmask^(1<<i)];
        }
        for(int curmask = 0; curmask < (1<<m); ++curmask){
            // out.println(curmask + " " + memo[curmask]);
            memo[curmask] = n-memo[curmask];
            long curcost = 0;
            for(int i = 0;i < m;i++){
                if((curmask&(1<<i)) != 0){
                    curcost += c[i];
                }
            }
            ans[(int)memo[curmask]] = Math.min(ans[(int)memo[curmask]], curcost);
        }
        for(int i = (int)n-1;i >= 1;i--){
            ans[i] = Math.min(ans[i], ans[i+1]);

        }
        for(int i = 1;i <= n;i++){
            ans[i] = (ans[i] == Long.MAX_VALUE ? -1 : ans[i]);
            out.println(ans[i]);
        }
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
