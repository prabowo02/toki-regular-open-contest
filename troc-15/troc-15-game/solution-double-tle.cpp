#include <iostream>
using namespace std;

constexpr int ITER = 1000;

double cnt[2][5005][2];
double ans[2], done[2];
// Done[i] = probability of player i has done

int main(){
  int n, tmpd, a, b;
  cin >> n >> tmpd >> a >> b;
  double d = tmpd;
  cnt[0][a][0] = cnt[1][b][0] = 1;

  for(int i = 1;i <= ITER;i++){
    for(int j = 0;j <= 1;j++){
      // Count (i&1)
      for(int k = 1;k <= n;k++) cnt[j][k][i&1] = 0;

      for(int k = 1;k < n;k++){
        for(int roll = 1;roll <= d;roll++){
          cnt[j][(k+roll > n ? n-(k+roll-n) : k+roll)][i&1] += cnt[j][k][!(i&1)]/d;
        }
      }
      
      // for(int k = 1;k <= n;k++) cout << cnt[j][k][i&1] << " \n"[k == n];
      // for(int k = 1;k <= n;k++) cout << cnt[j][k][!(i&1)] << " \n"[k == n];
      done[j] += cnt[j][n][i&1];
      ans[j] += cnt[j][n][i&1]*(1.0-done[!j]);

    }
  }
  cout << ans[0] << endl;
}
