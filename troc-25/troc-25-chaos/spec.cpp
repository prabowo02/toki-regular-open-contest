#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MXN = 100000;
const int MXA = 1000000000;

class ProblemSpec : public BaseProblemSpec{
protected:
	int N;
	vector<int> A;

	std::string ans;

	void InputFormat(){
		LINE(N);
		LINE(A % SIZE(N));
	}
	void OutputFormat(){
		LINE(ans);
	}

	void GradingConfig(){
		TimeLimit(2);
		MemoryLimit(256);
	}

	void Constraints(){
		CONS(1 <= N && N <= MXN);
		CONS(eachElementBetween(A, 0, MXA));
	}

	void Subtask1(){
		Points(100);
	}

private:
	bool eachElementBetween(vector<int> A, int lf, int rg){
		for(int i : A)
			if(!(lf <= i && i <= rg))
				return false;
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"4",
			"2 1 5 4",
		});
		Output({
			"YES",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"3",
			"1 0 5",
		});
		Output({
			"NO",
		});
	}
	void SampleTestCase3(){
		Subtasks({1});
		Input({
			"8",
			"420 727 69 1 69 0 1023 69",
		});
		Output({
			"YES",
		});
	}

	void BeforeTestCase(){
		A.clear();
	}

	void TestGroup1(){
		Subtasks({1});

		CASE(N = 1, A = vector<int>(1, 69));

		CASE(N = MXN, A = pureRandom(N));
		CASE(N = MXN, A = pureRandom(N));
		CASE(N = rnd.nextInt(1, MXN), A = pureRandom(N)); 
		
		CASE(N = 1, A = vector<int>(N, 0)); 
		CASE(N = MXN, A = vector<int>(N, 0)); 

		CASE(N = MXN, A = binary_array(N, 0, 0)); 
		CASE(N = MXN, A = binary_array(N, 1, 0)); 
		CASE(N = MXN, A = binary_array(N, 1, 1)); 

		CASE(N = MXN, A = exponential(N, 0)); 
		CASE(N = rnd.nextInt(1001, MXN), A = exponential(N, 1)); 
		CASE(N = MXN, A = exponential_random(N, 0)); 
		CASE(N = rnd.nextInt(1001, MXN), A = exponential_random(N, 1)); 
		CASE(N = MXN, A = exponential_random(N, 1));
		CASE(N = rnd.nextInt(1001, MXN), A = exponential_random(N, 0));

		CASE(N = MXN, A = maxedR(N, MXA, 1));
		CASE(N = MXN, A = maxedR(N, MXA, 0));
		CASE(N = MXN, A = maxedR(N, rnd.nextInt(MXA / 10, MXA), 0)); 
		CASE(N = rnd.nextInt(1001, MXN), A = maxedR(N, rnd.nextInt(MXA / 10, MXA), 1));
		CASE(N = MXN, A = maxedR2(N, MXA, 1));
		CASE(N = rnd.nextInt(1001, MXN), A = maxedR2(N, rnd.nextInt(MXA / 10, MXA), 0));
	}

private:
	vector<int> pureRandom(int N){
		vector<int> res;
		for(int i = 0; i < N; i ++)
			res.push_back(rnd.nextInt(0, MXA));
		return res;
	}

	vector<int> binary_array(int N, int e0, int e1){
		vector<int> res = {e0, e1};
		for(int i = 2; i < N; i ++)
			res.push_back(rnd.nextInt(0, 1));
		return res;
	}

	vector<int> exponential(int N, int ys){
		vector<int> res = {};
		int st = rnd.nextInt(1, 5);
		res.push_back(st);

		long long L = 0; bool done = 0; int idL = -1;
		for(int i = 1; i < N; i ++){
			if(!done && L <= MXA) L += res.back() + 1;
			if(!done && L <= MXA) res.push_back(L + rnd.nextInt(1, 10005));
			else{
				if(!done){
					done = 1; L = res.back();
					idL = i;
					if(ys) L += MXA * (long long)rnd.nextInt(60, 100);
					else L = L / 2 - 727420ll;
				}
				
				priority_queue<long long> pq; pq.push(L);
				int tmpi = i;
				for(; i < N; i ++){
					long long top = pq.top(); pq.pop();
					long long get = rnd.nextLongLong(0, top);
					pq.push(get); pq.push(top - get);
				}

				for(i = tmpi; i < N; i ++){
					res.push_back(min((long long)MXA, pq.top()));
					pq.pop();
				}

				rnd.shuffle(res.begin() + tmpi + 1, res.end());
			}
		}

		return res;
	}

	vector<int> exponential_random(int N, int ys){
		vector<int> res = {};
		int st = rnd.nextInt(1, 100);
		res.push_back(st);

		long long L = 0; bool done = 0; int idL = -1;
		for(int i = 1; i < N; i ++){
			if(!done && L <= MXA) L += res.back() + 1;
			if(!done && L <= MXA){
				int get = rnd.nextInt(1, 150);
				if(get <= 100)
					res.push_back(get);
				else
					res.push_back(L + rnd.nextInt(1, 10005));
			}else{
				if(!done){
					done = 1;
					idL = i;
					if(ys) L = MXA * (long long)rnd.nextInt(60, 100);
					else{
						L -= res.back() + 1;
						L = res.back() - L - 1;
					}
				}
				
				priority_queue<long long> pq; pq.push(L);
				int tmpi = i;
				for(; i < N; i ++){
					long long top = pq.top(); pq.pop();
					long long get = rnd.nextLongLong(0, top);
					pq.push(get); pq.push(top - get);
				}

				for(i = tmpi; i < N; i ++){
					res.push_back(min((long long)MXA, pq.top()));
					pq.pop();
				}

				rnd.shuffle(res.begin() + tmpi + 1, res.end());
			}
		}
		return res;
	}

	vector<int> maxedR(int N, int A1, int ys){
		vector<int> res = {A1};
		long long L = A1;
		if(ys) L *= (long long)rnd.nextInt(60, 100);
		else L -= 3;
		priority_queue<long long> pq; pq.push(L);
		for(int i = 0; i < N; i ++){
			long long top = pq.top(); pq.pop();
			long long get = rnd.nextLongLong(0, top);
			pq.push(get); pq.push(top - get);
		}

		for(int i = 1; i < N; i ++){
			res.push_back(min((long long)MXA, pq.top()));
			pq.pop();
		}
		rnd.shuffle(res.begin() + 1, res.end());
		return res;
	}

	vector<int> maxedR2(int N, int A2, int ys){
		int A1 = rnd.nextInt(0, A2 / 10);
		vector<int> res = {A1, A2};
		long long L = A2 - (A1 + 1);
		if(ys) L *= (long long)rnd.nextInt(60, 100);
		else L -= 3;
		priority_queue<long long> pq; pq.push(L);
		for(int i = 0; i < N; i ++){
			long long top = pq.top(); pq.pop();
			long long get = rnd.nextLongLong(0, top);
			pq.push(get); pq.push(top - get);
		}

		for(int i = 2; i < N; i ++){
			res.push_back(min((long long)MXA, pq.top()));
			pq.pop();
		}
		rnd.shuffle(res.begin() + 2, res.end());
		return res;
	}
};
