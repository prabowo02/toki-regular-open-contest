#include<bits/stdc++.h>
#include<tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

const int mxs=100;

class ProblemSpec : public BaseProblemSpec{
	protected:
		int n;
		string s;

		string ans;

		void InputFormat(){
			LINE(n);
			LINE(s);
		}
		void OutputFormat(){
			LINE(ans);
		}

		void GradingConfig(){
			TimeLimit(1);
			MemoryLimit(64);
		}

		void Constraints(){
			CONS(1<=n && n<=100);
			CONS(is_lower(s));
			CONS(s.size() == n);
		}

		void Subtask1(){
			Points(100);
		}
  private:
    bool is_lower(string t) {
      for (auto i : t) {
        if ('a' <= i && i <= 'z') {
          continue;
        }
        return false;
      }
      return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
	protected:
		void SampleTestCase1(){
			Subtasks({1});
			Input({
				"6",
				"aaabba",
			});
			Output({
				"aba",
			});
		}
		void SampleTestCase2(){
			Subtasks({1});
			Input({
				"8",
				"xiimaaaa",
			});
			Output({
				"xima",
			});
		}

		void TestGroup1(){
			Subtasks({1});

			//gibberish
			CASE(n=17; s="maximathtzaphnoob";);
			CASE(n=16; s="stevennovaryoorz";);
			CASE(n=17; s="raaamaaapaaangorz";);
			CASE(n=18; s="hhocccckkyyyyyyorz";);
			CASE(n=21; s="prabowoowoorztokiboss";);
			CASE(n=31; s="kuyjoindiscordservercpindonesia";); //no compression

			//a sebanyak 1, b sebanyak 2, c sebanyak 3, ...
			CASE(n=91; s="abbcccddddeeeeeffffffggggggghhhhhhhhiiiiiiiiijjjjjjjjjjkkkkkkkkkkkllllllllllllmmmmmmmmmmmmm";); 
			//max all same
			CASE(n=mxs; s="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";);
			//max alternating
			CASE(n=mxs; s=alt(n););
			//max alternating each segment random size
			CASE(n=mxs; s=altrnd(n););
			//max palindrome from alternating random
			CASE(n=mxs; s=palin(n););
		}

	private:
		string alt(int n){
			string ss="";
			for(int i=0; i<n; i++)
				if(i&1) ss+='m';
				else ss+='n';
			return ss;
		}
		string altrnd(int n){
			string ss="";
			int id=0; bool isA=true;
			while(id<n-7){
				int cnt=rnd.nextInt(1, 7);
				for(int i=0; i<cnt; i++)
					if(isA) ss+='p';
					else ss+='q';
				id+=cnt;
				isA=!isA;
			}
			for(int i=id; i<n; i++)
				if(isA) ss+='p';
				else ss+='q';
			return ss;
		}
		string palin(int n){
			string ss="";
			string nw=altrnd(n/2);
			ss+=nw;
			if(n&1) ss+='x';
			reverse(nw.begin(), nw.end());
			ss+=nw;
			return ss;
		}
};
