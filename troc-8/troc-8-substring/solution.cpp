#include <bits/stdc++.h>
using namespace std;

int b, o, n;
string S;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>S;
	
	for (char c : S) {
		if (c=='b') {
			b++;
		}
		
		if (c=='o') {
			o++;
		}
		
		if (c=='n') {
			n++;
		}
	}
	
	cout<<max(0,min(b,min(o,n))-1)<<'\n';
	
	return 0;
}
