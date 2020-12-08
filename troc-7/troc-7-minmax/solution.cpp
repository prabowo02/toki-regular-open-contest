#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int N, R, P;
int A[MAXN];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N;
	
	for (int i=1;i<=N;i++) {
		cin>>A[i];
	}
	
	for (int i=1;i<=N;i++) {
		cin>>R;
		
		if (A[i]<R&&P==0) {
			A[i]++;
			P++;
		}
		
		if (A[i]<R) {
			P=2;
			break;
		}
	}
	
	if (P!=2) {
		cout<<-1<<'\n';
		return 0;
	}
	
	for (int i=1;i<=N;i++) {
		cout<<A[i];
		
		if (i==N) {
			cout<<'\n';
		}
		else {
			cout<<' ';
		}
	}
	
	return 0;
}
