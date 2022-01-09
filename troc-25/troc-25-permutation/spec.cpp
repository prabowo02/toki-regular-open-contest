#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MXN = 300;

class ProblemSpec : public BaseProblemSpec{
protected:
	int N, K;
	vector<int> A;

	int ans;

	void InputFormat(){
		LINE(N, K);
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
		CONS(0 <= K && K <= MXN);
		CONS(isPermutation(N, A));
	}

	void Subtask1(){
		Points(100);
	}

private:
	bool isPermutation(int N, vector<int> A){
		sort(A.begin(), A.end());
		bool ok = 1;
		for(int i = 0; i < N; i ++)
			if(A[i] != i + 1) ok = 0;
		return ok;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"3 1",
			"1 2 3",
		});
		Output({
			"4",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"3 2",
			"1 2 3",
		});
		Output({
			"5",
		});
	}
	void SampleTestCase3(){
		Subtasks({1});
		Input({
			"3 2",
			"3 1 2",
		});
		Output({
			"4",
		});
	}
	void SampleTestCase4(){
		Subtasks({1});
		Input({
			"13 10",
			"9 4 8 11 6 2 5 12 10 7 1 3 13",
		});
		Output({
			"12772",
		});
	}

	void BeforeTestCase(){
		A.clear();
	}

	void TestGroup1(){
		Subtasks({1});

		CASE(N = 1, K = MXN, A = vector<int>(1, 1));
		CASE(N = MXN, K = 0, A = randomPermutation(N));
		CASE(N = MXN, K = MXN, A = randomPermutation(N));
		CASE(N = MXN, K = rnd.nextInt(0, MXN / 2), A = randomPermutation(N));
		CASE(N = MXN, K = rnd.nextInt(MXN / 2, MXN), A = randomPermutation(N));
		CASE(N = rnd.nextInt(MXN / 2, MXN), K = rnd.nextInt(0, MXN), A = randomPermutation(N));
		CASE(N = rnd.nextInt(1, MXN / 2), K = rnd.nextInt(0, MXN), A = randomPermutation(N));

		CASE(N = MXN, K = MXN, A = sorted(N));
		CASE(N = MXN, K = rnd.nextInt(MXN / 2, MXN), A = sorted(N));
		CASE(N = rnd.nextInt(MXN / 2, MXN), K = rnd.nextInt(0, MXN), A = sorted(N));
		CASE(N = MXN, K = MXN, A = reverse_sorted(N));
		CASE(N = MXN, K = rnd.nextInt(MXN / 2, MXN), A = reverse_sorted(N));
		CASE(N = rnd.nextInt(MXN / 2, MXN), K = rnd.nextInt(0, MXN), A = reverse_sorted(N));

		CASE(N = MXN, K = MXN, A = hill(N));
		CASE(N = MXN, K = MXN, A = valley(N));
		CASE(N = MXN, K = MXN, A = hill(N, 1));
		CASE(N = MXN, K = MXN, A = valley(N, 1));
		CASE(N = MXN, K = rnd.nextInt(MXN / 2, MXN), A = hill(N, 1));
		CASE(N = MXN, K = rnd.nextInt(MXN / 2, MXN), A = valley(N, 1));
	}

private:
	vector<int> randomPermutation(int N){
		vector<int> res(N);
		iota(res.begin(), res.end(), 1);
		rnd.shuffle(res.begin(), res.end());
		return res;
	}

	vector<int> sorted(int N){
		vector<int> res(N);
		iota(res.begin(), res.end(), 1);
		return res;
	}

	vector<int> reverse_sorted(int N){
		vector<int> res(N);
		iota(res.begin(), res.end(), 1);
		reverse(res.begin(), res.end());
		return res;
	}

	vector<int> hill(int N, int noise = 0){
		vector<int> A(N);
		for(int l = 0, r = N - 1, cnt = 1; cnt <= N; cnt ++){
			if(cnt & 1) A[l ++] = cnt;
			else A[r --] = cnt;
		}
		if(noise){
			int times = rnd.nextInt(0, N / 4);
			for(int i = 0; i < times; i ++){
				swap(A[rnd.nextInt(0, N - 1)], A[rnd.nextInt(0, N - 1)]);
			}
		}
		return A;
	}

	vector<int> valley(int N, int noise = 0){
		vector<int> A(N);
		for(int l = 0, r = N - 1, cnt = N; cnt >= 1; cnt --){
			if(cnt & 1) A[l ++] = cnt;
			else A[r --] = cnt;
		}
		if(noise){
			int times = rnd.nextInt(0, N / 4);
			for(int i = 0; i < times; i ++){
				swap(A[rnd.nextInt(0, N - 1)], A[rnd.nextInt(0, N - 1)]);
			}
		}
		return A;
	}
};