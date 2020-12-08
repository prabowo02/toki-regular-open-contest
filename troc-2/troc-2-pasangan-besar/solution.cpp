#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M = 5e4;

int n, x, y, c, d, m1, m2;

int cntA[M + 5];
int cntB[M + 5];

int urut[M + 5];

inline void genA(){
  int tmpn = 1;
  int now = x;
  memset(urut, -1, sizeof urut);
  urut[now] = 0;
  cntA[now] = 1;

  int cycleawal = -1, cycleakhir = -1;
  for(int i = 1;i < n; ++i, ++tmpn){
    now = (1LL * now * c) % m1;
    if(urut[now] != -1){
      cycleawal = urut[now];
      cycleakhir = tmpn;
      break;
    }
    else{
      urut[now] = tmpn;
      cntA[now] = 1;
    }
  }

  if(cycleawal != -1){
    int cycle = cycleakhir - cycleawal;
    int banyak = (n - tmpn) / cycle;
    for(int i = 0;i < m1; ++i){
      if(urut[i] >= cycleawal && urut[i] < cycleakhir){
        cntA[i] += banyak;
      }
    }
    tmpn += cycle * banyak;
  }

  for(int i = tmpn; i < n; ++i){
    cntA[now]++;
    now = (1LL * now * c) % m1;
  }

  // fprintf(stderr, "DEBUG\n");
  // for(int i = 0;i < m1; ++i){
  //   fprintf(stderr, "A %d: %d\n", i, cntA[i]);
  // }
}

inline void genB(){
  int tmpn = 1;
  int now = y;

  memset(urut, -1, sizeof urut);
  urut[now] = 0;
  cntB[now] = 1;

  int cycleawal = -1, cycleakhir = -1;
  for(int i = 1;i < n; ++i, ++tmpn){
    now = (1LL * now * d) % m2;
    if(urut[now] != -1){
      cycleawal = urut[now];
      cycleakhir = tmpn;
      break;
    }
    else{
      urut[now] = tmpn;
      cntB[now] = 1;
    }
  }

  if(cycleawal != -1){
    int cycle = cycleakhir - cycleawal;
    int banyak = (n - tmpn) / cycle;
    for(int i = 0;i < m2; ++i){
      if(urut[i] >= cycleawal && urut[i] < cycleakhir){
        cntB[i] += banyak;
      }
    }
    tmpn += cycle * banyak;
  }

  for(int i = tmpn; i < n; ++i){
    cntB[now]++;
    now = (1LL * now * d) % m2;
  }
}

inline void checkSame(){
  int totalA = 0;
  int totalB = 0;
  for(int i = 0;i < m1; ++i) totalA += cntA[i];
  for(int i = 0;i < m2; ++i) totalB += cntB[i];

  //fprintf(stderr, "TOTAL : %d %d\n", totalA, totalB);
  assert(totalA == totalB);
}

int main(){

  LL ans = 0;
  cin >> n >> x >> y >> c >> d >> m1 >> m2;
  
  genA();
  genB();
  checkSame();

  int idxA = 0, idxB = 0;
  while(idxA != m1 && idxB != m2){
    int mins = min(cntA[idxA], cntB[idxB]);
    ans += 1LL * mins * idxA * idxB;
    cntA[idxA] -= mins;
    cntB[idxB] -= mins;
    if(!cntA[idxA]) idxA++;
    if(!cntB[idxB]) idxB++;
  }

  cout << ans << endl;
  return 0;
}

//bisa aja dia yang muter tapi ada sisanya gitu wkwkwkwk
//10 3 10 2 3 10 11
//10 3 10 2 3 8 11
//5 3 2 3 2 4 4
