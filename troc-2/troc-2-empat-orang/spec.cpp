#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  long long ans;
  vector<int> C[4], W[4], S, T;

  void InputFormat() {
    LINE(N);
    for (int i = 0; i < 4; i++) {
      LINE(C[i] % SIZE(N));
      LINE(W[i] % SIZE(N));
    }
    LINES(S, T) % SIZE(4);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= 20000);
    for (int i = 0; i < 4; i++) {
      CONS(between(C[i], 1, 1000000));
      CONS(between(W[i], 1, 1000000));
    }
    CONS(between(S, 1, N));
    CONS(between(T, 1, N));
  }

  bool between(vector<int> A, int l, int r) {
    for (auto it : A) if (it < l || r < it) return false;
    return true;
  }

  void Subtask1() {
    Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3",
      "10 20 1",
      "2 5 3",
      "10 20 2",
      "2 5 3",
      "10 20 3",
      "2 5 3",
      "10 20 4",
      "2 5 3",
      "1 2",
      "3 1",
      "2 1",
      "2 2"
    });
    Output({
      "49"
    });
  }

  void TestGroup1() {
    Subtasks({1});

    // small
    for (int i = 1; i <= 10; i++) {
      CASE(N = i,
        complete_random(0),
        complete_random(1),
        complete_random(2),
        complete_random(3)
      );
    }
    CASE(N = 500,
      nginep_mahal_semua(0, N - 3),
      nginep_mahal_semua(1, N - 3),
      nginep_murah_tidak_direct(2),
      nginep_murah_tidak_direct(3)
    );
    CASE(N = 499,
      nginep_murah_direct(0, 0),
      nginep_murah_direct(1, N - 2),
      nginep_murah_direct(2, 4),
      nginep_murah_direct(3, 250)
    );
    CASE(N = 10,
      nginep_murah_tidak_direct(0),
      nginep_murah_tidak_direct(1),
      nginep_murah_tidak_direct(2),
      nginep_murah_tidak_direct(3)
    );
    CASE(N = 498,
      nginep_murah_direct(0, 0),
      nginep_murah_tidak_direct(1, N - 100, N - 1),
      nginep_mahal_semua(2, 4),
      nginep_murah_direct(3, 250)
    );
    CASE(N = 500,
      nginep_murah_direct(0, 200),
      nginep_murah_tidak_direct(1, N - 5, N - 3),
      nginep_mahal_semua(2, 300),
      nginep_murah_direct(3, 250)
    );
    CASE(N = 500,
      nginep_mahal_semua(0, 250),
      nginep_murah_tidak_direct(1, N - 5, N - 3),
      nginep_mahal_semua(2, 0),
      nginep_murah_tidak_direct(3, N / 2, N - 100)
    );
    CASE(N = 500,
      nginep_mahal_semua(0, 0),
      nginep_mahal_semua(1, 125),
      nginep_mahal_semua(2, 250),
      nginep_mahal_semua(3, 375)
    );
    CASE(N = 500,
      nginep_murah_direct(0, 5),
      nginep_murah_direct(1, 10),
      nginep_murah_direct(2, 15),
      nginep_murah_direct(3, 20)
    );
    CASE(N = 500,
      complete_random(0, 499, 5, 1000),
      complete_random(1, 200),
      complete_random(2, 300),
      complete_random(3, 498)
    );
    CASE(N = 500,
      nginep_murah_tidak_direct(0, N - 5, N - 3),
      nginep_murah_tidak_direct(1, N / 2, N - 200),
      complete_random(2, 400),
      complete_random(3, 100)
    );
    CASE(N = 500,
      complete_random(0, 400),
      complete_random(1, 250, 1000000, 1000000),
      nginep_murah_direct(2, 400),
      nginep_murah_tidak_direct(3, N / 4, N / 2)
    );
    CASE(N = 500,
      complete_random(0, 69),
      complete_random(1, 250, 25, 50),
      nginep_mahal_semua(2, 389),
      nginep_mahal_semua(3, 1)
    );
    for (int it = 0; it < 5; it++) {
      CASE(N = 500,
        complete_random(0),
        complete_random(1),
        complete_random(2),
        complete_random(3)
      );
    }

    // big
    CASE(N = 20000,
      nginep_mahal_semua(0, N - 3),
      nginep_mahal_semua(1, N - 3),
      nginep_murah_tidak_direct(2),
      nginep_murah_tidak_direct(3)
    );
    CASE(N = 20000,
      nginep_murah_direct(0, 0),
      nginep_murah_direct(1, N - 2),
      nginep_murah_direct(2, 100),
      nginep_murah_direct(3, 5000)
    );
    CASE(N = 20000,
      nginep_murah_tidak_direct(0),
      nginep_murah_tidak_direct(1),
      nginep_murah_tidak_direct(2),
      nginep_murah_tidak_direct(3)
    );
    CASE(N = 5000,
      nginep_murah_direct(0, 0),
      nginep_murah_tidak_direct(1, N - 100, N - 1),
      nginep_mahal_semua(2, 169),
      nginep_murah_direct(3, 1250)
    );
    CASE(N = 10000,
      nginep_murah_direct(0, 2000),
      nginep_murah_tidak_direct(1, N - 50, N - 30),
      nginep_mahal_semua(2, 3000),
      nginep_murah_direct(3, 2500)
    );
    CASE(N = 5000,
      nginep_mahal_semua(0, 2500),
      nginep_murah_tidak_direct(1, N - 50, N - 30),
      nginep_mahal_semua(2, 0),
      nginep_murah_tidak_direct(3, N / 2, N - 1000)
    );
    CASE(N = 5000,
      nginep_mahal_semua(0, 0),
      nginep_mahal_semua(1, 1250),
      nginep_mahal_semua(2, 2500),
      nginep_mahal_semua(3, 3750)
    );
    CASE(N = 5000,
      nginep_murah_direct(0, 50),
      nginep_murah_direct(1, 100),
      nginep_murah_direct(2, 150),
      nginep_murah_direct(3, 200)
    );
    CASE(N = 5000,
      complete_random(0, 499, 5, 10000),
      complete_random(1, 2000),
      complete_random(2, 3000),
      complete_random(3, 4980)
    );
    CASE(N = 5000,
      nginep_murah_tidak_direct(0, N - 50, N - 30),
      nginep_murah_tidak_direct(1, N / 2, N - 2000),
      complete_random(2, 4000),
      complete_random(3, 1000)
    );
    CASE(N = 5000,
      complete_random(0, 4000),
      complete_random(1, 250, 1000000, 1000000),
      nginep_murah_direct(2, 4000),
      nginep_murah_tidak_direct(3, N / 4, N / 2)
    );
    CASE(N = 5000,
      complete_random(0, 690),
      complete_random(1, 2500, 250, 500),
      nginep_mahal_semua(2, 3890),
      nginep_mahal_semua(3, 10)
    );
    CASE(N = 20000,
      complete_random(0, 1250, 999900, 1000000),
      complete_random(1, 2500, 999900, 1000000),
      complete_random(2, 0, 999900, 1000000),
      complete_random(3, 3750, 999900, 1000000)
    );
    for (int it = 0; it < 5; it++) {
      CASE(N = 20000,
        complete_random(0),
        complete_random(1),
        complete_random(2),
        complete_random(3)
      );
    }
  }

  void init(int N) {
    if (S.size() != 4) S.resize(4);
    if (T.size() != 4) T.resize(4);
    for (int i = 0; i < 4; i++) {
      C[i].resize(N);
      W[i].resize(N);
    }
  }

  void nginep_murah_direct(int id, int delta) {
    init(N);

    S[id] = random(0, N - 1);
    T[id] = (S[id] + delta) % N;

    for (int i = 0; i < N; i++) {
      C[id][i] = random(1, 1000);
      W[id][i] = random(1, 1000);
    }

    S[id]++;
    T[id]++;
  }

  void nginep_murah_tidak_direct(int id) {
    nginep_murah_tidak_direct(id, N - 2, N - 1);
  }

  void nginep_murah_tidak_direct(int id, int delta, int at_murah) {
    init(N);

    S[id] = random(0, N - 1);
    T[id] = (S[id] + delta) % N;
    int at = (S[id] + at_murah) % N;

    for (int i = 0; i < N; i++) {
      C[id][i] = random(999000, 1000000);
      W[id][i] = random(1, 1000);
    }
    C[id][at] = random(1, 1000);

    S[id]++;
    T[id]++;
  }

  void nginep_mahal_semua(int id, int delta) {
    init(N);
    S[id] = random(0, N - 1);
    T[id] = (S[id] + delta) % N;

    for (int i = 0; i < N; i++) {
      C[id][i] = random(999000, 1000000);
      W[id][i] = random(1, 10);
    }

    S[id]++;
    T[id]++;
  }

  void complete_random(int id) {
    complete_random(id, random(0, N - 1));
  }

  void complete_random(int id, int delta) {
    complete_random(id, delta, 1, 1000000);
  }

  void complete_random(int id, int delta, int L, int R) {
    init(N);

    S[id] = random(0, N - 1);
    T[id] = (S[id] + delta) % N;
    for (int i = 0; i < N; i++) {
      C[id][i] = random(L, R);
      W[id][i] = random(L, R);
    }
    S[id]++;
    T[id]++;
  }

  int random(int l, int r) {
    return rnd.nextInt(l, r);
  }

};
