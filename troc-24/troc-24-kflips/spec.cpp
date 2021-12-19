#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MX 2000

class ProblemSpec : public BaseProblemSpec {
	protected:
		int n,k;
		string s;
		
		int ans;

		void InputFormat() {
			LINE(n,k);
			LINE(s);
		}

		void OutputFormat() {
			LINE(ans);
		}

		void GradingConfig() {
			TimeLimit(1);
			MemoryLimit(256);
		}

		void Constraints() {
			CONS(1 <= k && k<=n && n <= MX);
			CONS(s.size()==n);
			CONS(isBinaryString(s));
		}
	
	private:
	    bool isBinaryString(string s){
			for (auto it:s) if (it<'0' || '1'<it) return false;
			return true;
		}
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
  protected:
	void SampleTestCase1() {
		Input({
			"10 2",
			"1111010001"
		});

		Output({"9"});
	}

	void SampleTestCase2() {
		Input({
			"3 3",
			"011"
		});
		Output({"0"});
	}
	
	void SampleTestCase3() {
		Input({
			"3 1",
			"100"
		});
		Output({"0"});
	}

	void TestGroup1() {
		//corner cases for greedy
		CASE(n=6,k=2,s="110010");
		CASE(n=6,k=2,s="101100");
		
		
		//random case
		for (int x=1;x<MX;x*=10){
			CASE(n=MX,k=x,s=genRandomString(n));
		}
		
		//anti scams
		CASE(genAntiScam(369));
		CASE(genAntiScam(420));
		CASE(genAntiScam(MX));
		CASE(genAntiScam(MX));
		CASE(genAntiScam(MX));
		
		//small k
		for (int x=0;x<5;x++){
			int w=rnd.nextInt(1,50);
			CASE(n=MX,k=rnd.nextInt(1,w),s=genFlip(MX,w));
		}
		
		//gen large k
		CASE(n=MX,k=MX,s=genRandomString(n));
		CASE(n=MX,k=MX/2,s=genRandomString(n));
		CASE(n=MX,k=MX/2-1,s=string(MX/2,'1')+string(MX/2,'0'));
		
		//large ans
		CASE(n=MX,k=1,s=string(MX/2,'1')+string(MX/2,'0'));
		CASE(n=MX-1,k=1,s=string(MX/2,'1')+string(MX/2-1,'0'));
		
		//n=k=1 case
		CASE(n=1,k=1,s="0");
		CASE(n=1,k=1,s="1");
	}
		
  private:
	string genRandomString(int n){
		string res;
		for (int x=0;x<n;x++){
			if (rnd.nextInt(2)) res+="0";
			else res+="1";
		}
		return res;
	}
	
	string genFlip(int n,int k){
		int part=rnd.nextInt(0,n);
		
		string res;
		for (int x=0;x<part;x++) res+="0";
		for (int x=0;x<n-part;x++) res+="1";
		
		vector<int> idx;
		for (int x=0;x<n;x++) idx.push_back(x);
		rnd.shuffle(idx.begin(),idx.end());
		
		for (int x=0;x<k;x++) res[idx[x]]^=1;
		
		return res;
	}
	
	int calc(int l,int r,string s){
		int cnt1=0;
		int res=0;
		
		for (int x=l;x<=r;x++){
			if (s[x]=='0') res+=cnt1;
			else cnt1++;
		}
		
		return res;
	}
	
	int solve1(int n,int k,string s){
		//intended solution
		
		int ans=1e9;
		for (int l=0;l<=n;l++){
			int used=0;
			for (int x=0;x<l;x++) if (s[x]=='1') used++;
			
			if (used>k) break;
			
			int r=n;
			while (r>l && (used!=k || s[r-1]!='0')){
				r--;
				if (s[r]=='0') used++;
			}
			
			//cout<<l<<" "<<r<<endl;
			ans=min(ans,calc(l,r-1,s));
		}
		
		return ans;
	}
	
	int solve2(int n,int k,string t){
		//rng scam solution
		
		string s;
		
		int ans=1e9;
		for (int zzz=0;zzz<1000;zzz++){
			s=t;
			int l=0,r=n-1;
			
			for (int x=0;x<k;x++){
				while (l<n && s[l]=='0') l++;
				while (r>=0 && s[r]=='1') r--;
				
				if (l>r) break;
				
				int cnt0=0,cnt1=0;
				for (int x=l;x<n;x++)if (s[x]=='0') cnt0++;
				for (int x=0;x<r;x++) if (s[x]=='1') cnt1++;
				
				if (cnt0==cnt1){
					if (rnd.nextInt(2)) cnt0++;
					else cnt0--;
				}
				
				if (cnt0>cnt1) s[l]='0';
				else s[r]='1';
			}
			
			ans=min(ans,calc(0,n-1,s));
		}
		
		return ans;
	}
		
	void genAntiScam(int __n){
		while (true){
			string __s;
			for (int x=0;x<__n;x++) __s+=('0'+rnd.nextInt(2));
			
			int __k=rnd.nextInt(1,__n);
			
			int v1=solve1(__n,__k,__s),v2=solve2(__n,__k,__s);
			
			if (v1!=v2){
				n=__n;
				k=__k;
				s=__s;
				break;
			}
		}
	}
};
