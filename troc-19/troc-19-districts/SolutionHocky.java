import java.io.*;
import java.util.*;
import java.lang.*;

public class SolutionHocky{


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static final int MAXN = 100000;
    static final int MAXM = 1000000;
    static class Kotak{
        int a, b, c, d;
        long area;
        Kotak(int a, int b, int c, int d){
            this.a = a; this.b = b; this.c = c; this.d = d;
        }
    }

    static Kotak[] isi = new Kotak[MAXN + 5];
    static ArrayList bucket[][] = new ArrayList[2][MAXM + 5];


    static class Edge implements Comparable<Edge> {
        int u,v;
        long c;
        Edge(int u, int v, long c){ this.u = u; this.v = v; this.c = c; }
        @Override
        public int compareTo(Edge other) {
            return c < other.c ? -1 : 1;
        }
    }

    static ArrayList <Edge> edges = new ArrayList<Edge>(MAXN * 10 + 5);

    static boolean isOverlapping(int a, int b, boolean x){
        if(x) return !(isi[a].d <= isi[b].b || isi[b].d <= isi[a].b);
        return !(isi[a].c <= isi[b].a || isi[b].c <= isi[a].a);
    }

    static void make_edge(int a, int b){
        // out.println(a + " " + b);
        edges.add(new Edge(a, b, Math.abs(isi[a].area-isi[b].area)));
    }

    static int par[] = new int[MAXN + 5];

    static int findpar(int pos){
        if(par[pos] == pos) return pos;
        return par[pos] = findpar(par[pos]);
    }

    public static void main(String[] args) throws IOException{
        int n = in.nextInt();
        for(int i = 1;i <= n;i++){
            isi[i] = new Kotak(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
            isi[i].area = (long)(isi[i].d-isi[i].b) * (isi[i].c-isi[i].a);
            if(bucket[0][isi[i].a] == null) bucket[0][isi[i].a] = new ArrayList();
            if(bucket[1][isi[i].c] == null) bucket[1][isi[i].c] = new ArrayList();
            bucket[0][isi[i].a].add(i);
            bucket[1][isi[i].c].add(i);
        }

        for(int i = 1;i <= MAXM;i++){
            if(bucket[0][i] != null && bucket[1][i] != null){
                // out.println(i);
                Collections.sort(bucket[0][i], new Comparator(){
                    @Override
                    public int compare(Object o1, Object o2){
                        return (isi[(Integer)o1].b < isi[(Integer)o2].b ? -1 : 1);
                    }
                });
                Collections.sort(bucket[1][i], new Comparator(){
                    @Override
                    public int compare(Object o1, Object o2){
                        return (isi[(Integer)o1].b < isi[(Integer)o2].b ? -1 : 1);
                    }
                });
                int asz = bucket[0][i].size();
                int bsz = bucket[1][i].size();
                int ptra = 0;
                int ptrb = 0;
                while(ptra < asz && ptrb < bsz){
                    int a = (Integer)bucket[0][i].get(ptra);
                    int b = (Integer)bucket[1][i].get(ptrb);
                    if(isOverlapping(a, b, true)) make_edge(a, b);
                    if(isi[a].d < isi[b].d) ptra++;
                    else ptrb++;
                }
            }
            if(bucket[0][i] != null) bucket[0][i].clear();
            if(bucket[1][i] != null) bucket[1][i].clear();
        }

        for(int i = 1;i <= n;i++){
            if(bucket[0][isi[i].b] == null) bucket[0][isi[i].b] = new ArrayList();
            if(bucket[1][isi[i].d] == null) bucket[1][isi[i].d] = new ArrayList();
            bucket[0][isi[i].b].add(i);
            bucket[1][isi[i].d].add(i);
        }


        for(int i = 1;i <= MAXM;i++){
            if(bucket[0][i] == null) continue;
            if(bucket[1][i] == null) continue;
            // out.println(i);
            Collections.sort(bucket[0][i], new Comparator(){
                @Override
                public int compare(Object o1, Object o2){
                    return (isi[(Integer)o1].a < isi[(Integer)o2].a ? -1 : 1);
                }
            });
            Collections.sort(bucket[1][i], new Comparator(){
                @Override
                public int compare(Object o1, Object o2){
                    return (isi[(Integer)o1].a < isi[(Integer)o2].a ? -1 : 1);
                }
            });
            int asz = bucket[0][i].size();
            int bsz = bucket[1][i].size();
            int ptra = 0;
            int ptrb = 0;
            while(ptra < asz && ptrb < bsz){
                int a = (Integer)bucket[0][i].get(ptra);
                int b = (Integer)bucket[1][i].get(ptrb);
                if(isOverlapping(a, b, false)) make_edge(a, b);
                if(isi[a].c < isi[b].c) ptra++;
                else ptrb++;
            }
        }

        int edge_count = 0;
        long ans = 0;

        Collections.sort(edges);
        // out.println("Here");
        for(int i = 1;i <= n;i++) par[i] = i;

        for(Edge cur : edges){
            if(edge_count == n-2) break;
            if(findpar(cur.u) == findpar(cur.v)) continue;
            edge_count++;
            par[par[cur.v]] = par[cur.u];
            ans += cur.c;
        }
        out.println(edge_count == n-2 ? ans : -1);
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
