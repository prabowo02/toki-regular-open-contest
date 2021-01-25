import java.io.*;
import java.util.*;
import java.lang.*;

public class Permutation {


    // static int[][] edge = new int[10005][]; // Jagged array
    // final static INF = Integer.MAX_VALUE;

    static Reader in = new Reader();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static final int MX = 300;
    static final int MXSZ = MX + 5;
    static final int MOD = 998244353;

    static long[][] memo;
    static long[] fact, inv, finv;

    static int[] isi, ori, color;
    static int colorcnt;

    static void prec() {
        fact = new long[MXSZ];
        inv = new long[MXSZ];
        finv = new long[MXSZ];
        fact[0] = inv[0] = finv[0] = fact[1] = inv[1] = finv[1] = 1;
        for(int i = 2; i <= MX; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
            inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
            finv[i] = (finv[i - 1] * inv[i]) % MOD;
        }
    }

    static long comb(int a, int b) {
        return fact[a] * finv[a - b] % MOD * finv[b] % MOD;
    }

    static long dp(int kiri, int kanan) {
        if(memo[kiri][kanan] != -1) return memo[kiri][kanan];
        if(kanan <= kiri || color[kiri] == color[kanan]) return 1;
        long ret = 0;
        if(color[kanan] == color[kanan - 1]) ret += dp(kiri, kanan - 1) % MOD;
        for(int i = kiri; i < kanan; i++) {
            if(color[i] == color[i + 1]) continue;
            if(i > kiri && color[i] != color[i - 1]) continue;
            ret += dp(kiri, i - 1) * dp(i + 1, kanan) % MOD * comb(kanan - kiri, i - kiri) % MOD;
        }
        return memo[kiri][kanan] = ret %= MOD;
    }

    public static void main(String[] args) throws IOException {
        prec();
        int n = in.nextInt();
        isi = new int[n + 1];
        color = new int[n + 1];
        ori = new int[n + 1];
        memo = new long[n + 1][n + 1];
        for(int i = 0;i <= n;i++) for(int j = 0;j <= n;j++) memo[i][j] = -1;
        boolean can = true;
        int lst = 1;
        for(int i = 1;i <= n;i++) isi[i] = ori[i] = in.nextInt();
        for(int i = 1; i <= n; i++) {
            if(!can) break;
            if(ori[i] == i) continue;
            for(int j = 1; j <= n; j++) {
                if(ori[j] == i) {
                    if(j <= lst) {
                        can = false;
                        break;
                    }
                    colorcnt++;
                    for(int k = j - 1; k >= lst; k--) {
                        color[k] = colorcnt;
                        int tmp = ori[k];
                        ori[k] = ori[k + 1];
                        ori[k + 1] = tmp;
                    }
                    lst = j;
                    break;
                }
            }
            if(lst == n) break;

        }

        if(can) {
            if(lst != n) can = false;
            for(int i = 1; i <= n; i++) if(ori[i] != i) { can = false; break; }
        }
        out.println(can ? dp(1, n - 1) : 0L);
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
            while ((c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1)) c = read();
            do {
                buf[cnt++] = c;
                c = read();
            } while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1));
            return new String(buf, 0, cnt);
        }

        public char nextChar() throws IOException {
            byte c = read();
            while ((c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1)) c = read();
            return (char)c;
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[1 << 10]; // line length
            int cnt = 0;
            byte c;
            do {
                c = read();
                buf[cnt++] = c;
            } while (!(c == '\n' || c == '\r' || c == -1));
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException {
            int ret = 0;
            boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9') {
                if(c == '-') sgn = true;
                c = read();
            }
            do {
                ret = (ret << 3) + (ret << 1) + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            return (sgn ? -ret : ret);
        }

        public long nextLong() throws IOException {
            long ret = 0;
            boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9') {
                if(c == '-') sgn = true;
                c = read();
            }
            do {
                ret = (ret << 3) + (ret << 1) + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            return (sgn ? -ret : ret);
        }

        public double nextDouble() throws IOException {
            double ret = 0;
            boolean sgn = false;
            byte c = read();
            while (c < '0' || c > '9') {
                if(c == '-') sgn = true;
                c = read();
            }
            do {
                ret = (ret * 10) + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if(c == '.') {
                double temp = 1;
                c = read();
                do {
                    ret += (temp /= 10) * (c - '0');
                } while ((c = read()) >= '0' && c <= '9');
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
