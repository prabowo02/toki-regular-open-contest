#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int,int> ii;

const int INF = 2e9;
int n, k;
vector<int> a, bt;
vector<ll> dp;

struct line {
    int id;
    ll m, c;
    line(ll x=0, ll y=0, int z=0): m(x), c(y), id(z) {}
    ll operator () (ll x) {return m*x+c;}
};

bool greaterFrac(ll a, ll b, ll c, ll d) {
    // a/b >= c/d
    if (a/b != c/d) return a/b > c/d;
    return (a%b)*d >= (c%d)*b;
}

bool isBad(line a, line b, line c) {
    // (c1-c2)/(m2-m1) >= (c2-c3)/(m3-m2);
    return greaterFrac(a.c-b.c,b.m-a.m,b.c-c.c,c.m-b.m);
}

struct convexHull {
    int sz; 
    vector<line> v;
    convexHull() {sz = 0; v.clear();}

    void insert(ll m, ll c) {
        line cur = line(m,c);
        while (sz >= 2 && isBad(v[sz-2],v[sz-1],cur)) {
            v.pop_back(); sz--;
        }
        v.push_back(cur); sz++;
    }

    int query(ll x) {
        int ret = -1;
        for (int l = 0, r = sz-1; l <= r; ) {
            int mid = (l+r)/2;
            if (ret == -1 || v[mid](x) < v[ret](x)) ret = mid;
            if (mid+1 < sz && v[mid+1](x) < v[mid](x)) l = mid+1;
            else r = mid-1;
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    a = vector<int>(n+2); a[0] = INF;
    for (int i = 1; i <= n; i++) cin >> a[i];
    reverse(a.begin()+1,a.begin()+n+1);
    vector<int> st; st.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (a[st.back()] <= a[i]) st.pop_back();
        st.push_back(i);
    }
    int m = st.size()-1;
    dp = vector<ll>(m+2), bt = vector<int>(m+2);
    convexHull ch; map<ll,int> op;
    for (int i = 1; i <= m; i++) {
        if (bt[i-1] < k) ch.insert(a[st[i]],dp[i-1]);
        int p = ch.query(st[i]);
        dp[i] = ch.v[p](st[i]);
        bt[i] = bt[ch.v[p].id]+1;
    }
    cout << dp[m] << '\n';
    return 0;
}