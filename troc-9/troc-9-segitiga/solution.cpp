#include <bits/stdc++.h>
using namespace std;

int A[3];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	for (int i=0;i<3;i++) {
		cin>>A[i];
	}
	
	sort(A,A+3);
	
	if (A[0]%A[1]==0&&A[1]%A[2]==A[2]-1&&A[2]%A[0]==1) {
	//if (A[0]!=1&&A[0]==A[1]&&A[1]==A[2]-1) {
	//if (A[0]+A[1]>A[2]&&A[0]==A[1]&&A[1]==A[2]-1) {
		cout<<"Ya\n";
	}
	else {
		cout<<"Tidak\n";
	}
	
	return 0;
}
