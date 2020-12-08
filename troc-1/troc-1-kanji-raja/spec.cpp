#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> U, V;
  int ANS;

  void InputFormat() { 
    LINE(N);
    LINES(U, V) % SIZE(N-1); 
  }

  void OutputFormat() { LINE(ANS); }

  void Constraints() {
    CONS(9 <= N && N <= MAX_N);
    CONS(connected(N, U, V));
  }

  void Subtask1() {}

 private:
  bool eachElementBetween(vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [lo, hi](int x) {
      return lo <= x && x <= hi;
    });
  }

  bool connected(int n, vector<int> u, vector<int> v) {
    vector<int> adj[n+1];
    vector<bool> vis(n+1, 0);

    for(int i = 0 ; i < u.size() ; i++) {
      adj[u[i]].push_back(v[i]);
      adj[v[i]].push_back(u[i]);
    }

    function<void(int)> dfs = [&](int now) {
      if(vis[now]) return;
      vis[now] = true;

      for(int nex : adj[now]) {
        dfs(nex);
      }
    };

    dfs(1);
    return all_of(vis.begin() + 1, vis.end(), [](bool x) {
      return x;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});

    Input({"9",
           "1 2",
           "2 3",
           "4 5",
           "5 6",
           "7 8",
           "8 9",
           "2 5",
           "5 8"});
    
    Output({"1"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({"17",
           "1 2",
           "2 3",
           "4 5",
           "5 6",
           "7 8",
           "8 9",
           "2 5",
           "5 8",
           "10 11",
           "11 12",
           "13 9",
           "9 14",
           "15 16",
           "16 17",
           "11 9",
           "9 16"});
    
    Output({"10"});
  }

  void BeforeTestCase() {
    U.clear();
    V.clear();
  }

  void AfterTestCase() {
    renumber();
    reorder();
    swapEdge();
  }

  void TestGroup1() {
    Subtasks({1});
    
    CASE(brutalCase());

    for(int i = 0 ; i < 3 ; i++) {
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           pseudoStarGraph(N, 3, 3));
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           pseudoStarGraph(N, 3, 5));
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           pseudoStarGraph(N, 3, 10));
    }

    for(int i = 0 ; i < 3 ; i++) {
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           graphWithDegreeBetween(N, 3, 3));
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           graphWithDegreeBetween(N, 3, 5));
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           graphWithDegreeBetween(N, 3, 10));
    }

    for(int i = 0 ; i < 5 ; i++) {
      CASE(N = rnd.nextInt(9 * MAX_N / 10, MAX_N),
           randomTree(N));
    }
  }

 private:
  void brutalCase() {
    N = MAX_N;

    U = {1, 1, 1, 1};
    V = {2, 3, 4, 5};

    for(int i = 6 ; i <= N ; i++) {
      if(i & 1) {
        U.push_back(4);
        V.push_back(i);
      } else {
        U.push_back(5);
        V.push_back(i);
      }
    }
  }

  void randomTree(int n) {
    for(int i = 2 ; i <= n ; i++) {
      int par = rnd.nextInt(1, i-1);

      U.push_back(par);
      V.push_back(i);
    }
  }

  // 1 <= lowDeg <= hiDeg
  void pseudoStarGraph(int n, int lowDeg, int hiDeg) {
    int cur = 1;

    while(n - cur >= hiDeg) {
      int deg = rnd.nextInt(lowDeg, hiDeg);

      U.push_back(1);
      V.push_back(++cur);
      int pos = cur;

      for(int i = 2 ; i <= deg ; i++) {
        U.push_back(pos);
        V.push_back(++cur);
      }
    }

    while(cur < n) {
      U.push_back(rnd.nextInt(1, cur));
      V.push_back(++cur);
    }
  }

  void graphWithDegreeBetween(int n, int lowDeg, int hiDeg) {
    int cur = 1;

    while (n - cur >= hiDeg) {
      int deg = rnd.nextInt(lowDeg, hiDeg);

      U.push_back(rnd.nextInt(1, cur));
      V.push_back(++cur);
      int pos = cur;

      for (int i = 2; i <= deg; i++) {
        U.push_back(pos);
        V.push_back(++cur);
      }
    }

    while (cur < n) {
      U.push_back(rnd.nextInt(1, cur));
      V.push_back(++cur);
    }
  }

  void renumber() {
    vector<int> nums(N+1);
    iota(nums.begin(), nums.end(), 0);
    rnd.shuffle(nums.begin()+1, nums.end());

    for(int &x : U) x = nums[x];
    for(int &x : V) x = nums[x];
  }

  void reorder() {
    vector<int> nums(U.size());
    iota(nums.begin(), nums.end(), 0);
    rnd.shuffle(nums.begin(), nums.end());

    vector<int> copyU = U;
    vector<int> copyV = V;

    for(int i = 0 ; i < U.size() ; i++) {
      U[i] = copyU[nums[i]];
      V[i] = copyV[nums[i]];
    }
  }

  void swapEdge() {
    for(int i = 0 ; i < U.size() ; i++)
      if(rnd.nextInt(2))
        swap(U[i], V[i]);
  }
};
