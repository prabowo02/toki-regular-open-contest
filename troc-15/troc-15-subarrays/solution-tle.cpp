#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 200000;
constexpr int MAXA = 200000;

int cnt[MAXA+5];
int isi[MAXN+5];

void cant(){
  cout << "NO" << endl;
  exit(0);
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  for(int i = 1;i <= n;i++) cin >> isi[i];
  for(int i = 1;i <= n;i++){
    int cntone = 0;
    for(int j = i;j <= n;j++){
      if(cnt[isi[j]] == 2) continue;
      cntone += (++cnt[isi[j]] == 2 ? -1 : 1);
      if(!cntone) cant();
    }
    memset(cnt, 0, sizeof(cnt));
  }
  cout << "YES" << endl;
  return 0;
}