#include <bits/stdc++.h>

using namespace std;

const int N = 2048;

int n, p, t, v, d;
int x[N], h[N];

int main() {
  scanf("%d %d %d %d %d", &n, &p, &t, &v, &d);
  for (int i = 0; i < n; ++i)
    scanf("%d", x+i);
  for (int i = 0; i < n; ++i)
    scanf("%d", h+i);
  vector<int> vx;
  for (int i = 0; i < n; ++i) {
    vx.push_back(x[i]);
    vx.push_back(x[i]+p);
  }
  sort(vx.begin(), vx.end());
  vx.erase(unique(vx.begin(), vx.end()), vx.end());
  vector<tuple<int, int, int> > range;
  for (int i = 0; i + 1 < vx.size(); ++i) {
    range.emplace_back(vx[i], vx[i+1], t);
  }
  for (int i = 0; i < n; ++i) {
    int start = x[i], finish = x[i] + p;
    for (auto & it : range) {
      if (start <= get<0>(it) && get<1>(it) <= finish)
        get<2>(it) = min(get<2>(it), h[i]);
    }
  }
  double cost = 0;
  for (auto it : range) {
    int start, finish, height;
    tie(start, finish, height) = it;
    double time = (double)(finish - start) / v;
    cost += d * (t - height) * time;
  }
  printf("%.9lf\n", cost);
  return 0;
}