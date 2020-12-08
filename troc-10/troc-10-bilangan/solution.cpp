/*
	Solution complexity: O(sqrt(M log (M)) log(M)) with M = 1000000007
*/
#include <cstdio>
#include <vector>
#include <algorithm>

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
	/*
		number can be obtained by noticing that
		2021 is relatively prime to 10^9+6, then
		executing:
		for(int i = 0;;i ++){
			if(i*2021ll%1000000006==1){
				printf("%d\n", i);
				return 0;
			}
		}
		One may also use the extended Euclid if
		they so choose.
	*/
}
int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	int ans=mod;
	//without modulo
	if(a%2019==b%2019&&a<=b){
		//additions only
		ans=std::min(ans, (b-a)/2019);
		if(a*2020ll<=b){
			//additions + 1 multiplication
			ans=std::min(ans, 1+(b-a*2020)/(2020*2019)+(b-a*2020)%(2020*2019)/2019);
			if(a*2020ll*2020ll<=b){
				//additions + 2 multiplications
				ans=std::min(ans, 2+(b-a*2020*2020)/(2020*2019)+(b-a*2020*2020)%(2020*2019)/2019);
			}
		}
	}
	//with modulo
	std::vector <int> possible_a, possible_b;
	possible_a.push_back(a);
	possible_b.push_back(b);
	for(int i = 2;i<ans;i++){
		if(possible_a.size()<possible_b.size()){
			std::vector <int> rep;
			for(int i = 0;i < possible_a.size();i ++){
				rep.push_back(operation1(possible_a[i]));
				rep.push_back(operation2(possible_a[i]));
				rep.push_back(operation3(possible_a[i]));
			}
			sort(rep.begin(), rep.end());
			rep.resize(unique(rep.begin(), rep.end())-rep.begin());
			swap(rep, possible_a);
		}else{
			std::vector <int> rep;
			for(int i = 0;i < possible_b.size();i ++){
				rep.push_back(reverse1(possible_b[i]));
				rep.push_back(reverse2(possible_b[i]));
				rep.push_back(reverse3(possible_b[i]));
			}
			sort(rep.begin(), rep.end());
			rep.resize(unique(rep.begin(), rep.end())-rep.begin());
			swap(rep, possible_b);
		}
		for(int j = 0, k = 0;j < possible_a.size() && k < possible_b.size();){
			if(possible_a[j]<possible_b[k]){
				j++;
			}else if(possible_a[j]>possible_b[k]){
				k++;
			}else{
				ans=i;
				break;
			}
		}
	}
	printf("%d\n", ans);
}