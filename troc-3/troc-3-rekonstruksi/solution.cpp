#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int N, M;
int A[MAXN];
int D[MAXN];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>M;
	
	for (int i=1;i<=N;i++) {
		cin>>A[i];
		
		if (A[i]>N) {
			cout<<-1<<'\n';
			return 0;
		}
	}
	
	D[0]=1;
	
	for (int i=N;i>=1;i--) {
		D[A[i]]++;
		A[i]+=M*(D[A[i]]-1);
		
		if (A[i]>N) {
			cout<<-1<<'\n';
			return 0;
		}
	}
	
	for (int i=1;i<=N;i++) {
		if (i>1) {
			cout<<' ';
		}
		
		cout<<A[i];
	}
	
	cout<<'\n';
	
	return 0;
}
