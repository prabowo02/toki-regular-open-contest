#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

const int ADD = 2019;
const int MUL = 2020;
const int EXP = 2021;

int power(int x, int y, int mod=MOD) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % mod;
    x = 1LL * x * x % mod;
  }

  return ret;
}

bool add(int &num) {
  num += ADD;
  if (num < MOD) return false;

  num -= MOD;
  return true;
}

bool mul(int &num) {
  long long res = 1LL * num * MUL;
  if (res < MOD) {
    num = res;
    return false;
  }

  num = res % MOD;
  return true;
}

bool expo(int &num) {
  if (num <= 1) return false;

  num = power(num, EXP);
  return true;
}

bool iadd(int &num) {
  num -= ADD;
  if (num >= 0) return false;

  num += MOD;
  return true;
}

const int IMUL = power(MUL, MOD-2);
bool imul(int &num) {
  if (num % MUL == 0) {
    num /= MUL;
    return false;
  }

  num = 1LL * num * IMUL % MOD;
  return true;
}

const int IEXP = power(EXP, MOD/2 - 2, MOD-1);
bool iexpo(int &num) {
  if (num <= 1) return false;

  num = power(num, IEXP);
  return true;
}

const int MAX_STEP = 13;
vector<pair<int, bool>> dist[MAX_STEP];
vector<tuple<int, bool, int>> bfs(int val, vector<function<bool(int&)>> operations) {
  for (int i = 0; i < MAX_STEP; ++i) dist[i].clear();

  vector<tuple<int, bool, int>> ret;
  dist[0].emplace_back(val, false);

  for (int i = 0; i < MAX_STEP; ++i) {
    sort(dist[i].begin(), dist[i].end());
    dist[i].resize(unique(dist[i].begin(), dist[i].end()) - dist[i].begin());

    for (pair<int, bool> &p: dist[i]) {
      int num; bool used_modulo;
      tie(num, used_modulo) = p;

      ret.emplace_back(num, used_modulo, i);
      if (i + 1 < MAX_STEP) {
        for (auto &op: operations) {
          int nxt = num;
          bool require_modulo = op(nxt);

          dist[i+1].emplace_back(nxt, used_modulo || require_modulo);
        }
      }
    }
  }

  return ret;
}

int main() {
  int a, b;
  scanf("%d %d", &a, &b);

  vector<tuple<int, bool, int>> 
    bfsA = bfs(a, {add, mul, expo}),
    bfsB = bfs(b, {iadd, imul, iexpo});

  sort(bfsA.begin(), bfsA.end());

  int ans = 100;
  for (tuple<int, bool, int> &t: bfsB) {
    int num, step; bool used_modulo;
    tie(num, used_modulo, step) = t;

    auto it = lower_bound(bfsA.begin(), bfsA.end(), make_tuple(num, false, -1));
    if (it != bfsA.end() && get<0>(*it) == num) {
      ans = min(ans, step + get<2>(*it) + (used_modulo || get<1>(*it)));
    }
  }

  printf("%d\n", ans);
  return 0;
}
