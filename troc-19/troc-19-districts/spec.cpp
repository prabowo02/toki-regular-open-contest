#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXN = 1e5;
const int MAXVAL = 1e6;

struct Event {
  int l, r, y, ty;
  Event() {}
  Event(int _l, int _r, int _y, int _ty) : l(_l), r(_r), y(_y), ty(_ty) {}
  bool operator < (const Event& ot) const {
    if(y == ot.y) return ty < ot.ty;
    else return y < ot.y;
  }
};

struct Fenwick {
  int n;
  vector<int> ft;
  Fenwick(int _n) : n(_n) {
    ft.assign(n+1, 0);
  }
  void update(int x, int val) {
    for(; x <= n; x+=x&(-x)) ft[x] += val;
  }
  int query(int x) {
    int ret = 0;
    for(; x; x-=x&(-x)) ret += ft[x];
    return ret;
  }
  int query(int l, int r) {
    return query(r) - query(l-1);
  }
};

struct Rect {
  int a, b, c, d;
  Rect() {}
  Rect(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}
};

vector<pair<int, int>> events[2][MAXVAL+1];

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> a, b, c, d;
  long long ans;

  void InputFormat() {
    LINE(N);
    LINES(a, b, c, d) % SIZE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Subtask1() {
    Points(100);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(allBetween(a, 1, MAXVAL));
    CONS(allBetween(b, 1, MAXVAL));
    CONS(allBetween(c, 1, MAXVAL));
    CONS(allBetween(d, 1, MAXVAL));
    CONS(allSmaller(a, c));
    CONS(allSmaller(b, d));
    CONS(noOverlap(a, b, c, d));
  }

private:
  bool between(int x, int l, int r) {
    return (l <= x && x <= r);
  }

  bool allBetween(vector<int> &v, int l, int r) {
    for(auto x : v) if(!between(x, l, r)) return 0;
    return 1;
  }

  bool allSmaller(vector<int> &a, vector<int> &b) {
    int sz = a.size();
    for(int i = 0; i < sz; i++) if(a[i] >= b[i]) return false;
    return true;
  }

  bool noOverlap(vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &d) {
    int n = a.size();
    vector<Event> events;
    for(int i = 0; i < n; i++) {
      events.push_back(Event(a[i], c[i], b[i], 1));
      events.push_back(Event(a[i], c[i], d[i], -1));
    }
    sort(events.begin(), events.end());
    Fenwick ft(MAXVAL);
    for(Event e : events) {
      if(e.ty == 1) { //open
        if(ft.query(e.l) != ft.query(e.r-1) || ft.query(e.l) % 2 != 0) return false;
        else {
          ft.update(e.l, 1);
          ft.update(e.r, 1);
        }
      } else { //close
        ft.update(e.l, -1);
        ft.update(e.r, -1);
      }
    }
    return (ft.query(MAXVAL) == 0);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "4",
      "1 2 3 4",
      "2 4 3 5",
      "3 1 5 4",
      "3 4 6 7"
    });
    Output({
      "5"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3",
      "1 1 2 2",
      "2 2 3 3",
      "3 1 4 2"
    });
    Output({
      "-1"
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "2",
      "1 1 2 2",
      "100 100 101 101"
    });
    Output({
      "0"
    });
  }

  void BeforeTestCase() {
    a.clear();
    b.clear();
    c.clear();
    d.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 4, a = {1, 2, 4, 4}, b = {2, 4, 1, 4}, c = {3, 3, 6, 7}, d = {4, 5, 4, 7});
    CASE(N = 5, a = {1, 1, 1, 1, 2}, b = {1, 2, 3, 4, 1}, c = {2, 2, 2, 2, MAXVAL}, d = {2, 3, 4, 5, MAXVAL});
    // Line graphs
    CASE(generateRandomOneConnected(2, MAXVAL));
    CASE(generateRandomOneConnected(2, rnd.nextInt(2, MAXVAL)));
    CASE(generateRandomOneConnected(MAXVAL, 2));
    CASE(generateRandomOneConnected(rnd.nextInt(2, MAXVAL), 2));

    // 1 component (with max test)
    CASE(generateRandomOneConnected(20, 20));
    CASE(generateRandomOneConnected(MAXVAL, MAXVAL));
    
    // 1 component random connected
    CASE(generateRandomOneConnected(rnd.nextInt(2, MAXVAL), rnd.nextInt(2, MAXVAL)));
    CASE(generateRandomOneConnected(rnd.nextInt(2, MAXVAL), rnd.nextInt(2, MAXVAL)));

    // "star" graph
    CASE(generateStarRandom());
    CASE(generateStarMax());

    // 2 component line graphs
    CASE(generateRandomTwoConnected(2, MAXVAL/2, 3, MAXVAL));
    CASE(generateRandomTwoConnected(MAXVAL/2, 2, MAXVAL, 3));

    // 2 component
    CASE(generateRandomTwoConnected(20, 20, 40, 40));
    CASE(generateRandomTwoConnected(MAXVAL/2, MAXVAL/2, MAXVAL, MAXVAL));
    CASE(generateRandomTwoConnected(rnd.nextInt(2, MAXVAL/2), rnd.nextInt(2, MAXVAL/2), rnd.nextInt(MAXVAL/2+1, MAXVAL), rnd.nextInt(MAXVAL/2+1, MAXVAL)));
    CASE(generateRandomTwoConnected(rnd.nextInt(2, MAXVAL/2), rnd.nextInt(2, MAXVAL/2), rnd.nextInt(MAXVAL/2+1, MAXVAL), rnd.nextInt(MAXVAL/2+1, MAXVAL)));

    // impossible line graphs
    CASE(generateRandom(2, MAXVAL));
    CASE(generateRandom(MAXVAL, 2));

    // impossible random test cases
    CASE(generateRandom(20, 20));
    CASE(generateRandom(MAXVAL, MAXVAL));
    CASE(generateRandom(rnd.nextInt(2, MAXVAL), rnd.nextInt(2, MAXVAL)));
    CASE(generateRandom(rnd.nextInt(2, MAXVAL), rnd.nextInt(2, MAXVAL)));
  }

