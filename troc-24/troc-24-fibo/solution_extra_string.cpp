#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ii pair<ll,ll>
#define fi first
#define se second
 
#define puf push_front
#define pof pop_front
#define pub push_back
#define pob pop_back
 
#define rep(x,s,e) for (auto x=s-(s>e);x!=e-(s>e);s<e?x++:x--)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int) (x).size()

vector<string> ans;

void add_copy(int a,int b){
	ans.pub(to_string(a)+"="+to_string(b));
}

void add_not(int a,int b){
	ans.pub(to_string(a)+"=~"+to_string(b));
}

void add_and(int a,int b,int c){
	ans.pub(to_string(a)+"="+to_string(b)+"&"+to_string(c));
}

void add_or(int a,int b,int c){
	ans.pub(to_string(a)+"="+to_string(b)+"|"+to_string(c));
}

void add_xor(int a,int b,int c){
	ans.pub(to_string(a)+"="+to_string(b)+"^"+to_string(c));
}

void add_left(int a,int b,int c){
	ans.pub(to_string(a)+"="+to_string(b)+"<<"+to_string(c));
}

void add_right(int a,int b,int c){
	ans.pub(to_string(a)+"="+to_string(b)+">>"+to_string(c));
}

void add_print(int a){
	ans.pub("."+to_string(a));
}

int main(){
	//create 100...000 at register 99
	add_or(99,0,1);
	for (auto &it:{1,2,4,8}){
		add_right(98,99,it);
		add_or(99,98,99);
	}
	add_left(98,99,1);
	add_and(98,98,99);
	add_xor(99,99,98);
	
	add_print(99); //100...000
	add_not(98,99);
	
	rep(x,0,5){
		add_right(2,0,1);
		add_right(3,0,2);
		add_not(3,3);
		add_and(4,0,2);
		add_and(5,4,3);
		add_left(2,5,1);
		add_left(3,5,2);
		add_xor(0,0,2);
		add_xor(0,0,3);
		add_xor(0,0,5);
	}
	
	//change base to 0,1,1,2,...
	add_left(0,0,2);
	add_left(1,1,2);
	
	rep(x,12,2){
		add_and(0,0,98);
		add_left(69,99,x);
		
		add_and(2,1,69); //do we have to add this current bit to 0
		add_and(10,0,2); //if we have to do doubling operation
		
		add_or(0,0,2); //we are done if dont need doubling
		
		//now we do doubling operation
		//we build 10101010101 mask at 10
		//we build 111111111111 mask at 11
		
		rep(x,1,4){
			add_right(11,10,1<<x);
			add_or(10,10,11);
		}
		add_left(11,10,1);
		add_or(11,10,11);
		
		add_not(4,0);
		add_and(4,4,10);
		
		//propogate reg 4
		rep(x,0,4){
			add_right(5,4,1<<x);
			add_or(4,4,5);
		}
		
		add_left(5,4,1);
		add_xor(5,5,4);
		add_right(4,4,1);
		
		add_xor(0,0,4);
		add_xor(0,0,5);
		add_xor(0,0,11);
		
		if (x%2==1) add_or(0,0,99); //we force the 0-bit to be flipped
		
		//change this later
		add_right(2,0,1);
		add_right(3,0,2);
		add_not(3,3);
		add_and(4,0,2);
		add_and(5,4,3);
		add_left(2,5,1);
		add_left(3,5,2);
		add_xor(0,0,2);
		add_xor(0,0,3);
		add_xor(0,0,5);
	}
	
	add_right(2,0,2);
	
	cout<<sz(ans)<<endl;
	for (auto &it:ans) cout<<it<<endl;
	cout<<"super idol de xiao rong dou mei ni de tian"<<endl;
}
