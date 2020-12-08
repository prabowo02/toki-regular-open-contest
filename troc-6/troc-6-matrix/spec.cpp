#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MIN_N = 20;
const int MAX_N = 500;
const int MIN_VAL = 1;
const int MAX_VAL = 1000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<vector<int>> C;
  int ANS;

  void InputFormat() {
    LINE(N);
    GRID(C) % SIZE(N, N);
  }

  void OutputFormat() { LINE(ANS); }

  // there is valid A and B can be derived from the tc construction
  // since we can't put A and B here..
  void Constraints() {
    CONS(MIN_N <= N && N <= MAX_N);
    CONS(eachElementsBetween(C, -1, MAX_VAL * MAX_VAL));
    CONS(C[N-1][N-1] == -1);
    CONS(countElement(C, 0) == 0);
    CONS(countElement(C, -1) == 1);
  }

  void Subtask1() {
  }

 private:
  bool eachElementsBetween(vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](int x) {
      return lo <= x && x <= hi;
    });
  }

  bool eachElementsBetween(vector<vector<int>> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](vector<int> x) {
      return eachElementsBetween(x, lo, hi);
    });
  }

  int countElement(vector<vector<int>> &v, int x) {
    int ret = 0;
    for (vector<int> row : v) {
      ret += count(row.begin(), row.end(), x);
    }
    return ret;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});

    Input({
      "20", 
      "2 2 2 2 2 2 1 1 1 1 1 1 1 1 3 3 3 3 3 3",
      "2 2 2 2 2 2 1 1 1 1 1 1 1 1 3 3 3 3 3 3",
      "2 2 2 2 2 2 1 1 1 1 1 1 1 1 3 3 3 3 3 3",
      "2 2 2 2 2 2 1 1 1 1 1 1 1 1 3 3 3 3 3 3",
      "2 2 2 2 2 2 1 1 1 1 1 1 1 1 3 3 3 3 3 3",
      "2 2 2 2 2 6 1 1 1 1 1 1 1 1 6 3 3 3 3 3",
      "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
      "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
      "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
      "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
      "4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4",
      "1 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4 1",
      "1 1 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4 1 1",
      "1 1 1 4 1 1 1 1 1 1 1 1 1 1 1 1 4 1 1 1",
      "1 1 1 1 4 1 1 1 1 1 1 1 1 1 1 4 1 1 1 1",
      "1 1 1 1 1 4 1 1 1 1 1 1 1 1 4 1 1 1 1 1",
      "1 1 1 1 1 1 4 1 1 1 1 1 1 4 1 1 1 1 1 1",
      "1 1 1 1 1 1 1 4 1 1 1 1 4 1 1 1 1 1 1 1",
      "1 1 1 1 1 1 1 1 4 1 1 4 1 1 1 1 1 1 1 1",
      "4 1 1 1 1 1 1 1 1 8 9 1 1 1 1 1 1 1 1 -1"
    });

    Output({"12"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({
      "20",
      "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20",
      "2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40",
      "3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60",
      "4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80",
      "5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100",
      "6 12 18 24 30 36 42 48 54 60 66 72 78 84 90 96 102 108 114 120",
      "7 14 21 28 35 42 49 56 63 70 77 84 91 98 105 112 119 126 133 140",
      "8 16 24 32 40 48 56 64 72 80 88 96 104 112 120 128 136 144 152 160",
      "9 18 27 36 45 54 63 72 81 90 99 108 117 126 135 144 153 162 171 180",
      "10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200",
      "11 22 33 44 55 66 77 88 99 110 121 132 143 154 165 176 187 198 209 220",
      "12 24 36 48 60 72 84 96 108 120 132 144 156 168 180 192 204 216 228 240",
      "13 26 39 52 65 78 91 104 117 130 143 156 169 182 195 208 221 234 247 260",
      "14 28 42 56 70 84 98 112 126 140 154 168 182 196 210 224 238 252 266 280",
      "15 30 45 60 75 90 105 120 135 150 165 180 195 210 225 240 255 270 285 300",
      "16 32 48 64 80 96 112 128 144 160 176 192 208 224 240 256 272 288 304 320",
      "17 34 51 68 85 102 119 136 153 170 187 204 221 238 255 272 289 306 323 340",
      "18 36 54 72 90 108 126 144 162 180 198 216 234 252 270 288 306 324 342 360",
      "19 38 57 76 95 114 133 152 171 190 209 228 247 266 285 304 323 342 361 380",
      "20 40 60 80 100 120 140 160 180 200 220 240 260 280 300 320 340 360 380 -1",
    });

    Output({"400"});
  }

  void AfterTestCase() {
    rnd.shuffle(tempC.begin(), tempC.end());

    for (int i = 0 ; i < tempC.size() ; i++) {
      if (tempC[i] == -1) {
        swap(tempC[i], tempC[tempC.size()-1]);
        break;
      }
    }

    C.clear();
    C.resize(N);
    for (int i = 0 ; i < N ; i++) {
      C[i].resize(N);
      for (int j = 0 ; j < N ; j++)
        C[i][j] = tempC[i * N + j];
    }
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = MAX_N, 
         A = randomArray(N, MIN_VAL, MAX_VAL), 
         B = randomArray(N, MIN_VAL, MAX_VAL),
         tempC = arrayMultiplication(A, B),
         removeRandom(tempC));
    
    vector<function<void(vector<int>&)>> removeMethods = {
      removeRandom, removeMinimum, removeMaximum
    };
    vector<function<void(vector<int>&, int)>> modifierMethods = {
      distortValue, duplicateValue, changeToOne
    };

    for (int i = 0 ; i < 2 ; i++) {
      for (auto remover : removeMethods) {
        // all 1 A B
        CASE(N = rnd.nextInt(MIN_N, MAX_N),
             A = randomArray(N, 1, 1),
             B = randomArray(N, 1, 1),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
        // all 1 A, random B
        CASE(N = rnd.nextInt(MIN_N, MAX_N),
             A = randomArray(N, 1, 1),
             B = randomArray(N, 1, MAX_VAL),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
        // 2^i A, B
        CASE(N = rnd.nextInt(MIN_N, MAX_N),
             A = generatePowerOf(N, {2}),
             B = generatePowerOf(N, {2}),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
        // 2^i3^j A, B
        CASE(N = rnd.nextInt(MIN_N, MAX_N),
             A = generatePowerOf(N, {2, 3}),
             B = generatePowerOf(N, {2, 3}),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
        // primes duplicate A, B
        CASE(N = rnd.nextInt(MIN_N, MAX_N),
             A = generatePrimes(N, true),
             B = generatePrimes(N, true),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
        // primes unique A, B (there is 168 primes < 1000)
        CASE(N = rnd.nextInt(MIN_N, 168),
             A = generatePrimes(N, false),
             B = generatePrimes(N, false),
             tempC = arrayMultiplication(A, B),
             remover(tempC));
      }
    }

    vector<int> nValues = {20, 50, 269, 451, 500};
    for (auto remover : removeMethods) {
      for (int n : nValues) {
        vector<int> steps = {0, 0, 0, 5, 10, 20, 50, n / 3};

        for (int tc = 0 ; tc < 2 ; tc++) {
          A = randomArray(n, MIN_VAL, MAX_VAL);
          B = randomArray(n, MIN_VAL, MAX_VAL);

          for (auto modifier : modifierMethods) {
            modifier(A, steps[rnd.nextInt(steps.size())]);
            modifier(B, steps[rnd.nextInt(steps.size())]);
          }

          vector<int> c = arrayMultiplication(A, B);
          remover(c);

          CASE(N = n, tempC = c);
        }
      }
      
      CASE(N = rnd.nextInt(MIN_N, MAX_N),
           A = randomArray(N, MIN_VAL, MAX_VAL),
           B = randomArray(N, MIN_VAL, MAX_VAL),
           tempC = arrayMultiplication(A, B),
           remover(tempC));
      CASE(N = rnd.nextInt(MIN_N, MAX_N),
           A = randomArray(N, MIN_VAL, MAX_VAL),
           B = randomArray(N, MIN_VAL, MAX_VAL),
           duplicateValue(A, rnd.nextInt(20)),
           duplicateValue(B, rnd.nextInt(20)),
           tempC = arrayMultiplication(A, B),
           remover(tempC));
    }

    for (auto remover : removeMethods) {
      CASE(N = MAX_N,
           A = generateLargePrimes(N, rnd.nextInt(1, 3)),
           B = generateLargePrimes(N, rnd.nextInt(1, 3)),
           tempC = arrayMultiplication(A, B),
           remover(tempC));
      CASE(N = MAX_N-1,
           A = generateLargePrimes(N, rnd.nextInt(1, 5)),
           B = generateLargePrimes(N, rnd.nextInt(1, 5)),
           tempC = arrayMultiplication(A, B),
           remover(tempC));
    }
    
    CASE(N = MAX_N,
         A = generateLargePrimes(N, rnd.nextInt(1, 1)),
         B = generateLargePrimes(N, rnd.nextInt(1, 1)),
         tempC = arrayMultiplication(A, B),
         removeRandom(tempC));
      
    CASE(N = MAX_N,
         A = generateLargePrimes(N, rnd.nextInt(1, 2)),
         B = generateLargePrimes(N, rnd.nextInt(1, 2)),
         tempC = arrayMultiplication(A, B),
         removeRandom(tempC));
  }

 private:
  vector<int> A, B;
  vector<int> tempC;

  vector<int> randomArray(int n, int lo, int hi) {
    vector<int> ret(n);
    for (int &x : ret) x = rnd.nextInt(lo, hi);
    return ret;
  }

  vector<int> arrayMultiplication(vector<int> &a, vector<int> &b) {
    vector<int> ret;
    for (int x : a)
      for (int y : b)
        ret.push_back(x * y);
    return ret;
  }

  function<void(vector<int>&)> removeRandom = [&](vector<int> &c) {
    int idx = rnd.nextInt(c.size());
    c[idx] = -1;
  };

  function<void(vector<int>&)> removeMinimum = [&](vector<int> &c) {
    int mins = *min_element(c.begin(), c.end());
    for (int &x : c) {
      if (x == mins) {
        x = -1;
        break;
      }
    }
  };

  function<void(vector<int>&)> removeMaximum = [&](vector<int> &c) {
    int maks = *max_element(c.begin(), c.end());
    for (int &x : c) {
      if (x == maks) {
        x = -1;
        break;
      }
    }
  };

  function<void(vector<int>&, int)> duplicateValue = [&](vector<int> &v, int step) {
    for (int i = 0 ; i < step ; i++) {
      int a = rnd.nextInt(v.size());
      int b = rnd.nextInt(v.size());
      
      v[b] = v[a];
    }
  };

  function<void(vector<int>&, int)> distortValue = [&](vector<int> &v, int step) {
    for (int i = 0 ; i < step ; i++) {
      int a = rnd.nextInt(v.size());
      v[a] = rnd.nextInt(MIN_VAL, MAX_VAL);
    }
  };

  function<void(vector<int>&, int)> changeToOne = [&](vector<int> &v, int step) {
    for (int i = 0 ; i < step ; i++) {
      int a = rnd.nextInt(v.size());
      v[a] = 1;
    }
  };

  vector<int> generatePowerOf(vector<int> primes) {
    vector<int> ret;
    for (int i = 1 ; i <= MAX_VAL ; i++) {
      int x = i;
      for (int prime : primes) {
        while (x % prime == 0) {
          x /= prime;
        }
      }
      if (x == 1) {
        ret.push_back(i);
      }
    }

    return ret;
  }

  vector<int> generatePowerOf(int n, vector<int> primes) {
    vector<int> ret(n);
    vector<int> powerOf = generatePowerOf(primes);
    for (int &x : ret) {
      x = powerOf[rnd.nextInt(powerOf.size())];
    }
    return ret;
  }

  vector<int> generatePrimes() {
    vector<int> ret;
    
    for (int i = 2 ; i <= MAX_VAL ; i++) {
      bool ok = true;
      for (int j = 2 ; j * j <= i ; j++)
        ok &= (i % j != 0);
      if (ok)
        ret.push_back(i);
    }
    
    return ret;
  }

  vector<int> generateLargePrimes(int n, int lim) {
    vector<int> primes = generatePrimes();
    vector<int> ret;

    reverse(primes.begin(), primes.end());
    primes.resize(lim);

    for (int i = 0 ; i < n ; i++) {
      ret.push_back(primes[rnd.nextInt(lim)]);
    }

    return ret;
  }

  vector<int> generatePrimes(int n, bool mayDuplicate) {
    vector<int> primes = generatePrimes();
    vector<int> ret;

    assert(mayDuplicate || primes.size() >= n);
    
    if (mayDuplicate) {
      for (int i = 0 ; i < n ; i++) {
        ret.push_back(primes[rnd.nextInt(primes.size())]);
      }
    } else {
      rnd.shuffle(primes.begin(), primes.end());
      primes.resize(n);

      ret = primes;
    }

    return ret;
  }
};
