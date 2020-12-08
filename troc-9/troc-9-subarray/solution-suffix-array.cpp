#include <bits/stdc++.h>
using namespace std;

const int N = 40005;

int n, q;
int a[N];
vector<int> b[N];

int blen[N];
int idx[N];

vector<int> sa, lcp;
int LMatch[N], RMatch[N];

vector<int> suffixArray(const vector<int> &s) {
  int n = s.size();
  vector<int> sa(n), rank(n);
  iota(sa.begin(), sa.end(), 0);
  reverse(sa.begin(), sa.end());
  
  stable_sort(sa.begin(), sa.end(), [&s](int x, int y) {return s[x] < s[y];});
  for (int i=0; i<n; i++) rank[i] = s[i];
  
  for (int k=1; k<n; k<<=1) {
    vector<int> trank = rank;
    for (int i=0; i<n; i++) 
      rank[sa[i]] = (i > 0 && trank[sa[i-1]] == trank[sa[i]] && sa[i-1] + k < n && trank[sa[i-1] + (k>>1)] == trank[sa[i] + (k>>1)] ? rank[sa[i-1]] : i);
     
    vector<int> cnt(n), tsa = sa;
    iota(cnt.begin(), cnt.end(), 0);    
    
    for (int i=0; i<n; i++) {      
      if (tsa[i] - k >= 0)
        sa[cnt[rank[tsa[i] - k]]++] = tsa[i] - k;
    } 
  }
  
  return sa;
}

vector<int> LCP(const vector<int> &s, const vector<int> &sa) {
  int n = s.size();
  vector<int> rank(n);
  for (int i=0; i<n; i++) rank[sa[i]] = i;

  vector<int> lcp(n-1);
  for (int i=0, h=0; i<n; i++) {
    if (rank[i] < n-1) {
      for (int j=sa[rank[i] + 1]; max(i, j) + h < n && s[i+h] == s[j+h]; ++h);
      lcp[rank[i]] = h;
      if (h > 0) --h;
    }
  }
  return lcp;
}

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);
    b[i].resize(k);

    for (int j = 0; j < k; ++j) {
      scanf("%d", &b[i][j]);
    }
  }
}

void build() {
  vector<int> s;
  for (int i = 1; i < n; ++i) {
    idx[s.size()] = -1;
    s.push_back(a[i] ^ a[i-1]);
  }
  idx[s.size()] = -1;
  s.push_back(-1);

  for (int i = 0; i < q; ++i) {
    blen[i] = s.size();
    for (int j = 1; j < b[i].size(); ++j) {
      idx[s.size()] = i;
      s.push_back(b[i][j] ^ b[i][j-1]);
    }
    idx[s.size()] = i;
    s.push_back(-i-2);
  }

  sa = suffixArray(s);
  lcp = LCP(s, sa);

  // for (int num: s) cerr << num << " "; cerr << endl;
  // for (int num: sa) cerr << num << " "; cerr << endl;
  // for (int num: lcp) cerr << num << " "; cerr << endl;

  stack<int> st;

  st.push(0);
  LMatch[0] = st.top();
  for (int i = 1; i < sa.size(); ++i) {
    while (st.top() > 0 && lcp[i-1] <= lcp[st.top()-1]) st.pop();
    LMatch[i] = st.top();
    st.push(i);
  }

  while (st.size()) st.pop();

  st.push((int) sa.size() - 1);
  RMatch[(int) sa.size() - 1] = st.top();
  for (int i = (int) sa.size() - 2; i >= 0; --i) {
    while (st.top() < (int) sa.size()-1 && lcp[i] <= lcp[st.top()]) st.pop();
    RMatch[i] = st.top();
    st.push(i);
  }

  // for (int i = 0; i < sa.size(); ++i) cerr << LMatch[i] << " " << RMatch[i] << endl;
}

void solve1() {
  vector<int> pre(sa.size());
  for (int i = 1; i < sa.size(); ++i) {
    if (sa[i] < n) pre[i] = 1;
    pre[i] += pre[i-1];
  }

  int ans[q];
  for (int i = 0; i < sa.size(); ++i) {
    if (idx[sa[i]] >= 0 && sa[i] == blen[idx[sa[i]]]) {
      int L = (lcp[i-1] == b[idx[sa[i]]].size() ? LMatch[i] : i);
      int R = (i < lcp.size() && lcp[i] + 1 == b[idx[sa[i]]].size() ? RMatch[i] : i);

      ans[idx[sa[i]]] = pre[R] - pre[L-1];
    }
  }

  for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
}

int main() {
  read();
  build();
  solve1();
  return 0;
}