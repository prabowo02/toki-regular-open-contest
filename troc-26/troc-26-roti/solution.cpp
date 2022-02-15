#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long LL;
typedef pair<int,int> ii;

const LL MX = 1e15;
const LL INF = 1e18;
int n, m, k;
vector<int> a, st, bt;
vector<LL> dp;

struct line {
    int id;
    LL m, c;
    line(LL x=0, LL y=0, LL z=0): m(x), c(y), id(z) {}
    LL operator () (LL x) {return m*x+c;}
};

bool greaterFrac(LL a, LL b, LL c, LL d) {
    // a/b >= c/d;
    if (a/b != c/d) return a/b > c/d;
    return (a%b)*d >= (c%d)*b;
}

bool isBad(line a, line b, line c) {
    // (c1-c2)/(m2-m1) >= (c2-c3)/(m3-m2)
    return greaterFrac(a.c-b.c,b.m-a.m,b.c-c.c,c.m-b.m);
}

struct convexHull {
    int sz;
    vector<line> v;
    convexHull() {sz = 0; v.clear();}

    void insert(LL m, LL c, int id) {
        line cur = line(m,c,id);
        while (sz >= 2 && isBad(v[sz-2],v[sz-1],cur)) {
            v.pop_back(); sz--;
        }
        v.push_back(cur); sz++;
    }

    int query(LL x) {
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

void monge(LL mid) {
    convexHull ch; 
    dp = vector<LL>(m+2);
    bt = vector<int>(m+2);
    for (int i = 1; i <= m; i++) {
        ch.insert(a[st[i]],dp[i-1],i-1);
        int p = ch.query(st[i]);
        dp[i] = ch.v[p](st[i])+mid;
        bt[i] = bt[ch.v[p].id]+1;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    a = st = vector<int>(n+2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    reverse(a.begin()+1,a.begin()+n+1);
    for (int i = 1; i <= n; i++) {
        while (m > 0 && a[st[m]] <= a[i]) m--;
        st[++m] = i;
    }
    LL ans = INF;
    for (LL l = 0, r = MX; l <= r; ) {
        LL mid = (l+r)/2; monge(mid);
        if (bt[m] <= k) {
            ans = dp[m]-mid*bt[m];
            r = mid-1;
        }
        else l = mid+1;
    }
    assert(ans != INF);
    cout << ans << '\n';
    return 0;
}