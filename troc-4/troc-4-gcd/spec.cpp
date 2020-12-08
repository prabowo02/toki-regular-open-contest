#include <tcframe/spec.hpp>

using namespace tcframe;

#include<bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pf push_front
#define pb2 pop_back
#define pf2 pop_front
#define line printf("\n")
#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define ll long long
#define all(a) a.begin(),a.end()
#define vi vector<int>

using namespace std;


const int MAXN = 1e5;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> W;
  vector<int> U, V;
  int Q;
  vector<int> A, B;
  
  void InputFormat() {
    LINE(N, M);
    LINE(W % SIZE(N));
    LINES(U, V) % SIZE(M);
    LINE(Q);
    LINES(A, B) % SIZE(Q);
  }

  vector<int> answers;
  void OutputFormat() {
    LINES(answers) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(128);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXN);
    CONS(1 <= Q && Q <= MAXN);
    CONS(each_element_between(W, 1, MAXN));
    CONS(each_element_between(A, 1, N) && each_element_between(B, 1, N));
    CONS(each_element_between(U, 1, N) && each_element_between(V, 1, N));
    CONS(graph_connected());
    CONS(query_valid());
  }
  
  bool query_valid() {
    for (int i = 0; i < Q; i++) {
      if (A[i] == B[i]) return false;
    }
    return true;
  }
  
  vector<int> par;
  int rt(int a) { return par[a] = (a == par[a] ? a : rt(par[a])); }
  void join(int a,int b) {
    a = rt(a), b = rt(b);
    if (a != b) par[a] = b;
  }
  
  bool graph_connected() {
    par = vi(N + 1);
    iota(all(par), 0);
    
    rep(i, 0, M) join(U[i], V[i]);
    rep(i, 1, N + 1) {
      // printf("rt %d = %d\n", i, rt(i));
      if (rt(i) != rt(1)) return false; 
    }
    return true;
  }
  
  bool each_element_between(vi &arr, int lo, int hi) {
    for (auto a : arr)
      if (a < lo || a > hi) 
        return false;
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
      "5 5",
      "6 4 3 18 9",
      "1 2",
      "2 3",
      "3 4",
      "4 5",
      "1 4",
      "4",
      "1 2",
      "1 3",
      "2 4",
      "4 5",
    });
    
    Output({
      "2",
      "3",
      "2",
      "9",
    });
  }
  
  // 1 2 5 6
  // 4 3 8 7
  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "8 10",
      "8 1 8 8 7 7 7 1",
      "1 2",
      "2 3",
      "3 4",
      "4 1",
      "5 6",
      "6 7",
      "7 8",
      "8 5",
      "2 5",
      "3 8",
      "4",
      "1 7",
      "4 6",
      "1 3",
      "5 7",
    });
    
    Output({
      "1",
      "1",
      "8",
      "7",
    });
  }

  void TestGroup1() { 
    Subtasks({1});
    
    rep(i, 0, 3) {
      // notice all_query() is called after weight_subgraph()
      // overwrite Q in weight_subgraph() to all_query()
      CASE(N = 10, linear_graph(), weight_subgraph(), all_query());
      CASE(N = 10, complete_graph(), weight_subgraph(), all_query());
      CASE(N = 10, tree_graph(), weight_subgraph(), all_query());
      CASE(N = 10, random_graph(), weight_subgraph(), all_query());
      
      CASE(N = 10, linear_graph(), all_query(), weight_random());
      CASE(N = 10, complete_graph(), all_query(), weight_random());
      CASE(N = 10, tree_graph(), all_query(), weight_random());
      CASE(N = 10, random_graph(), all_query(), weight_random());
    }
    rep(i, 0, 3) {
      // notice all_query() is called after weight_subgraph()
      // overwrite Q in weight_subgraph() to all_query()
      CASE(N = 300, linear_graph(), weight_subgraph(), all_query());
      CASE(N = 300, complete_graph(), weight_subgraph(), all_query());
      CASE(N = 300, tree_graph(), weight_subgraph(), all_query());
      CASE(N = 300, random_graph(), weight_subgraph(), all_query());
      
      CASE(N = 300, linear_graph(), all_query(), weight_random());
      CASE(N = 300, complete_graph(), all_query(), weight_random());
      CASE(N = 300, tree_graph(), all_query(), weight_random());
      CASE(N = 300, random_graph(), all_query(), weight_random());
    }
    
    rep(i, 0, 3) {
      CASE(N = 100000, linear_graph(), weight_subgraph());
      CASE(N = 100000, tree_graph(), weight_subgraph());
      CASE(N = 100000, random_graph(), weight_subgraph());
      
      CASE(N = 100000, linear_graph(), random_query(), weight_random());
      CASE(N = 100000, tree_graph(), random_query(), weight_random());
      CASE(N = 50000, random_graph(), random_query(), weight_random());
      
      CASE(N = 100000, linear_graph(), random_query(), weight_same());
      CASE(N = 100000, tree_graph(), random_query(), weight_same());
      CASE(N = 50000, random_graph(), random_query(), weight_same());
      
      CASE(N = 40000, cluster_case());
    }
  }
  
  void linear_graph() {
    U = V = vi(N - 1);
    rep(i, 1, N) tie(U[i - 1], V[i - 1]) = mp(i, i + 1);
    M = U.size();
  }
  
  void complete_graph() {
    U = V = vi(0);
    rep(i, 1, N + 1) rep(j, i + 1, N + 1) {
      U.pb(i);
      V.pb(j);
    }
    M = U.size();
  }
  
  void tree_graph() {
    U = V = vi(0);
    int base_line = rnd.nextInt(2, N);
    // create base line
    rep(i, 2, base_line + 1) U.pb(i), V.pb(i - 1);
    // random the rest
    for (int rem = base_line + 1; rem <= N;) {
      // create chain of size sz, attach it to random node
      int sz = rnd.nextInt(1, N - rem + 1);
      int par = rnd.nextInt(1, rem - 1);
      rep(i, rem, rem + sz) U.pb(i), V.pb(par), par = i;
      rem += sz;
    }
    M = U.size();
  }
  
  void random_graph() {
    tree_graph();
    M = min(2 * N, MAXN);
    U.resize(M), V.resize(M);
    rep(k, N - 1, M) tie(U[k], V[k]) = mp(rnd.nextInt(1, N), rnd.nextInt(1, N));
  }
  
  void all_query() {
    A = B = vi(0);
    rep(i, 1, N + 1) rep(j, i + 1, N + 1) {
      A.pb(i);
      B.pb(j);
    }
    Q = A.size();
  }
  
  // Q always equal MAXN 
  void random_query() {
    Q = MAXN;
    A = B = vi(Q);
    rep(i, 0, Q) {
      A[i] = rnd.nextInt(1, N);
      do {
        B[i] = rnd.nextInt(1, N);
      } while (A[i] == B[i]);
    } 
  }
  
  int gcd(int a, int b) { return a == 0 ? b : gcd(b % a, a); }
  int lcm(int a, int b) { return (ll) a * b / gcd(a, b); }
  
  vi random_walk(int st, int steps, int col) {
    vi q;
    vi in_q(N + 1, 0), vis(N + 1, 0);
    vector<vi> adj(N + 1, vi(0));
    rep(k, 0, M) adj[U[k]].pb(V[k]), adj[V[k]].pb(U[k]);
    
    q.pb(st);
    in_q[st] = true;
    while (steps--) {
      int a = q.back(); q.pop_back();
      vis[a] = true;
      W[a - 1] = lcm(W[a - 1], col);
      for (int b : adj[a]) if (!in_q[b]) {
        q.pb(b); in_q[b] = true;
        swap(q[q.size() - 1], q[rnd.nextInt(0, q.size() - 1)]);
      }
    }
      
    vi visited;
    rep(i, 1, N + 1) if (vis[i]) visited.pb(i);
    return visited;
  }
  
  void weight_subgraph() {
    W = vi(N, 2);
    
    int col[10] = {3, 4, 5, 6, 7, 8, 9, 10, 12, 17};
    Q = MAXN; A = B = vi(Q);
    rep(i, 0, 10) {
      int &x = A[i], &y = B[i];
      x = rnd.nextInt(1, N);
      
      vi candidate = random_walk(x, rnd.nextInt(2, N), col[i]);
      y = candidate[rnd.nextInt(1, candidate.size() - 1)];
    }
    rep(i, 10, MAXN) {
      A[i] = rnd.nextInt(1, N);
      do {
        B[i] = rnd.nextInt(1, N);
      } while (A[i] == B[i]);
    }
  }
  
  void weight_random() {
    W = vi(N);
    for (auto &v : W) v = rnd.nextInt(1, MAXN / 2) * 2;
  }
  
  void weight_same() {
    vi cnt(MAXN + 1, 0), candidate; 
    int maks = 0;
    rep(k, 1, MAXN + 1) {
      for (int i = k; i <= MAXN; i+= k) cnt[i]++;
      if (cnt[k] >= 80) candidate.pb(k);
      maks = max(maks, cnt[k]);
    }
    
    int x = candidate[rnd.nextInt(0, candidate.size() - 1)];
    W = vi(N, x);
  }
  
  // create small graph numbered from id
  // with weight power of base_val
  void create_cluster(vi id, int base_val) {
    // random tree
    int n = id.size();
    vector<vi> adj(n, vi(0));
    rep(i, 1, n) {
      int x = i, y = rnd.nextInt(0, i - 1);
      U.pb(id[i]), V.pb(id[y]);
      adj[x].pb(y);
      adj[y].pb(x);
    }
    // random edges to create general connected graph
    rep(i, 0, n) {
      int x = rnd.nextInt(0, n - 1);
      int y = rnd.nextInt(0, n - 1);
      U.pb(id[x]), V.pb(id[y]);
      adj[x].pb(y);
      adj[y].pb(x);
    }
    rep(i, 0, n) rnd.shuffle(all(adj[i]));
    
    // pick query
    vi val;
    for (int i = 1; i <= MAXN; i *= base_val)
      val.pb(i);
    
    rep(i, 0, n * 2) {
      int a = rnd.nextInt(0, n - 1);
      int b = rnd.nextInt(0, n - 1);
      
      while (b == a) // reshuffle
        b = rnd.nextInt(0, n - 1);
      A.pb(id[a]); B.pb(id[b]);
      
      // puts("gg here");
      if (i >= val.size()) continue;
      int col = val[i];
      // colour from a to b with colour col
      // printf("cluster %d\n", i);
      queue<int> q;
      vi par(n, -1);
      
      q.push(a);
      par[a] = a;
      while(q.size()) {
        int nw = q.front(); q.pop();
        for (int nx : adj[nw]) if (par[nx] == -1) {
          par[nx] = nw;
          q.push(nx);
        }
      }
      
      for (int nw = b; ; nw = par[nw]) {
        W[id[nw] - 1] = lcm(W[id[nw] - 1], col);
        if (nw == a) break;
        nw = par[nw];
      }
    }
    
  }
  
  // create chain of small graph, each query will based on that small graph.
  void cluster_case() {
    U = V = A = B = vi(0);
    W = vi(N, 1);
    
    vi last_id;
    vi val = {2, 3};
    for (int i = 1; i <= N;) {
      int sz = 200;
      // sz = min(sz, N + 1 - i);
      
      vi id(sz);
      iota(all(id), i);
      i += sz;
      
      create_cluster(id, val[rnd.nextInt(0, 1)]);
      
      if (last_id.size()) { // join cluster
        // 10 edges from random nodes
        rep(j, 0, 10) {
          int x = last_id[rnd.nextInt(0, last_id.size() - 1)];
          int y = id[rnd.nextInt(0, id.size() - 1)];
          U.pb(x), V.pb(y);
        }
      }
      last_id = id;
    }
    rep(i, 0, W.size()) {
      W[i] *= rnd.nextInt(1, MAXN / W[i]);
    }
    M = U.size();
    Q = A.size();
  }
  
  void AfterTestCase() {
    // randomized node id
    // node id i becomes id ch[i]
    vi ch(N + 1), last_w = W;
    iota(all(ch), 0);
    random_shuffle(ch.begin() + 1, ch.end());
    rep(k, 0, N) {
      W[ch[k + 1] - 1] = last_w[k];
    }
    rep(k, 0, M) {
      U[k] = ch[U[k]], V[k] = ch[V[k]];
      if (rnd.nextInt(0, 1)) swap(U[k], V[k]);
    }
    rep(k, 0, Q) A[k] = ch[A[k]], B[k] = ch[B[k]];
  }
};
