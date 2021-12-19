#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MX 100

class ProblemSpec : public BaseProblemSpec {
	protected:
		int N;
		vector<int> A, B;
		int ans;

		void InputFormat() {
			LINE(N);
			LINE(A % SIZE(N));
			LINE(B % SIZE(N));
		}

		void OutputFormat() {
			LINE(ans);
		}

		void GradingConfig() {
			TimeLimit(1);
			MemoryLimit(256);
		}

		void Constraints() {
			CONS(1 <= N && N <= MX);
			CONS(isPerm(A));
			CONS(isPerm(B));
		}
	
	private:
		bool isPerm(vector<int> v) {
			vector<int> occ(v.size() + 5, 0);
			for (int i : v) {
				occ[i]++;
			}
			for (int i = 1; i <= v.size(); i++) {
				if (occ[i] != 1) {
					return 0;
				}
			}
			return 1;
		}
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
	protected:
		void SampleTestCase1() {
			Input({
					"5",
					"1 2 3 4 5",
					"5 2 3 1 4"
					});

			Output({"2"});
		}

		void TestGroup1() {
			CASE(N = 1, A = {1}, B = {1});

			for (int i = 0; i < 2; i++) {
				CASE(random());
			}

			for (int i = 0; i < 2; i++) {
				CASE(randomCollide(MX));
			}

			for (int i = 0; i < 2; i++) {
				CASE(randomCollide(0));
			}

			for (int i = 0; i < 3; i++) {
				int x = rnd.nextInt(MX) + 1;
				CASE(randomCollide(x));
			}
		}

	private:
		void random() {
			N = max(rnd.nextInt(MX), max(rnd.nextInt(MX), rnd.nextInt(MX))) + 1;
			A.resize(N, 0);
			B.resize(N, 0);
			for (int i = 0; i < N; i++) {
				A[i] = B[i] = i + 1;
			}
			rnd.shuffle(A.begin(), A.end());
			rnd.shuffle(B.begin(), B.end());
		}

		void randomCollide(int x) {
			N = MX;
			A.resize(N, 0);
			B.resize(N, 0);
			vector<int> id(N, 0), v(N, 0);
			for (int i = 0; i < N; i++) {
				id[i] = i;
				v[i] = i + 1;
			}
			rnd.shuffle(id.begin(), id.end());
			rnd.shuffle(v.begin(), v.end());
			for (int i = 0; i < x; i++) {
				A[id[i]] = B[id[i]] = v[i];
			}
			vector<int> tv = v;
			rnd.shuffle(tv.begin() + x, tv.end());
			for (int i = x; i < N; i++) {
				A[id[i]] = v[i];
				if (i != N - 1 && tv[i] == v[i]) {
					swap(tv[i], tv[i + 1]);
				}
				B[id[i]] = tv[i];
			}
		}
};
