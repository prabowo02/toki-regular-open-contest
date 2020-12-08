#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 1000100100;
const long long INFLL = 1LL*INF*INF;

int h, n;
int d[N];
int s;
int a[N], b[N], t[N], q[N];
int x;

long long ans[N];

void read() {
  scanf("%d %d", &h, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &d[i]);
  }
  scanf("%d", &s);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d %d", &a[i], &b[i], &t[i], &q[i]);
  }
  scanf("%d", &x);
  --x;
}

struct Line {
  long long vert;
  int slope;

  Line(long long _vert=0, int _slope=0): vert(_vert), slope(_slope) {}

  long long eval(int x) {
    return 1LL*slope*x + vert;
  }
};

class LiChao {
  vector<int> coordinates;
  vector<Line> lines;

  void update(int node, int l, int r, Line line) {
    bool ll = line.eval(coordinates[l]) <= lines[node].eval(coordinates[l]);
    bool rr = line.eval(coordinates[r]) <= lines[node].eval(coordinates[r]);

    if (ll == rr) {
      if (ll) swap(lines[node], line);
      return;
    }

    int mid = (l + r) >> 1;
    update(node*2 + 1, l, mid+0, line);
    update(node*2 + 2, mid+1, r, line);
  }

  void update(int node, int l, int r, int ll, int rr, Line line) {
    if (l > rr || r < ll) return;
    if (ll <= l && r <= rr) return update(node, l, r, line);

    int mid = (l + r) >> 1;

    update(node*2 + 1, l, mid+0, ll, rr, line);
    update(node*2 + 2, mid+1, r, ll, rr, line);
  }

  long long query(int node, int l, int r, int x) {
    if (l > x || r < x) return INFLL;
    if (l == x && r == x) return lines[node].eval(coordinates[x]);

    int mid = (l + r) >> 1;
    return min(lines[node].eval(coordinates[x]), 
      min(query(node*2 + 1, l, mid+0, x), query(node*2 + 2, mid+1, r, x)));
  }

  inline int getIdx(int coor) {
    return lower_bound(coordinates.begin(), coordinates.end(), coor) - coordinates.begin();
  }

 public:
  void init(vector<int> _coordinates) {
    coordinates = _coordinates;
    lines = vector<Line>(coordinates.size() * 4, Line(INFLL));
  }

  void add(int l, int r, Line line) {
    update(0, 0, (int) coordinates.size() - 1, getIdx(l), getIdx(r), line);
  }

  long long query(int x) {
    return query(0, 0, (int) coordinates.size() - 1, getIdx(x));
  }
} tree;

void init() {
  vector<int> floors(n*3 + 2);
  for (int i = 0; i < n; ++i) {
    floors[i*3 + 0] = a[i];
    floors[i*3 + 1] = b[i];
    floors[i*3 + 2] = d[i];
  }
  floors[n*3] = 1; floors[n*3 + 1] = h;

  sort(floors.begin(), floors.end());
  floors.resize(unique(floors.begin(), floors.end()) - floors.begin());

  tree.init(floors);
}

void update(int x, long long dist) {
  ans[x] = dist;

  // Only use stairs
  tree.add(1, d[x], Line(1LL*d[x]*s + dist, -s));
  tree.add(d[x], h, Line(-1LL*d[x]*s + dist, s));

  // Use lift
  tree.add(a[x], d[x], Line(1LL*d[x]*t[x] + q[x] + dist, -t[x]));
  tree.add(d[x], b[x], Line(-1LL*d[x]*t[x] + q[x] + dist, t[x]));

  // Use stairs after lift
  tree.add(1, a[x], Line(1LL*a[x]*s + 1LL*(d[x]-a[x])*t[x] + q[x] + dist, -s));
  tree.add(b[x], h, Line(-1LL*b[x]*s + 1LL*(b[x]-d[x])*t[x] + q[x] + dist, s));
}

void solve() {
  int l = x, r = x;
  update(x, 0LL);
  while (l > 0 || r+1 < n) {
    if (l == 0) ++r, update(r, tree.query(d[r]));
    else if (r+1 == n) --l, update(l, tree.query(d[l]));
    else {
      long long distL = tree.query(d[l-1]), distR = tree.query(d[r+1]);
      if (distL < distR) {
        update(--l, distL);
      } else {
        update(++r, distR);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
  read();
  init();
  solve();
  return 0;
}
