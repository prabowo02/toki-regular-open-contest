// Super Idol的笑容
//    都没你的甜
//  八月正午的阳光
//    都没你耀眼
//  热爱105°C的你
// 滴滴清纯的蒸馏水

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#define ll long long
#define ii pair<ll,ll>
#define iii pair<ii,ll>
#define fi first
#define se second
#define endl '\n'
#define debug(x) cout << #x << ": " << x << endl

#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define lb lower_bound
#define ub upper_bound

#define rep(x,start,end) for(auto x=(start)-((start)>(end));x!=(end)-((start)>(end));((start)<(end)?x++:x--))
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

#define indexed_set tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>
//change less to less_equal for non distinct pbds, but erase will bug

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int n,k;
string s;

int calc(int l,int r){
	int cnt1=0;
	int res=0;
	
	rep(x,l,r+1){
		if (s[x]=='0') res+=cnt1;
		else cnt1++;
	}
	
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	
	cin>>n>>k;
	cin>>s;
	
	int l=0,r=n-1;
	
	rep(x,0,k){
		while (l<n && s[l]=='0') l++;
		while (r>=0 && s[r]=='1') r--;
		
		if (l>r) break;
		
		int cnt0=0,cnt1=0;
		rep(x,l,n) if (s[x]=='0') cnt0++;
		rep(x,0,r) if (s[x]=='1') cnt1++;
		
		if (cnt0>cnt1) s[l]='0';
		else s[r]='1';
	}
	
	cout<<calc(0,n-1)<<endl;
}
