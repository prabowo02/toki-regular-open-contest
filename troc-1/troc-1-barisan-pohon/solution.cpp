#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pob pop_back
#define REPP(i,l,r,c) for (int i=l;i<r;i+=c)
#define REP(i,l,r) REPP(i,l,r,1)
#define REPS(i,l,r) REP(i,l,r+1)
#define FOR(i,n) REP(i,0,n)
#define FORS(i,n) REPS(i,0,n)
#define REPD(i,l,r) for (int i=r-1;i>=l;i--)
#define FORD(i,l,r) REPD(i,0,n)
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int INF=1E9;
const ll INFLL=1E16;
const double INFD=1E9;
const double EPS=1E-9;
const ll MOD=1E9+7;
const double PI=acos(-1.0);

bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}

void in(int &number) {
    bool negative=false; register int c;
    number=0; c=getchar();
    if (c=='-') negative=true, c=getchar();
    for (;c>47&&c<58;c=getchar()) number=number*10+c-48;
    if (negative) number*=-1;
}

const int MAX_A=1000000;
const int MAX_N=300000;

int n;
int A[MAX_N+10];
int cnt[MAX_A+10];

int zero() {
	memset(cnt,0,sizeof cnt);
	FOR(i,n) cnt[A[i]]++;
	int ret=-INF; FOR(i,n) ret=max(ret,cnt[A[i]]);
	return n-ret;
}

int solve() {
	memset(cnt,0,sizeof cnt);
	int ret=INF;
	REPS(d,1,MAX_A) {						//Harmonik O(MAX_A ln MAX_A)
		int cur=MAX_A/d+1; cur=min(cur,n);
		int benar=0;
		FOR(i,cur) {
			int A0=A[i]-i*d;
			if (A0>0) cnt[A0]++, benar=max(benar,cnt[A0]);
		}
		ret=min(ret,n-benar);
		FOR(i,cur) {
			int A0=A[i]-i*d;
			if (A0>0) cnt[A0]--;
		}
	}
	return ret;
}

int main() {
	in(n); FOR(i,n) in(A[i]);
	int ans=zero();							//d=0
	ans=min(ans,solve());					//d>0
	reverse(A,A+n); ans=min(ans,solve());	//d<0
	printf("%d",ans); puts("");
	return 0;
}

