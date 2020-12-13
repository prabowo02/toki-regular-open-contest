#include <iostream>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> pii;

const int MAXN = 200000;
int d;
bool isi[MAXN + 5];
int segt[4 * MAXN + 5];
int lazy[4 * MAXN + 5];

void prop(int kiri, int kanan, int idx) {
    if(lazy[idx] == 0) return;
    segt[idx] += lazy[idx];
    if(kiri != kanan) {
        lazy[idx * 2] += lazy[idx];
        lazy[idx * 2 + 1] += lazy[idx];
    }
    lazy[idx] = 0;
    return;
}

void upd(int kiri, int kanan, int idx, int l, int r, int val) {
    prop(kiri, kanan, idx);
    if(kiri > r || kanan < l) return;
    if(l <= kiri && kanan <= r) {
        lazy[idx] += val;
        prop(kiri, kanan, idx);
        return;
    }
    int mid = (kiri + kanan) >> 1;
    upd(kiri, mid, idx * 2, l, r, val);
    upd(mid + 1, kanan, idx * 2 + 1, l, r, val);
    segt[idx] = max(segt[idx * 2], segt[idx * 2 + 1]);
    return;
}

int get(int kiri, int kanan, int idx) {
    prop(kiri, kanan, idx);
    return segt[idx];
}

int find(int kiri, int kanan, int idx, int tar) {
    prop(kiri, kanan, idx);
    if(kiri == kanan) return kiri;
    int mid = (kiri + kanan) >> 1;
    int ret = get(kiri, mid, idx * 2);
    if(ret > tar) return find(kiri, mid, idx * 2, tar);
    return find(mid + 1, kanan, idx * 2 + 1, tar);
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n >> d;

    for(int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        isi[i] = (ch == '1');
        if(isi[i]) upd(1, n, 1, i, max(1, i + d - 1), 1);
    }

    int q;
    cin >> q;
    for(int i = 1; i <= q; i++) {
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            isi[x] = !isi[x];
            upd(1, n, 1, x, max(1, x + d - 1), isi[x] ? 1 : -1);
        } else {
            int res = get(1, n, 1);
            if(res <= x) cout << -1 << '\n';
            else cout << find(1, n, 1, x) << '\n';
        }
    }

    return 0;
}
