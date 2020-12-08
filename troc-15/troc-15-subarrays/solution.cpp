#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 200000;
constexpr int MAXA = 200000;

int isi[MAXN+5];

void cant(){
  cout << "NO" << endl;
  exit(0);
}

int segt[4*MAXN+5];
int lazy[4*MAXN+5];

void pushdown(int kiri, int kanan, int idx){
  if(lazy[idx] == 0) return;
  segt[idx] += lazy[idx];
  if(kiri != kanan){
    lazy[idx<<1] += lazy[idx];
    lazy[idx<<1|1] += lazy[idx];
  }
  lazy[idx] = 0;
  return;
}

// Find minimum range, check whether there exists 0
void update(int kiri, int kanan, int idx, int l, int r, int val){
  pushdown(kiri, kanan, idx);
  if(kiri > r || kanan < l) return;
  if(l <= kiri && kanan <= r){
    lazy[idx] += val;
    pushdown(kiri, kanan, idx);
    return;
  }
  int mid = (kiri+kanan)>>1;
  update(kiri, mid, idx<<1, l, r, val);
  update(mid+1, kanan, idx<<1|1, l, r, val);
  segt[idx] = min(segt[idx<<1], segt[idx<<1|1]);
}

bool query(int kiri, int kanan, int idx, int l, int r){
  if(kiri > r || kanan < l) return 1;
  pushdown(kiri, kanan, idx);
  if(l <= kiri && kanan <= r) return !!segt[idx];
  int mid = (kiri+kanan)>>1;
  return query(kiri, mid, idx<<1, l, r) && query(mid+1, kanan, idx<<1|1, l, r);
}

int nx[MAXN+5];
int pre[MAXA+5];
bool done[MAXA+5];


int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  for(int i = 1;i <= n;i++){
    cin >> isi[i]; nx[i] = n+1;
    nx[pre[isi[i]]] = i;
    pre[isi[i]] = i;
  }

  for(int i = 1;i <= n;i++){
    if(!done[isi[i]]){
      update(1, n, 1, i, nx[i]-1, 1);
      done[isi[i]] = 1;
    }
  }

  for(int i = 1;i <= n;i++){
    if(!query(1, n, 1, i, n)) cant();
    update(1, n, 1, i, nx[i]-1, -1);
    if(nx[i] != n+1) update(1, n, 1, nx[i], nx[nx[i]]-1, 1);
  }

  cout << "YES" << endl;
  return 0;
}