#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define ll long long
const int MX = 305;
const int mod = 998244353;

int N, K, P[MX];
int L[MX], R[MX];
int dp[MX][MX][MX][2];

inline void upd(int &a, int b){
	a += b;
	if(a >= mod) a -= mod;
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> N >> K;
	for(int i = 0; i < N; i ++){
		cin >> P[i];
		P[i] --;
	}

	for(int i = 0; i < N; i ++){
		L[P[i]] = i;
		R[P[i]] = i;
		for(; L[P[i]] > 0 && P[L[P[i]] - 1] < P[i]; L[P[i]] --);
		for(; R[P[i]] < N - 1 && P[R[P[i]] + 1] < P[i]; R[P[i]] ++);
	}

	dp[0][0][0][0] = 1;
	for(int i = 0; i <= N; i ++){
		for(int j = 0; j < N; j ++){
			for(int k = 0; k <= K; k ++){
				/* dont' use */
				upd(dp[i][j + 1][k][0], dp[i][j][k][0]);
				upd(dp[i][j + 1][k][0], dp[i][j][k][1]);

				/* use */
				if(L[P[j]] <= i && i <= R[P[j]]){
					upd(dp[i + 1][j][k][1], dp[i][j][k][1]);

					if(i != j)
						upd(dp[i + 1][j][k + 1][1], dp[i][j][k][0]);
					else{
						upd(dp[i + 1][j][k][0], dp[i][j][k][0]);
					}
				}
			}
		}
	}

	int ans = 0;
	for(int i = 0; i <= K; i ++){
		upd(ans, dp[N][N][i][0]);
		upd(ans, dp[N][N][i][1]);
	}

	cout << ans << endl;
	return 0;
}