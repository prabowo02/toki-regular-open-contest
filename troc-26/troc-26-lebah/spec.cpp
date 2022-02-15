#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, K, L;
  vector<int> A, B, C, D;
  long long ANSWER;

  void InputFormat() {
    LINE(K, L);
    LINE(N);
    LINES(A, B) % SIZE(N);
    LINE(M);
    LINES(C, D) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ANSWER);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX_NM);
    CONS(1 <= M && M <= MAX_NM);
    CONS(1 <= K && K <= MAX_VAL);
    CONS(1 <= L && L <= MAX_VAL);

    CONS(isEachElementBetween(A, 1, MAX_VAL));
    CONS(isEachElementOne(B));
    CONS(isEachElementBetween(C, 1, MAX_VAL));
    CONS(isEachElementBetween(D, 1, MAX_VAL));
  }

  void Subtask1() {
    Points(100);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

 private:
  const int MAX_NM = 1e5;
  const int MAX_VAL = 1e9;

  bool isEachElementBetween(const vector<int>& X, int lo, int hi) {
    for (int x : X) {
      if (x < lo || x > hi) {
        return false;
      }
    }
    return true;
  }

  bool isEachElementOne(const vector<int>& X) {
    for (int x : X) {
      if (x != -1 && x != 1) {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({ 1 });
    Input({
      "3 1",
      "2",
      "4 1",
      "10 -1",
      "2",
      "5 2",
      "8 1"
    });
    Output({
      "3"
    });
  }

  void SampleTestCase2() {
    Subtasks({ 1 });
    Input({
      "3 2",
      "2",
      "4 1",
      "10 -1",
      "2",
      "5 2",
      "10 1"
    });
    Output({
      "1"
    });
  }

  void SampleTestCase3() {
    Subtasks({ 1 });
    Input({
      "7 4",
      "2",
      "1 1",
      "7 -1",
      "3",
      "1 1",
      "5 2",
      "8 1",
    });
    Output({
      "-1"
    });
  }

  void BeforeTestCase() {
    A.clear();
    B.clear();
    C.clear();
    D.clear();
  }

  void AfterTestCase() {
    for (int i = 1; i < N; i++) {
      int j = rnd.nextInt(0, i);
      swap(A[i], A[j]);
      swap(B[i], B[j]);
    }
    for (int i = 1; i < M; i++) {
      int j = rnd.nextInt(0, i);
      swap(C[i], C[j]);
      swap(D[i], D[j]);
    }
  }

  void TestGroup1() {
    Subtasks({ 1 });

    // corner tests (5)
    CASE(N = 1, M = 1, K = 2, L = 1, A = { MAX_VAL }, B = { 1 }, C = { MAX_VAL }, D = { 1 });
    CASE(N = 1, M = 1, K = 2, L = 1, A = { 1 }, B = { -1 }, C = { 1 }, D = { 1 });
    CASE(N = 1, M = 1, K = 2, L = 1, A = { 2 }, B = { -1 }, C = { 1 }, D = { MAX_VAL });
    CASE(N = 1, M = 1, K = 2, L = 1, A = { MAX_VAL - 1 }, B = { 1 }, C = { MAX_VAL }, D = { MAX_VAL });
    CASE(N = 1, M = 1, K = MAX_VAL, L = MAX_VAL - 1, A = { MAX_VAL }, B = { -1 }, C = { 1 }, D = { MAX_VAL });
    // corner tests (impossible) (2)
    CASE(N = 1, M = 1, K = 2, L = 1, A = { 1 }, B = { -1 }, C = { 2 }, D = { 1 });
    CASE(N = 1, M = 1, K = 2, L = 1, A = { MAX_VAL - 2 }, B = { 1 }, C = { MAX_VAL }, D = { MAX_VAL });

    // maxtests (2)
    CASE(N = MAX_NM, M = MAX_NM, K = 1 + M, L = 1, beeRandom(50000, 1, MAX_VAL, 19999, 20000), flowerRandom(MAX_VAL, 0, -1));
    CASE(N = 19998, M = 9999, K = 10000, L = 1, beeRandom(9999, 1, MAX_VAL - 99999, 100000, 100000), flowerAntiGreedy(MAX_VAL, 0, -1));

    // L + M < K (2)
    CASE(N = 1, M = 1, K = 3, L = 1, A = { 1 }, B = { 1 }, C = { 2 }, D = { 1 });
    CASE(N = MAX_NM, M = MAX_NM, K = 2 + M, L = 1, beeRandom(32841, MAX_VAL / 10, MAX_VAL, 0, 100000), flowerRandom(1, 0, -1));

    // K <= L (2)
    CASE(N = 1, M = 1, K = 1, L = 1, A = { 2 }, B = { 1 }, C = { 1 }, D = { 1 });
    CASE(N = MAX_NM, M = MAX_NM, K = MAX_VAL - 999999, L = MAX_VAL - 1, beeRandom(40000, 1, MAX_VAL, 0, 1000000), flowerRandom(1, 0, -1));

    // large K and L, but K - L <= M (5)
    CASE(N = 2, M = 3, K = MAX_VAL / 2, L = K - 2, A = { MAX_VAL / 2, MAX_VAL / 2 }, B = { 1, -1 }, C = { 2, MAX_VAL - 1, 1 }, D = { 1, 1, 2 });
    CASE(N = 6, M = MAX_NM, K = MAX_VAL / 10, L = K - M, beeRandom(3, 1, MAX_VAL, 100000000, 400000000), flowerAntiGreedy(MAX_VAL, 9999, -1));
    CASE(N = 6, M = MAX_NM, K = MAX_VAL / 10, L = K - M, beeRandom(3, 1, MAX_VAL, 100000000, 400000000), flowerAntiGreedy(MAX_VAL, 9999, K - 1)); // -1
    CASE(N = 1000, M = MAX_NM, K = MAX_VAL / 1000, L = K - 42069, beeRandom(400, 1, MAX_VAL, 100000, 1000000), flowerRandom(MAX_VAL, 9009, -1));
    CASE(N = MAX_NM, M = MAX_NM, K = MAX_VAL, L = K - M, beeRandom(71920, 1, MAX_VAL, 0, 100000), flowerRandom(MAX_VAL, 8192, -1));

    // all same direction (B[i] == B[i+1]) (4)
    CASE(N = 25000, M = MAX_NM, K = 10000 + M, L = K - M, beeRandom(N, 1, 0, 10000, 500000), flowerAntiGreedy(MAX_VAL, 1, -1));
    CASE(N = MAX_NM, M = MAX_NM, K = 69420, L = 69, beeRandom(0, 0, MAX_VAL, 0, 100000), flowerRandom(MAX_VAL, 420, -1));
    CASE(N = MAX_NM, M = MAX_NM, K = 87678, L = 1, beeRandom(0, 0, MAX_VAL - 12312312, 0, 100000), flowerAntiGreedy(MAX_VAL, 6969, 71947));
    CASE(N = MAX_NM, M = MAX_NM, K = 69420, L = 1, beeRandom(N, 1213121, 0, 1000, 20000), flowerOnRange(10000, 1, 1213120, 1, 1000), flowerRandom(MAX_VAL, 8430, -1));

    // some flowers has same position as bees OR some flowers are impossible to reach (5)
    CASE(N = MAX_NM, M = MAX_NM, K = 2 * M, L = K - M, beeRandom(40404, 1, MAX_VAL, 0, 400000), flowerAtBee(1, MAX_VAL, MAX_VAL), flowerAntiGreedy(MAX_VAL - 1, 2134, -1, 1));
    CASE(N = MAX_NM, M = MAX_NM, K = 2 * M - 100, L = M, beeRandom(78109, MAX_VAL / 2 + 100, MAX_VAL / 2 - 100, 0, 400000),
         flowerOnRange(31, MAX_VAL / 2 - 99, MAX_VAL / 2 + 99, 1, 1000), flowerAtBee(69, MAX_VAL, MAX_VAL), flowerAntiGreedy(MAX_VAL - 1, 2134, -1));
    CASE(N = MAX_NM, M = MAX_NM, K = MAX_NM + 700, L = 900, beeRandom(50000, 1, MAX_VAL, 0, 300000), flowerAtBee(700, 100000, MAX_VAL), flowerAntiGreedy(MAX_VAL, 3819, -1, 100));
    CASE(N = MAX_NM, M = MAX_NM, K = MAX_NM, L = 500, beeRandom(42024, MAX_VAL / 2 + 1000000, MAX_VAL / 2 - 1000000, 0, 300000),
         flowerOnRange(501, MAX_VAL / 2 - 999999, MAX_VAL / 2 + 999999, 1, 1000), flowerAtBee(1000, 100000, MAX_VAL), flowerRandom(MAX_VAL, 3819, -1, 50)); // -1
    CASE(N = MAX_NM, M = MAX_NM, K = 6970, L = 6969, beeRandom(50505, MAX_VAL / 2 + 300000000, MAX_VAL / 2 - 300000000, 0, 150000),
         flowerOnRange(M - 1, MAX_VAL / 2 - 299999999, MAX_VAL / 2 + 299999999, 1, MAX_VAL / 2), flowerRandom(MAX_VAL, 0, -1));

    // random (12)
    for (int i = 1; i < 10000; i *= 20) {
      CASE(N = MAX_NM, M = MAX_NM, K = i + M, L = i, beeRandom(50001, i, MAX_VAL - i, 0, 200000), flowerAntiGreedy(MAX_VAL, 7777, -1));
      CASE(N = MAX_NM, M = MAX_NM, K = i + M, L = i, beeRandom(49999, i, MAX_VAL - i, 0, 200000), flowerRandom(MAX_VAL, 7777, -1));
      CASE(N = MAX_NM, M = MAX_NM, K = i + M, L = i, beeRandom(50000, i, MAX_VAL - i, 0, 200000), flowerRandom(MAX_VAL, 7777, K - i));
    }
  }

 private:
  const int MAX_NM = 1e5;
  const int MAX_VAL = 1e9;

  vector<pair<pair<int, int>, pair<int, int>>> range;

  // n0 bees have B[i] = 1. position of bees with B[i] = 1 is randomly generated starting from start0
  void beeRandom(int n0, int start0, int start1, int distBeeMin, int distBeeMax) {
    int n[2] = { n0, N - n0 };
    vector<vector<int>> ab(2);
    for (int t = 0; t < 2; t++) {
      for (int i = 0; i < n[t]; i++) {
        if (i == 0) {
          ab[t].push_back(t == 0 ? start0 : start1);
        } else {
          int dis = (t == 0 ? 1 : -1) * rnd.nextInt(distBeeMin, distBeeMax);
          ab[t].push_back(max(1, min(MAX_VAL, ab[t][i - 1] + dis)));
        }
        A.push_back(ab[t][i]);
        B.push_back(t == 0 ? 1 : -1);
      }
    }
    reverse(ab[1].begin(), ab[1].end());

    range.clear();
    for (int i = 0, j = 0; i < n[0]; i++) {
      while (j < n[1] && ab[1][j] <= ab[0][i]) j++;
      int left = ab[0][i];
      while (j < n[1]) {
        if (i + 1 < n[0] && ab[1][j] > ab[0][i + 1]) break;
        int right = (ab[0][i] + ab[1][j]) / 2;
        if (left < right) range.push_back({ {left - ab[0][i], right - ab[0][i]}, {ab[0][i], 0} });
        left = ab[1][j] + 1;
        j++;
      }
      if (i + 1 < n[0] && ab[0][i] < ab[0][i + 1]) {
        int right = ab[0][i + 1] - 1;
        if (j < n[1]) right = min(right, (ab[0][i] + ab[1][j]) / 2);
        if (left < right) range.push_back({ {left - ab[0][i], right - ab[0][i]}, {ab[0][i], 0} });
      }
    }
    for (int i = n[0] - 1, j = n[1] - 1; j >= 0; j--) {
      while (i >= 0 && ab[0][i] >= ab[1][j]) i--;
      int right = ab[1][j];
      while (i >= 0) {
        if (j > 0 && ab[0][i] < ab[1][j - 1]) break;
        int left = (ab[0][i] + ab[1][j] + 1) / 2;
        if (left < right) range.push_back({ {ab[1][j] - right, ab[1][j] - left}, {ab[1][j], 1} });
        right = ab[0][i] - 1;
        i--;
      }
      if (j > 0 && ab[1][j] != ab[1][j - 1]) {
        int left = ab[1][j - 1] + 1;
        if (i >= 0) left = max(left, (ab[0][i] + ab[1][j] + 1) / 2);
        if (left < right) range.push_back({ {ab[1][j] - right, ab[1][j] - left}, {ab[1][j], 1} });
      }
    }
    sort(range.begin(), range.end());
  }

  // generate flower so that sorting (energy, min_day) will fail
  // missing is used for generating impossible tc. pass missing = X where L <= X < K so that no flower has min_day equal to X. if missing = -1, then generate possible tc
  // the smallest generated flower distance is L + addL
  void flowerAntiGreedy(int energyStart, int energyDiff, int missing, int addL = 0) {
    int nr = range.size();
    set<int> act;
    priority_queue<pair<int, int>> pq;
    vector<int> p(nr), q(nr);
    for (int i = 0; i < nr; i++) p[i] = i;
    rnd.shuffle(p.begin(), p.end());
    for (int i = 0; i < nr; i++) q[p[i]] = i;

    int k = (missing < 0 ? K : missing);
    int i = 0;
    for (int l = L + addL; l < k && C.size() < M; l++) {
      while (i < range.size() && range[i].first.first <= l) {
        act.insert(p[i]);
        pq.push({ -range[i].first.second, p[i] });
        i++;
      }
      while (!pq.empty() && -pq.top().first < l) {
        act.erase(pq.top().second);
        pq.pop();
      }
      assert(!act.empty());
      auto it = act.lower_bound(rnd.nextInt(nr));
      int id = q[it != act.end() ? *it : * (--it)];
      if (range[id].second.second == 0) C.push_back(range[id].second.first + l);
      else C.push_back(range[id].second.first - l);
    }

    if (C.size() < M) {
      int distFlowerMin = k + (missing >= 0);
      while (i < range.size()) {
        act.insert(p[i]);
        pq.push({ -range[i].first.second, p[i] });
        i++;
      }
      while (!pq.empty() && -pq.top().first < distFlowerMin) {
        act.erase(pq.top().second);
        pq.pop();
      }
      assert(!act.empty());
      while (C.size() < M) {
        auto it = act.lower_bound(rnd.nextInt(nr));
        int id = q[it != act.end() ? *it : * (--it)];
        int left = max(distFlowerMin, range[id].first.first);
        if (range[id].second.second == 0) C.push_back(range[id].second.first + rnd.nextInt(left, range[id].first.second));
        else C.push_back(range[id].second.first - rnd.nextInt(left, range[id].first.second));
      }
    }

    while (D.size() < M) {
      if (D.empty()) D.push_back(energyStart);
      else D.push_back(max(1, D.back() - energyDiff));
    }
  }

  // missing is used for generating impossible tc. pass missing = X where L <= X < K so that no flower has min_day equal to X. if missing = -1, then generate possible tc
  // the smallest generated flower distance is L + addL
  void flowerRandom(int energyStart, int energyDiff, int missing, int addL = 0) {
    int k = (missing < 0 ? K : missing);
    for (int i = 0, l = L + addL; l < k && C.size() < M; l++) {
      while (i < range.size() && range[i].first.first <= l) i++;
      assert(i > 0);
      int id = rnd.nextInt(i);
      int right = min(l, range[id].first.second);
      if (range[id].second.second == 0) C.push_back(range[id].second.first + rnd.nextInt(range[id].first.first, right));
      else C.push_back(range[id].second.first - rnd.nextInt(range[id].first.first, right));
    }

    if (C.size() < M) {
      int distFlowerMin = (missing < 0 ? 0 : k + 1);
      vector<int> p;
      for (int i = 0; i < range.size(); i++) {
        if (distFlowerMin <= range[i].first.second) p.push_back(i);
      }
      assert(!p.empty());
      while (C.size() < M) {
        int id = p[rnd.nextInt(p.size())];
        int left = max(distFlowerMin, range[id].first.first);
        if (range[id].second.second == 0) C.push_back(range[id].second.first + rnd.nextInt(left, range[id].first.second));
        else C.push_back(range[id].second.first - rnd.nextInt(left, range[id].first.second));
      }
    }

    while (D.size() < M) {
      if (D.size() == addL) D.push_back(energyStart);
      else D.push_back(max(1, D.back() - energyDiff));
    }
  }

  // generate m flowers at a bee's position with energy [energyMin, energyMax]
  void flowerAtBee(int m, int energyMin, int energyMax) {
    for (int i = 0; i < m; i++) {
      int id = rnd.nextInt(range.size());
      C.push_back(range[id].second.first);
      D.push_back(rnd.nextInt(energyMin, energyMax));
    }
  }

  // randomly generate m flowers on [left, right] with energy [energyMin, energyMax]
  void flowerOnRange(int m, int left, int right, int energyMin, int energyMax) {
    for (int i = 0; i < m; i++) {
      C.push_back(rnd.nextInt(left, right));
      D.push_back(rnd.nextInt(energyMin, energyMax));
    }
  }
};