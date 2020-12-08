import java.io.*;
import java.util.*;
import java.lang.*;

public class SolutionHocky{


    // static int[][] edge = new int[10005][]; // Jagged arraycm

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static class Data{
        int position, val;
        Data(int pos, int v){
            position = pos;
            val = v;
        }
    }
    static class Pair{
        long base, power;
        int kiri;
        Pair(long a, long b){
            base = a;
            power = b;
        }
    }

    static long expo(long a, long b){
        long ret = 1;
        while(b > 0){
            if(b%2 == 1) ret = (ret*a)%MOD;
            a = (a*a)%MOD; b >>= 1;
        }
        return ret;
    }

    static int[] kiri = new int[100005], kanan = new int[100005];
    static long[] isi = new long[100005];
    static ArrayList<ArrayDeque<Data>> monotonDeq = new ArrayList<ArrayDeque<Data>>(100005);
    static ArrayList<ArrayList<Pair>> faktor = new ArrayList<ArrayList<Pair>>(100005);
    static final long MOD = 1000000007;

    public static void main(String[] args) throws IOException{
        int n = in.nextInt();
        for(int i = 0;i <= 100000;i++) monotonDeq.add(null);
        long ans = 1;
        for(int i = 0;i < n;i++){
            isi[i] = in.nextLong();
            ArrayList<Pair> curfaktor = new ArrayList<Pair>();
            long tmp = isi[i];
            for(int j = 2;j <= tmp;j++){
                if(j > tmp/j) break;
                if(tmp%j != 0) continue;
                Pair current = new Pair(j, 0);
                while(tmp%j == 0){
                    current.power++; tmp /= j;
                }
                curfaktor.add(current);
                if(tmp == 1) break;
            }
            if(tmp != 1){ curfaktor.add(new Pair(tmp, 1)); }
            int len = curfaktor.size();
            for(int j = 0;j < len;j++){
                Pair curval = curfaktor.get(j);
                if(monotonDeq.get((int)curval.base) == null){
                    monotonDeq.set((int)curval.base, new ArrayDeque<Data>());
                }
                ArrayDeque<Data> curDeq = monotonDeq.get((int)curval.base);
                while(!curDeq.isEmpty()){
                    // Check last
                    if(curDeq.peekLast().val <= curval.power) curDeq.pollLast();
                    else break;
                }
                curval.kiri = (curDeq.isEmpty() ? 0 : curDeq.peekLast().position+1);
                curDeq.offerLast(new Data(i, (int) curval.power));
            }
            faktor.add(curfaktor);
        }
        for(int i = 0;i <= 100000;i++){
            if(monotonDeq.get(i) != null)
                monotonDeq.get(i).clear();
        }
        for(int i = n-1;i >= 0;i--){

            ArrayList<Pair> curfaktor = faktor.get(i);
            int len = curfaktor.size();
            for(int j = 0;j < len;j++){
                Pair curval = curfaktor.get(j);
                ArrayDeque<Data> curDeq = monotonDeq.get((int)curval.base);
                while(!curDeq.isEmpty()){
                    // Check last
                    if(curDeq.peekFirst().val < curval.power) curDeq.pollFirst();
                    else break;
                }
                long kanan = (curDeq.isEmpty() ? n-1 : curDeq.peekFirst().position-1);
                curDeq.offerFirst(new Data(i, (int) curval.power));
                long contrib = (long)(i-curval.kiri+1)*(kanan-i+1);
                ans = (ans*expo(expo(curval.base,curval.power)%MOD,contrib))%MOD;
            }
        }
        out.println(ans);
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
