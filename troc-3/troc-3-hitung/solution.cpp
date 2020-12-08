#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e6+5;

int N, H;
long long A[MAXN];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N;
	
	for (int i=0;i<=N;i++) {
		cin>>A[i];
	}
	
	if (A[N]-A[0]==N) {
		cout<<N+1<<'\n';
	}
	else if (A[N]-A[0]==N-1) {
		cout<<1<<'\n';
	}
	else {
		cout<<0<<'\n';
	}
	
	return 0;
}
