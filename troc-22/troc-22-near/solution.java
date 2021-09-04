import java.io.*;
import java.util.*;

public class solution {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    Solver solver = new Solver();
    solver.Main(in, out);
    out.close();
  }

  static class Solver {
    static final int MOD = 998244353;

    static int N;
    static int K;
    static int[] P;

    int boolToInt(boolean b) {
      if (b) {
        return 1;
      } else {
        return 0;
      }
    }

    int id(int i, int u, int x, int y) {
      return i * N * N * 2 + u * N * 2 + x * 2 + y;
    }

    int add(int x, int y) {
      x += y;
      if (x >= MOD) {
        x -= MOD;
      }
      return x;
    }

    int mul(int x, int y) {
      return (int) (1l * x * y % MOD);
    }

    int Solve() {
      Vector<Vector<Integer>> adj = new Vector<>();
      for (int i = 0; i < N; i++)
        adj.add(new Vector<Integer>());
      for (int i = 1; i < N; i++) {
        adj.get(P[i]).add(i);
      }
      int[][] choose = new int[K + 1][K + 1];
      for (int i = 0; i <= K; i++) {
        choose[i][0] = 1;
        for (int j = 1; j <= i; j++) {
          choose[i][j] = add(choose[i - 1][j - 1], choose[i - 1][j]);
        }
      }
      // dp[power][node][label][is connected to lower label]
      int[] dp = new int[(K + 1) * N * N * 2];
      for (int u = N - 1; u >= 0; u--) {
        int[] all_g = new int[K + 1];
        int[] all_b = new int[K + 1];
        int[] cur_g = new int[K + 1];
        int[] cur_b = new int[K + 1];
        for (int x = N - 1; x >= 0; x--) {
          for (int y = 0; y < 2; y++) {
            if (x == 0) {
              for (int i = 0; i <= K; i++) {
                dp[id(i, u, x, y)] = dp[id(i, u, 1, y)];
              }
              continue;
            }
            all_g[0] = 1;
            all_b[0] = boolToInt(y == 0);
            for (int i = 1; i <= K; i++) {
              all_g[i] = mul(all_g[i - 1], x);
              if (y == 0) {
                all_b[i] = all_g[i];
              } else {
                all_b[i] = 0;
              }
            }
            for (int v_ = 0; v_ < adj.get(u).size(); v_++) {
              int v = adj.get(u).get(v_);
              for (int i = 0; i <= K; i++) {
                cur_g[i] = cur_b[i] = 0;
                for (int d = -1; d <= 1; d++) {
                  if (0 <= x + d && x + d < N) {
                    cur_g[i] = add(cur_g[i], dp[id(i, v, x + d, boolToInt(d == 1 || (x + d == 0)))]);
                    if (d != -1) {
                      cur_b[i] = add(cur_b[i], dp[id(i, v, x + d, boolToInt(d == 1 || (x + d == 0)))]);
                    }
                  }
                }
              }
              for (int i = K; i >= 0; i--) {
                int new_g = 0, new_b = 0;
                for (int j = 0; j <= i; j++) {
                  new_g = add(new_g, mul(choose[i][j] * all_g[j], cur_g[i - j]));
                  new_b = add(new_b, mul(choose[i][j] * all_b[j], cur_b[i - j]));
                }
                all_g[i] = new_g;
                all_b[i] = new_b;
              }
            }
            for (int i = 0; i <= K; i++) {
              dp[id(i, u, x, y)] = add(all_g[i], MOD - all_b[i]);
            }
          }
        }
      }
      int ans = 1;
      for (int i = 0; i < K; i++) {
        ans = mul(ans, MOD - N);
      }
      for (int i = 1; i < N; i++) {
        ans = add(ans, dp[id(K, 0, i, boolToInt(i == 0))]);
      }
      ans = add(ans, ans);
      return ans;
    }

    public void Main(InputReader in, PrintWriter out) {
      N = in.nextInt();
      K = 2;
      P = new int[N];
      for (int i = 1; i < N; i++) {
        P[i] = in.nextInt() - 1;
      }
      out.println(Solve());
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
