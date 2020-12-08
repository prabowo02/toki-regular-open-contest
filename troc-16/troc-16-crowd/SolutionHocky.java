import java.io.*;
import java.util.*;
import java.lang.*;

public class SolutionHocky{


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static int n;
    static int[] par = new int[505];
    static boolean[] parity = new boolean[505];

    static class Pair implements Comparable<Pair> {
        int val, u, v;
        Pair(int val, int u, int v){
            this.val = val;
            this.u = u;
            this.v = v;
        }
        @Override
        public int compareTo(Pair other) {
            if(val != other.val) return val-other.val;
            if(u != other.u) return u-other.u;
            return v-other.v;
        }
    }

    static boolean merge(int u, int v){
        // out.println(u + " " + v + " : " + par[u] + " " + par[v]);
        // out.println(parity[u]);
        // out.println(parity[v]);
        if(par[u] == par[v]) return parity[u] != parity[v];
        ArrayList<Integer> tmp = new ArrayList<Integer>(n);
        for(int i = 1;i <= n;i++) if(par[i] == par[v]) tmp.add(i);
        boolean same = (parity[u] == parity[v]);
        for(Integer cur : tmp){
            par[cur] = par[u];
            // out.println(parity[cur]);
            parity[cur] = (same ? !parity[cur] : parity[cur]);
            // out.println(parity[cur]);

        }
        return true;
    }
    
    public static void main(String[] args) throws IOException{
        n = in.nextInt();
        for(int i = 1;i <= n;i++) par[i] = i;
        ArrayList <Pair> isi = new ArrayList<Pair>((n*(n-1))/2);
        for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++){
            int tmp = in.nextInt();
            if(i < j) isi.add(new Pair(tmp, i, j));
        }
        boolean found = false;
        Collections.sort(isi);
        for(Pair cur : isi){
            // out.println(cur.u + " " + cur.v + " " + cur.val);
            if(!merge(cur.u, cur.v)){
                found = true;
                out.println(cur.val);
                break;
            }
        }
        if(!found) out.println(isi.get(isi.size()-1).val);
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
