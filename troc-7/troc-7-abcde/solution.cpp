#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pb push_back
#define reset(a,b) memset(a,b,sizeof a);
#define ALL(x) x.begin(),x.end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define sz(x) (int)(x.size())
#define lt(x) (int)(x.length())
#define MOD 1000000007 
#define mx 100003

int main(){
	int P, Q, R, S, T;
	cin >> P >> Q >> R >> S >> T;
	for(int a = 1; a <= 8; a++){
		for(int b = 1; b <= 8; b++){
			for(int c = 1; c <= 8; c++){
				for(int d = 1; d <= 8; d++){
					for(int e = 1; e <= 8; e++){
						if(P == a * b && Q == b * c && R == c * d && S == d * e && T == e * a){
							cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << '\n';
							return 0;
						}
					}
				}
			}
		}
	}
}