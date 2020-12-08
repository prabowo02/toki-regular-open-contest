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
	int n, x;
	vector<int> a;
	cin >> n;
	for(int i = 1; i <= n; i++){
		int y;
		cin >> y;
		a.push_back(y);
	}
	cin >> x;
	for(int i = 0; i < n; i++){
		if(a[i] == x){
			cout << i + 1 << '\n';
			return 0;
		}
	}
	assert(false);
}