private:
  bool isCutable(Rect &x) {
    return ((x.c - x.a) > 1 || (x.d - x.b) > 1);
  }

  vector<Rect> generateRandomRectangles(int n, int m, int limit) {
    vector<Rect> res;
    res.push_back(Rect(1, 1, n, m));
    int avail = (int)isCutable(res.back());

    while(res.size() < limit && avail > 0) {
      if(res.size() >= 2 && rnd.nextInt(100000) < 1) break;
      int idx = rnd.nextInt(avail);
      int pos;

      if(res[idx].c - res[idx].a == 1) pos = 0;
      else if(res[idx].d - res[idx].b == 1) pos = 10;
      else pos = rnd.nextInt(20);

      if(pos < 10) { //horizontal line
        int x = rnd.nextInt(res[idx].b+1, res[idx].d-1);
        res.push_back(Rect(res[idx].a, x, res[idx].c, res[idx].d));
        res[idx].d = x;
      } else { //vertical line
        int x = rnd.nextInt(res[idx].a+1, res[idx].c-1);
        res.push_back(Rect(x, res[idx].b, res[idx].c, res[idx].d));
        res[idx].c = x;
      }

      if(!isCutable(res[idx])) {
        swap(res[idx], res[avail-1]);
        avail--;
      }
      if(isCutable(res[res.size()-1])) {
        swap(res[res.size()-1], res[avail]);
        avail++;
      }
    }
    return res;
  }

  vector<vector<int>> getAdjList(vector<Rect>& rects) {
    for(int i = 0; i <= 1; i++) {
      for(int j = 1; j <= MAXVAL; j++) {
        events[i][j].clear();
      }
    }
    int n = rects.size();

    vector<vector<int>> adj(n+1);
    for(int i = 1; i <= n; i++) {
      Rect &x = rects[i-1];
      events[0][x.b].push_back({x.a, i}); events[0][x.b].push_back({x.c, -i});
      events[0][x.d].push_back({x.a, i}); events[0][x.d].push_back({x.c, -i});
      events[1][x.a].push_back({x.b, i}); events[1][x.a].push_back({x.d, -i});
      events[1][x.c].push_back({x.b, i}); events[1][x.c].push_back({x.d, -i});
    }

    for(int ty = 0; ty <= 1; ty++) {
      for(int i = 1; i <= MAXVAL; i++) {
        sort(events[ty][i].begin(), events[ty][i].end());
        pair<int, int> nw = {0, 0};
        for(auto& x : events[ty][i]) {
          if(x.second > 0) {
            if(nw.first == 0) nw.first = x.second;
            else if(nw.second == 0) nw.second = x.second;
            else assert(0);
            if(nw.first != 0 && nw.second != 0) {
              adj[nw.first].push_back(nw.second);
              adj[nw.second].push_back(nw.first);
            }
          } else {
            if(nw.first == -x.second) nw.first = 0;
            else if(nw.second == -x.second) nw.second = 0;
            else assert(0);
          }
        }
      }
    }
    return adj;
  }

  vector<bool> randomPickConnected(int n, vector<vector<int>> &adj) {
    vector<bool> vis(n+1);
    queue<int> q;
    int cnt = 0;
    q.push(rnd.nextInt(1, n));
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if(!vis[u]) {
        vis[u] = 1;
        cnt++;
        for(int v : adj[u]) if(!vis[v]) {
          if(cnt == 1 || rnd.nextInt(10000) < 9999) q.push(v);
        }
      }
    }
    return vis;
  }

  vector<Rect> generateRectanglesConnected(int x1, int y1, int x2, int y2, int limit) {
    vector<Rect> rects = generateRandomRectangles(x2-x1+1, y2-y1+1, limit);
    for(Rect &x : rects) {
      x.a += x1-1; x.c += x1-1;
      x.b += y1-1; x.d += y1-1;
    }
    vector<vector<int>> adj = getAdjList(rects);
    vector<bool> picked = randomPickConnected(rects.size(), adj);
    vector<int> idx;

    vector<Rect> ret;
    for(int i = 0; i < rects.size(); i++) {
      if(picked[i+1]) ret.push_back(rects[i]);
    }
    return ret;
  }

  void generateRandomOneConnected(int n, int m) {
    vector<Rect> rects = generateRectanglesConnected(1, 1, n, m, MAXN);
    rnd.shuffle(rects.begin(), rects.end());
    for(Rect &x : rects) {
      a.push_back(x.a);
      b.push_back(x.b);
      c.push_back(x.c);
      d.push_back(x.d);
    }
    N = rects.size();
  }

  void generateRandomTwoConnected(int n1, int m1, int n2, int m2) {
    vector<Rect> rects1 = generateRectanglesConnected(1, 1, n1, m1, MAXN/2);
    vector<Rect> rects2 = generateRectanglesConnected(n1, m1, n2, m2, MAXN/2);
    while(!rects2.empty()) {
      rects1.push_back(rects2.back());
      rects2.pop_back();
    }
    rnd.shuffle(rects1.begin(), rects1.end());
    for(Rect &x : rects1) {
      a.push_back(x.a);
      b.push_back(x.b);
      c.push_back(x.c);
      d.push_back(x.d);
    }
    N = rects1.size();
  }

  void generateRandom(int n, int m) {
    vector<Rect> rects = generateRandomRectangles(n, m, MAXN);
    rnd.shuffle(rects.begin(), rects.end());
    N = rnd.nextInt(2, rects.size());
    for(int i = 0; i < N; i++) {
      Rect &x = rects[i];
      a.push_back(x.a);
      b.push_back(x.b);
      c.push_back(x.c);
      d.push_back(x.d);
    }
  }

  vector<Rect> generateStarLeaf(Rect mid) {
    vector<Rect> rects;
    for(int x = mid.a, y; x < mid.c; x = y) {
      y = rnd.nextInt(x+1, mid.c);
      if(rects.size() >= MAXN-2) break;
      if(rnd.nextInt(10) <= 3) continue;
      rects.push_back(Rect(x, rnd.nextInt(1, mid.b-1), y, mid.b));
      rects.push_back(Rect(x, mid.d, y, rnd.nextInt(mid.d+1, MAXVAL)));
    }
    for(int x = mid.b, y; x < mid.d; x = y) {
      y = rnd.nextInt(x+1, mid.d);
      if(rects.size() >= MAXN-2) break;
      if(rnd.nextInt(10) <= 3) continue;
      rects.push_back(Rect(rnd.nextInt(1, mid.a-1), x, mid.a, y));
      rects.push_back(Rect(mid.c, x, rnd.nextInt(mid.c+1, MAXVAL), y));
    }
    return rects;
  }

  void generateStarRandom() {
    Rect mid;
    mid.a = rnd.nextInt(2, MAXVAL-2);
    mid.b = rnd.nextInt(2, MAXVAL-2);
    mid.c = rnd.nextInt(mid.a+1, MAXVAL-1);
    mid.d = rnd.nextInt(mid.b+1, MAXVAL-1);
    vector<Rect> rects = generateStarLeaf(mid);
    rects.push_back(mid);

    rnd.shuffle(rects.begin(), rects.end());

    N = rects.size();
    for(int i = 0; i < N; i++) {
      Rect &x = rects[i];
      a.push_back(x.a);
      b.push_back(x.b);
      c.push_back(x.c);
      d.push_back(x.d);
    }
  }

  void generateStarMax() {
    Rect mid = Rect(2, 2, 25000, 25000);
    vector<Rect> rects;
    rects.push_back(mid);
    for(int i = rects[0].a; i < rects[0].c; i++) {
      rects.push_back({i, 1, i+1, 2});
      rects.push_back({i, 25000, i+1, 25001});
    }
    for(int i = rects[0].b; i < rects[0].d; i++) {
      rects.push_back({1, i, 2, i+1});
      rects.push_back({25000, i, 25001, i+1});
    }
    rnd.shuffle(rects.begin(), rects.end());

    N = rects.size();
    for(int i = 0; i < N; i++) {
      Rect &x = rects[i];
      a.push_back(x.a);
      b.push_back(x.b);
      c.push_back(x.c);
      d.push_back(x.d);
    }
  }
};
