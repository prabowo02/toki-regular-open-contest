/*
	Solution complexity: O(sqrt(M log (M)) log(M)) with M = 1000000007
	Relatively slower than solution.cpp
	Relatively easier to code than solution.cpp
*/
#include <cstdio>
#include <set>

const int mod=1000000007;
int modex(int b, int e){
	int h = 1;
	while(e){
		if(e&1)h=(long long)b*h%mod;
		b=(long long)b*b%mod;
		e>>=1;
	}
	return h;
}
int operation1(int x){
	return (x+2019)%mod;
}
int reverse1(int x){
	return (x+mod-2019)%mod;
}
int operation2(int x){
	return (x*2020ll)%mod;
}
int inv2020=modex(2020, mod-2);
int reverse2(int x){
	return ((long long)x*inv2020)%mod;
}
int operation3(int x){
	return modex(x, 2021);
}
int reverse3(int x){
	return modex(x, 143493321);
}
int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	int ans=mod;
	if(a%2019==b%2019&&a<=b){
		ans=std::min(ans, (b-a)/2019);
		if(a*2020ll<=b){
			ans=std::min(ans, 1+(b-a*2020)/(2020*2019)+(b-a*2020)%(2020*2019)/2019);
			if(a*2020ll*2020ll<=b){
				ans=std::min(ans, 2+(b-a*2020*2020)/(2020*2019)+(b-a*2020*2020)%(2020*2019)/2019);
			}
		}
	}
	std::set <int> possible_a, possible_b;
	possible_a.insert(a);
	possible_b.insert(b);
	for(int i = 2;i<ans;i++){
		if(i&1){
			std::set <int> rep;
			for(std::set <int>::iterator it=possible_a.begin();it != possible_a.end();++it){
				rep.insert(operation1(*it));
				rep.insert(operation2(*it));
				rep.insert(operation3(*it));
			}
			swap(rep, possible_a);
		}else{
			std::set <int> rep;
			for(std::set <int>::iterator it=possible_b.begin();it != possible_b.end();++it){
				rep.insert(reverse1(*it));
				rep.insert(reverse2(*it));
				rep.insert(reverse3(*it));
			}
			swap(rep, possible_b);
		}
		for(std::set <int>::iterator it=possible_b.begin();it != possible_b.end();++it){
			if(possible_a.count(*it)){
				ans=i;
				break;
			}
		}
	}
	printf("%d\n", ans);
}