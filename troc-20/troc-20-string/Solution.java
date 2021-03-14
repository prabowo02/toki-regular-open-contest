import java.io.*;
import java.util.*;
import java.lang.*;

public class Solution {
  static Reader in = new Reader();
  static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

  static final int MOD = 998244353;

  public static void main(String[] args) throws IOException{
    int N = in.nextInt();
    String S = in.next(N);
    long[] A = new long[N];
    long[] B = new long[N];
    for (int i = 0; i < N; i++) {
      if (S.charAt(i) == '0') {
        A[i] = 1;
        B[i] = 0;
      } else if (S.charAt(i) == '1') {
        A[i] = 0;
        B[i] = 1;
      } else if (S.charAt(i) == '?') {
        A[i] = (MOD + 1) / 2;
        B[i] = (MOD + 1) / 2;
      }
    }

    long[][][] cnt = new long[N + 1][2][N + 2];
    long[][][] sum = new long[N + 1][2][N + 2];

    for (int i = N; i >= 0; i--) {
      for (int bal = 0; bal <= N; bal++) {
        cnt[i][0][bal] = cnt[i][1][bal] = 0;
        sum[i][0][bal] = sum[i][1][bal] = 0;
        if (i == N) {
          if (bal == 0) cnt[i][0][bal] += 1;
          if (bal >= 1) cnt[i][1][bal] += 1;
        } else {
          // Place 0
          if (bal >= 0) cnt[i][0][bal] += A[i] * cnt[i + 1][0][Math.max(bal - 1, 0)] % MOD;
          if (bal >= 0) sum[i][0][bal] += A[i] * cnt[i + 1][0][Math.max(bal - 1, 0)] % MOD;
          if (bal >= 0) sum[i][0][bal] += A[i] * sum[i + 1][0][Math.max(bal - 1, 0)] % MOD;

          if (bal >= 2) cnt[i][1][bal] += A[i] * cnt[i + 1][1][Math.max(bal - 1, 0)] % MOD;
          if (bal >= 2) sum[i][1][bal] += A[i] * sum[i + 1][1][Math.max(bal - 1, 0)] % MOD;

          // Place 1
          if (bal >= 0) cnt[i][0][bal] += B[i] * cnt[i + 1][0][bal + 1] % MOD;
          if (bal >= 0) sum[i][0][bal] += B[i] * sum[i + 1][0][bal + 1] % MOD;

          if (bal == 0) cnt[i][0][bal] += B[i] * cnt[i + 1][1][bal + 1] % MOD;
          if (bal == 0) sum[i][0][bal] += B[i] * cnt[i + 1][1][bal + 1] % MOD;
          if (bal == 0) sum[i][0][bal] += B[i] * sum[i + 1][1][bal + 1] % MOD;

          if (bal >= 0) cnt[i][1][bal] += B[i] * cnt[i + 1][1][bal + 1] % MOD;
          if (bal >= 0) sum[i][1][bal] += B[i] * cnt[i + 1][1][bal + 1] % MOD;
          if (bal >= 0) sum[i][1][bal] += B[i] * sum[i + 1][1][bal + 1] % MOD;
        }
        cnt[i][0][bal] %= MOD;
        cnt[i][1][bal] %= MOD;
        sum[i][0][bal] %= MOD;
        sum[i][1][bal] %= MOD;
      }
    }

    out.println((N - sum[0][0][0] + MOD) % MOD);
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
      return (char) c;
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
