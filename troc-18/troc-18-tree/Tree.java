import java.io.*;
import java.util.*;
import java.lang.*;

public class Tree{


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static ArrayList<Integer>[] edge;
    static int[] fir, las, dfscnt, parity;

    static class Bit{
        int n, logN;
        int[] BITVal;
        Bit (int N){
            this.n = N;
            BITVal = new int[N+1];
        }
        void upd(int pos, int val){
            if(pos <= 0) return;
            for(;pos <= n;pos += (pos&(-pos))) BITVal[pos] ^= val;
        }
        int get(int pos){
            int ret = 0;
            for(;pos > 0;pos -= (pos&(-pos))) ret ^= BITVal[pos];
            return ret;
        }
    }

    static void preOrder(int pos, int par){
        // out.println(dfscnt[parity[pos]]);
        fir[pos] = ++dfscnt[parity[pos]];
        if(edge[pos] != null)
        for(int nx : edge[pos]){
            if(nx == par) continue;
            parity[nx] = parity[pos]^1;
            preOrder(nx, pos);
        }
        las[pos] = ++dfscnt[parity[pos]];
    }

    public static void main(String[] args) throws IOException{
        int n = in.nextInt();
        edge = new ArrayList[n];
        parity = new int[n];
        fir = new int[n];
        las = new int[n];
        dfscnt = new int[2];
        for(int i = 0;i < n-1;i++){
            int u = in.nextInt()-1;
            int v = in.nextInt()-1;
            if(edge[u] == null) edge[u] = new ArrayList<Integer>();
            edge[u].add(v);
            if(edge[v] == null) edge[v] = new ArrayList<Integer>();
            edge[v].add(u);
        }

        preOrder(0, -1);
        // for(int i = 0;i < n;i++) out.println("" + i + " " + fir[i] + " " + las[i]);

        Bit solve[] = new Bit[2];
        solve[0] = new Bit(2*dfscnt[0]+1);
        solve[1] = new Bit(2*dfscnt[1]+1);

        int q = in.nextInt();
        while(q --> 0){
            int t = in.nextInt();
            int x = in.nextInt()-1;
            if(t == 1){
                int z = in.nextInt();
                solve[parity[x]].upd(fir[x], z);
                solve[parity[x]].upd(las[x], z);
            }else{
                // out.println(fir[x]);
                out.println(solve[parity[x]].get(fir[x]));
            }
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
