// Author   : rama_pang
// Problem  : troc-12-frekuensi
// Time     : O(N^3)
// Memory   : O(N^3)

import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class solution_rama {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    Frekuensi solver = new Frekuensi();
    solver.solve(in, out);
    out.close();
  }

  static class Frekuensi {
    private int MAXN = 255;

    private int N;
    private int L;
    private int R;

    private int[][] A;
    private int[][][] P;
    
    private int[][][] id;
    private int[][][] cnt;

    public void solve(InputReader in, PrintWriter out) {
      Read(in);
      out.println(Solve());
    }

    private void Read(InputReader in) {
      N = in.nextInt();
      L = in.nextInt();
      R = in.nextInt();

      A = new int[N + 5][N + 5];
      P = new int[N + 5][N + 5][MAXN];
      
      id = new int[N + 5][N + 5][2];
      cnt = new int[N + 5][N + 5][2 * N + 5];

      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          A[i][j] = in.nextInt();
          id[i][j][0] = i;
          id[i][j][1] = j;
        }
      }
    }

    private long Solve() {
      for (int rot = 0; rot < 4; rot++) {
        Rotate(); Calc();
        CountContribution();
      }

      long ans = 0;
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          for (int d = 1; d <= 2 * N; d++) {
            ans += cnt[i][j][d] * cnt[i][j][d]; // (cnt for direct, (cnt * (cnt - 1)) for indirect)
          }
        }
      }
      
      return ans;
    }

    private void Rotate() {
      int[][] A_ = new int[N + 5][N + 5];
      int[][][] id_ = new int[N + 5][N + 5][2];

      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          A_[N - j + 1][i] = A[i][j];
          id_[N - j + 1][i] = id[i][j];
        }
      }

      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          A[i][j] = A_[i][j];
          id[i][j] = id_[i][j];
        }
      }
    }

    private void Calc() {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          for (int k = 0; k < MAXN; k++) {
            P[i][j][k] = 0;
          }
        }
      }

      for (int i = N; i >= 1; i--) {
        for (int j = N; j >= 1; j--) {
          P[i][j][A[i][j]]++;
          for (int k = 0; k < MAXN; k++) {
            P[i][j][k] += P[i + 1][j - 1][k];
          }
        }
      }
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          for (int k = 1; k < MAXN; k++) {
            P[i][j][k] += P[i][j][k - 1];
          }
        }
      }
    }

    private void CountContribution() {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {    
          for (int d = 1; d <= i + j - 2; d++) { // Manhattan Distance
            int l = (d * L + A[i][j] - 1) / A[i][j] - 1;
            int r = (d * R) / A[i][j];

            // Count (x, y) which satisfies l < A[x][y] <= r in the diagonal (distance is fixed)
            int offset = Math.max(0, 1 - i + d);
            int n = id[i][j][0]; int m = id[i][j][1];
            cnt[n][m][d] += P[i - d + offset][Math.max(j - offset, 0)][Math.min(r, MAXN - 1)];
            cnt[n][m][d] -= P[i][Math.max(j - d, 0)][Math.min(r, MAXN - 1)];
            if (l == -1) continue;
            cnt[n][m][d] -= P[i - d + offset][Math.max(j - offset, 0)][Math.min(l, MAXN - 1)];
            cnt[n][m][d] += P[i][Math.max(j - d, 0)][Math.min(l, MAXN - 1)];
          }
        }
      }
    }
  }

  static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
  }
}
