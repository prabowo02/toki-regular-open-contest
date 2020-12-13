#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXM = 1000000000;
const int MAXT = 7;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, T, K;
  string F, S;

  int ans;

  void InputFormat() {
    LINE(N, M, T, K);
    LINE(F);
    LINE(S);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(4);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXM);
    CONS(1 <= T && T <= MAXT);
    CONS(1 <= K && K <= N);
    CONS(F.size() == N);
    CONS(all_of(F.begin(), F.end(), [&](char c) { return 'A' <= c && c < 'A' + T; }));
    CONS(S.size() == K);
    CONS(all_of(S.begin(), S.end(), [&](char c) { return 'A' <= c && c < 'A' + T; }));
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "6 7 7 5",
      "EADGBE",
      "ABCDF",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase2() {
    Input({
      "4 3 1 4",
      "AAAA",
      "AAAA",
    });
    Output({
      "81",
    });
  }

  void SampleTestCase3() {
    Input({
      "5 2 6 1",
      "DEEDE",
      "A",
    });
    Output({
      "0",
    });
  }

  void TestGroup1() {

    // Small answers
    CASE(N = 1; M = MAXM; K = 1; T = rnd.nextInt(1, MAXT); F = randomString(N, T); S = randomString(K, T));
    CASE(N = MAXN; M = MAXT; K = rnd.nextInt(1, N); T = MAXT; F = periodicString(N, T); S = periodicString(K, T));
    CASE(N = MAXN; M = T = rnd.nextInt(1, T); K = rnd.nextInt(1, N); F = sameString(N, 'B'); S = sameString(K, 'A'));
    CASE(N = MAXN; M = 1; T = MAXT; K = sqrt(N) * (T/2); F = longPeriodicString(N, sqrt(N), T); S = longPeriodicString(K, sqrt(N), T));
    CASE(N = MAXN; M = 1; K = 1; T = MAXT; F = randomString(N, T); S = randomString(K, T));

    // some largest possible ans
    CASE(N = MAXN; M = MAXM; K = 1; T = 1; F = sameString(N, 'A'); S = "A");
    CASE(N = MAXN; M = MAXM; K = N; T = 1; F = sameString(N, 'A'); S = sameString(K, 'A'));
    CASE(N = MAXN; M = MAXM; K = N/2; T = 1; F = sameString(N, 'A'); S = sameString(K, 'A'));

    // T | M
    CASE(N = MAXN; M = MAXM; K = rnd.nextInt(1, N); T = 2; F = randomString(N, T); S = randomString(K, T));
    CASE(N = MAXN; M = MAXM; K = rnd.nextInt(1, N); T = 5; F = randomString(N, T); S = randomString(K, T));

    // totally random
    CASE(N = sqrt(MAXN); M = MAXM; K = N/2; T = MAXT; F = randomString(N, T); S = randomString(K, T));
    CASE(N = rnd.nextInt(1, MAXN); M = rnd.nextInt(1, MAXM); K = rnd.nextInt(1, N); T = rnd.nextInt(1, T); F = randomString(N, T); S = randomString(K, T));

    // Some extreme cases
    CASE(N = MAXN; M = MAXM; K = rnd.nextInt(1, N); T = MAXT; F = periodicString(N, T); S = periodicString(K, T));
    CASE(N = MAXN; M = MAXM; K = N/2; T = MAXT; F = randomString(N, T); S = randomString(K, T));
    CASE(N = MAXN; M = MAXM - MAXM % T - 1; K = N; T = MAXT; F = randomString(N, T); S = randomString(K, T));

    // Ensure all possible values of T
    CASE(N = rnd.nextInt(1, MAXN); M = rnd.nextInt(1, MAXM); K = rnd.nextInt(1, N); T = 3; F = randomString(N, T); S = randomString(K, T));
    CASE(N = rnd.nextInt(1, MAXN); M = rnd.nextInt(1, MAXM); K = rnd.nextInt(1, N); T = 4; F = randomString(N, T); S = randomString(K, T));
    CASE(N = rnd.nextInt(1, MAXN); M = rnd.nextInt(1, MAXM); K = rnd.nextInt(1, N); T = 6; F = randomString(N, T); S = randomString(K, T));

    // Long periodic strings
    CASE(N = MAXN; M = MAXM; K = 20; T = MAXT; F = longPeriodicString(N, 2, T); S = longPeriodicString(K, 2, T));
    CASE(N = MAXN; M = MAXM; K = 30; T = MAXT; F = longPeriodicString(N, 3, T); S = longPeriodicString(K, 3, T));
    CASE(N = MAXN; M = MAXM; K = 50; T = MAXT; F = longPeriodicString(N, 5, T); S = longPeriodicString(K, 5, T));

    // 0 answer
    CASE(N = MAXN; M = MAXT - 1; K = N/2; T = MAXT; F = sameString(N, 'B'); S = sameString(K, 'A'));
  }

  string randomString(int n, int t) {
    string s;
    for (int i = 0; i < n; ++i) {
      s += 'A' + rnd.nextInt(t);
    }
    return s;
  }

  // len = 3, t = 4: 'AAABBBCCCDDDAAABBB...'
  string longPeriodicString(int n, int len, int t) {
    int cur = rnd.nextInt(t), cnt = 0;
    string s;
    for (int i = 0; i < n; ++i) {
      s += 'A' + cur;
      if (++cnt >= len) {
        cnt = 0;
        if (++cur >= t) cur -= t;
      }
    }
    return s;
  }

  // 'ABCDEABCDE...'
  string periodicString(int n, int t) {
    return longPeriodicString(n, 1, t);
  }

  string sameString(int n, char c) {
    string s;
    for (int i = 0; i < n; ++i) {
      s += c;
    }
    return s;
  }
};
