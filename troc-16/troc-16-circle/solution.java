import java.io.*;
import java.util.*;

public class solution {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    Circle solver = new Circle();
    solver.solve(in, out);
    out.close();
  }

  static class Circle {
    private long n;
    private long m = 0;
    private long nn = 0;
    private long[] nm = new long[2];
    private long ub = (long) 1e15;
    private long[] a = new long[100069];
    private long[] pr = new long[100069];
    private long[] dg = new long[100069];
    private long[] od = new long[100069];
    private long[] pst = new long[100069];
    private long[][] nr = new long[2][100069];
    private long[][] ps = new long[2][100069];
    private long z = 0;
    private long dv = (long) 1e9 + 7;
    private long inf = (long) 1e15;
    private Triple[] ed = new Triple[200069];
    private Pair[] al = new Pair[400069];
    private long[] vtd = new long[100069];
    private PriorityQueue<Pair> pq = new PriorityQueue<Pair>();
    private Triple[][] as = new Triple[2][100069];

    public void solve(InputReader in, PrintWriter out) {
      long i, k, l, w, sz, p;
      
      n = in.nextInt();
      sz = in.nextInt();

      for (i = 1; i <= n; i++) {
        a[(int) i] = in.nextInt();
        pr[(int) i] = i - 1;
      }

      for (i = 0; i < sz; i++) {
        k = in.nextInt();
        l = in.nextInt();
        w = in.nextInt();
        if (k + 1 == l) {
          p = k;
        } else if (k == 1 && l == n) {
          p = n;
        } else {
          p = 0;
        }
        if (p == 0) {
          m++;
          ed[(int) m] = new Triple(k, l, w);
        } else {
          a[(int) p] = Math.min(a[(int) p], w);
        }
      }

      for (i = 1; i <= n; i++) {
        k = i;
        l = i % n + 1;
        if (k > l) {
          long tmp = k;
          k = l;
          l = tmp;
        }
        m++;
        ed[(int) m] = new Triple(k, l, a[(int) i]);
      }

      for (i = 1; i <= m; i++) {
        ed[(int) i].first *= -1;
        long temp = ed[(int) i].second;
        ed[(int) i].second = ed[(int) i].first;
        ed[(int) i].first = temp;
      }
      Arrays.sort(ed, 1, (int) m + 1);
      for (i = 1; i <= m; i++) {
        long temp = ed[(int) i].second;
        ed[(int) i].second = ed[(int) i].first;
        ed[(int) i].first = temp;
        ed[(int) i].first *= -1;
      }
      
      sz = m;
      for (i = 1; i <= sz; i++) {
        k = ed[(int) i].first;
        l = ed[(int) i].second;
        if (k + 1 < l) {
          for (p = pr[(int) pr[(int) l]]; p != k; p = pr[(int) p]) {
            m++;
            ed[(int) m] = new Triple(p, l, ub);
          }
          pr[(int) l] = k;
        }
      }

      for (i = 1; i <= m; i++) {
        k = ed[(int) i].first;
        l = ed[(int) i].second;
        dg[(int) k]++;
        dg[(int) l]++;
      }
      for (i = 1; i <= n; i++) {
        od[(int) i + 1] = od[(int) i] + dg[(int) i];
        dg[(int) i] = 0;
      }

      dnc(1, m);
      out.println(z);
    }

    private void dnc(long lb, long rb) {
      long i, j, ii, k, l, w, mn = inf, e = 0;
      long[] p = new long[2];
      
      for (i = lb; i <= rb; i++) {
        k = ed[(int) i].first;
        l = ed[(int) i].second;
        w = ed[(int) i].third;
        for (ii = 0; ii < 2; ii++) {
          dg[(int) k]++;
          al[(int) od[(int) k] + (int) dg[(int) k]] = new Pair(l, w);
          if (vtd[(int) k] == 0) {
            vtd[(int) k] = 1;
            nn++;
            a[(int) nn] = k;
          }
          long temp = k;
          k = l;
          l = temp;
        }
      }
      
      Arrays.sort(a, 1, (int) nn + 1);

      for (i = 1;i <= nn; i++) {
        pst[(int) a[(int) i]] = i;
      }
      if (nn == 3) {
        for (i = 1; i <= nn; i++) {
          dij(0, a[(int) i]);
          for (j = i + 1; j <= nn; j++) {
            z = (z + nr[(int) 0][(int) a[(int) j]]) % dv;
          }
        }
      } else {
        for (i = lb; i <= rb; i++) {
          k = ed[(int) i].first;
          l = ed[(int) i].second;
          w = Math.max(pst[(int) l] - pst[(int) k] + 1, nn - (pst[(int) l] - pst[(int) k] - 1));
          if (w < mn) {
            mn = w;
            p[(int) 0] = k;
            p[(int) 1] = l;
          }
        }
        for (ii = 0; ii < 2; ii++) {
          dij(ii, p[(int) ii]);
          nm[(int) ii] = 0;
        }
        for (i = 1; i <= nn; i++) {
          if (a[(int) i] != p[(int) 0] && a[(int) i] != p[(int) 1]) {
            k = nr[(int) 0][(int) a[(int) i]];
            l = nr[(int) 1][(int) a[(int) i]];
            e = 0;
            if (i > pst[(int) p[(int) 0]] && i < pst[(int) p[(int) 1]]) {
              e = 1;
            }
            nm[(int) e]++;
            as[(int) e][(int) nm[(int) e]] = new Triple(k - l, k % dv,l % dv);
          }
        }
        Arrays.sort(as[(int) 0], 1, (int) nm[(int) 0] + 1);
        for (i = 1; i <= nm[(int) 0]; i++) {
          k = as[(int) 0][(int) i].second;
          l = as[(int) 0][(int) i].third;
          for (ii = 0;ii < 2; ii++) {
            ps[(int) ii][(int) i] = (ps[(int) ii][(int) i - 1] + k) % dv;
            long temp = k;
            k = l;
            l = temp;
          }
        }
        for (i = 1;i <= nm[(int) 1]; i++) {
          w = as[(int) 1][(int) i].first;
          k = as[(int) 1][(int) i].second;
          l = as[(int) 1][(int) i].third;
          
          int low = 1;
          int high = (int) nm[0] + 1;
          while (low < high) {
            int md = (low + high) / 2;
            if (as[0][md].first <= -w) {
              low = md + 1;
            } else {
              high = md;
            }
          }
          e = low - 1;
          
          z = (z + ps[(int) 0][(int) e]) % dv;
          z = (z + k * e % dv) % dv;
          z = (z + ps[(int) 1][(int) nm[(int) 0]]) % dv;
          z = (z + dv - ps[(int) 1][(int) e]) % dv;
          z = (z + l * (nm[(int) 0] - e) % dv) % dv;
        }
        z = (z + dv - nr[(int) 0][(int) p[(int) 1]] % dv) % dv;
      }
      for (i = 1; i <= nn; i++) {
        dg[(int) a[(int) i]] = 0;
        vtd[(int) a[(int) i]] = 0;
      }
      nn = 0;
      if (mn != inf) {
        for (ii = 0; ii < 2; ii++) {
          nm[(int) ii] = 0;
        }
        e = lb - 1;
        for (i = lb; i <= rb; i++) {
          k = ed[(int) i].first;
          l = ed[(int) i].second;
          w = ed[(int) i].third;
          if (pst[(int) k] < pst[(int) p[(int) 0]] || pst[(int) l] > pst[(int) p[(int) 1]]) {
            e++;
            Triple temp = ed[(int) i];
            ed[(int) i] = ed[(int) e];
            ed[(int) e] = temp;
          }
        }
        for (i = lb; i <= rb; i++) {
          k = ed[(int) i].first;
          l = ed[(int) i].second;
          w = ed[(int) i].third;
          if (k == p[(int) 0] && l == p[(int) 1]) {
            e++;
            Triple temp = ed[(int) i];
            ed[(int) i] = ed[(int) e];
            ed[(int) e] = temp;
            ed[(int) e].third = nr[(int) 0][(int) p[(int) 1]];
          }
        }
        w = nr[(int) 0][(int) p[(int) 1]];
        dnc(lb, e);
        ed[(int) e] = new Triple(p[(int) 0], p[(int) 1], w);
        dnc(e, rb);
      }
    }

    void dij(long ky, long x) {
      long i, k, l, w, ww;
      
      for (i = 1; i <= nn; i++) {
        nr[(int) ky][(int) a[(int) i]] = inf;
      }
      pq.add(new Pair(0,x));
      nr[(int) ky][(int) x] = 0;
      while(!pq.isEmpty()) {
        Pair top = pq.poll();
        w = top.first;
        k = top.second;
        if (w > nr[(int) ky][(int) k]) {
          continue;
        }
        for (i = 1; i <= dg[(int) k]; i++) {
          l = al[(int) od[(int) k] + (int) i].first;
          ww = al[(int) od[(int) k] + (int) i].second;
          if (w + ww < nr[(int) ky][(int) l]) {
            pq.add(new Pair(w + ww, l));
            nr[(int) ky][(int) l] = w + ww;
          }
        }
      }
    }
  }

  static class Pair implements Comparable<Pair> {
    long first;
    long second;
    
    Pair(long first, long second){
      this.first = first;
      this.second = second;
    }
    
    @Override
    public int compareTo(Pair other) {
      if (this.first != other.first) {
        return Long.compare(this.first, other.first);
      } else {
        return Long.compare(this.second, other.second);
      }
    }
  }


  static class Triple implements Comparable<Triple> {
    long first;
    long second;
    long third;
    
    Triple(long first, long second, long third){
      this.first = first;
      this.second = second;
      this.third = third;
    }

    @Override
    public int compareTo(Triple other) {
      if (this.first != other.first) {
        return Long.compare(this.first, other.first);
      } else if (this.second != other.second) {
        return Long.compare(this.second, other.second);
      } else {
        return Long.compare(this.third, other.third);
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
