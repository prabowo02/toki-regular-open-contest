//雪花飄飄北風嘯嘯
//天地一片蒼茫

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

int n;
int query(int l,int r,int d,int u){
	cout<<"? "<<l<<" "<<r<<" "<<d<<" "<<u<<endl;
	int temp;
	cin>>temp;
	return temp;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	
	cin>>n;
	
	int lo=0,hi=n,mi;
	while (hi-lo>1){
		mi=hi+lo>>1;
		
		int l=query(1,mi,1,n);
		int r=query(mi+1,n,1,n);
		int common=l+r-(n*n-1);
		
		if (l-common/2==mi*n) lo=mi;
		else hi=mi; 
	}
	
	int temp=hi;
	
	lo=0,hi=n,mi;
	while (hi-lo>1){
		if (hi-lo<=4){
			vector<int> v;
			rep(x,lo+1,hi+1) if ((temp+x)%2==0) v.pub(x);
			
			if (query(temp,temp,v[0],v[0])==0)
				cout<<"! "<<temp<<" "<<v[0]<<endl;
			else
				cout<<"! "<<temp<<" "<<v[1]<<endl;
			return 0;
		}
		else{
			mi=hi+lo>>1;
			
			int l=query(1,n,1,mi);
			int r=query(1,n,mi+1,n);
			int common=l+r-(n*n-1);
			
			if (l-common/2==mi*n) lo=mi;
			else hi=mi; 
		}
	}
}
