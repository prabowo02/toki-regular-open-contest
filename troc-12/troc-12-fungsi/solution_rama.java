// Author   : rama_pang
// Problem  : troc-12-fungsi
// Time     : O(A B log max(X, Y) + Q log max(X, Y))
// Memory   : O(A B log max(X, Y))

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
    Fungsi solver = new Fungsi();
    solver.solve(in, out);
    out.close();
  }

  static class Fungsi {
    private int MAXN = 100005;
    private int BITS = 30;

    private int A, B, KA, KB, LA, LB;
    private long[][] func = new long[MAXN][BITS];

    public void solve(InputReader in, PrintWriter out) {
      A = in.nextInt();
      B = in.nextInt();
      KA = in.nextInt();
      KB = in.nextInt();
      LA = in.nextInt();
      LB = in.nextInt();
      Build();

      int Q;
      Q = in.nextInt();

      for (int i = 0; i < Q; i++) {
        int X, Y;
        X = in.nextInt();
        Y = in.nextInt();
        out.println(Query(X, Y));
      }
    }

    private void Build() {
      for (int a = 0; a < A; a++) {
        for (int b = 0; b < B; b++) {
          if (a == KA) {
            func[a * B + b][0] = LA;
          } else if (b == KB) {
            func[a * B + b][0] = LB;
          } else {
            func[a * B + b][0] = 1;
          }
        }
      }
    
      for (int j = 1; j < BITS; j++) {
        for (int i = 0; i < A * B; i++) {
          int a = i / B, b = i % B;
          if ((a -= func[i][j - 1] % A) < 0) a += A; 
          if ((b -= func[i][j - 1] % B) < 0) b += B;
          func[i][j] = func[i][j - 1] + func[a * B + b][j - 1];
        }
      }
    }

    private int Query(int X, int Y) {
      int[] DX = FindRoot(X);
      int[] DY = FindRoot(Y);
      if (DX[0] > DY[0]) {
        int T;
        T = X; X = Y; Y = T;
        int[] T2;
        T2 = DX; DX = DY; DY = T2;
      }
    
      if (DX[1] != DY[1]) return -1;
      Y = Lift(Y, DY[0] - DX[0]);
    
      for (int j = BITS - 1; j >= 0; j--) {
        if (X - func[(X % A) * B + (X % B)][j] != Y - func[(Y % A) * B + (Y % B)][j]) {
          X -= func[(X % A) * B + (X % B)][j];
          Y -= func[(Y % A) * B + (Y % B)][j];
        }
      }
      
      if (X != Y) {
        X -= func[(X % A) * B + (X % B)][0];
      }

      return X;
    }

    private int[] FindRoot(int X) {
      int depth = 0;
      for (int j = BITS - 1; j >= 0; j--) {
        if (X > func[(X % A) * B + (X % B)][j]) {
          X -= func[(X % A) * B + (X % B)][j];
          depth |= 1 << j;
        }
      }
      int[] res = new int[2];
      res[0] = depth;
      res[1] = X;
      return res;
    }

    private int Lift(int X, int D) {
      for (int j = 0; j < BITS; j++) {
        if ((D & (1 << j)) > 0) {
          X -= func[(X % A) * B + (X % B)][j];
        }
      }
    
      return X;
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
