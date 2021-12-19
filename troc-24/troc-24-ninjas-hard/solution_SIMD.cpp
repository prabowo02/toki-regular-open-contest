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

const int dx[]={0,0,-1,1};
const int dy[]={1,-1,0,0};

int n,q;
string moves,clap;

deque<ii> dq;

int ans[50005];

map<ii,int> m;

struct upd{
	int time;
	int pos;
	int dir;
	int val;
};
vector<upd> v;

int arr[100005];
int brr[50005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	
	cin>>n>>q;
	cin>>moves;
	cin>>clap;
	
	int IDX=0;
	
	rep(x,n,0){
		dq.pub(ii(x,0));
		m[dq.back()]=IDX++;
	}
	
	rep(x,0,q){
		rep(z,0,4){
			int i=dq.front().fi,j=dq.front().se;
			int i2=i+dx[z],j2=j+dy[z];
			if (m.count(ii(i2,j2))){
				v.pub({m[ii(i,j)]-x,m[ii(i,j)],z,1});
				v.pub({m[ii(i2,j2)]-x,m[ii(i2,j2)],z^1,1});
			}
		}
		m.erase(dq.front());
		dq.pof();
		
		ii temp=dq.back();
		if (moves[x]=='U') temp.se++;
		if (moves[x]=='D') temp.se--;
		if (moves[x]=='R') temp.fi++;
		if (moves[x]=='L') temp.fi--;
		
		dq.pub(temp);
		m[temp]=IDX++;
		
		rep(z,0,4){
			int i=dq.back().fi,j=dq.back().se;
			int i2=i+dx[z],j2=j+dy[z];
			if (m.count(ii(i2,j2))){
				v.pub({m[ii(i,j)]-x,m[ii(i,j)],z,-1});
				v.pub({m[ii(i2,j2)]-x,m[ii(i2,j2)],z^1,-1});
			}
		}
	}
	
	rep(x,0,n){
		rep(z,0,4){
			int i2=dq[x].fi+dx[z],j2=dq[x].se+dy[z];
			if (m.count(ii(i2,j2))) v.pub({m[dq[x]]-q,m[dq[x]],z,1});
		}
	}
	
	sort(all(v),[](upd i,upd j){
		return i.time>j.time;
	});
	
	rep(x,0,q) if (clap[x]=='1') brr[x]=1;
	
	rep(x,0,n){
		while (!v.empty() && v.back().time==x){
			arr[v.back().pos]+=v.back().val;
			v.pob();
		}
		
		rep(y,0,q){
			ans[n-x-1]+=arr[y+x+1]*brr[y];
		}
	}
	
	rep(x,0,n) cout<<ans[x]<<endl;
}
