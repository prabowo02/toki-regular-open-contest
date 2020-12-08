#include<bits/stdc++.h>
using namespace std;

int n;
long long A[100010];

inline bool valid(long long x) {
	int region=0;
	bool status=false;
	for (int i=0;i<n;i++) {
		if (A[i]+i<=x-2) {
			if (!status) status=true, region++;
		}
		if (A[i]+i==x-1) {
			if (!status) region++;
			status=false;
		}
		if (A[i]+i==x) {
			status=false;
		}
		if (region>=2) return false;
	}
	if (n!=x && !status) region++;
	return (region<=1);
}

int main() {
	long long ans=0, sum=0;
	scanf("%d",&n); for (int i=0;i<n;i++) {
		scanf("%lld",A+i); ans=max(ans,A[i]+i); sum+=A[i];
	}
	while (true) { //Harusnya range jawaban cuma di max(A[i]+i)..max(A[i]+i)+2
		if (!valid(ans)) ans++;	
		else {
			ans=ans*(ans+1)/2; ans-=sum;
			printf("%lld\n",ans); return 0;
		}
	}
	return 0;
	
}
