#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MX 200000

class ProblemSpec : public BaseProblemSpec {
	protected:
		int T;
		vector<int> N, M, ans;

		void InputFormat() {
			LINE(T);
			LINES(N, M) % SIZE(T);
		}

		void OutputFormat() {
			LINES(ans) % SIZE(T);
		}

		void GradingConfig() {
			TimeLimit(1);
			MemoryLimit(256);
		}

		void Constraints() {
			CONS(1 <= T && T <= 10000);
			CONS(allGood());
		}

	private:
		bool allGood() {
			for (int i = 0; i < T; i++) {
				if (N[i] > M[i]) {
					return 0;
				}
				if (M[i] > MX) {
					return 0;
				}
				if (N[i] < 0) {
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
					"2",
					"4 6",
					"69 420"
					});

			Output({
					"11",
					"440614405"
					});
		}

		void TestGroup1() {
			CASE(genAll1());
		}

		void TestGroup2() {
			CASE(genAll2());
		}

	private:
		void genAll1() {
			N.clear(); M.clear();
			for (int i = 3; i <= 140; i++) {
				for (int j = i; j <= 140; j++) {
					N.push_back(i); M.push_back(j);
				}
			}
			T = N.size();
		}
		void genAll2() {
			N.clear(); M.clear();
			for (int i = 0; i < 2000; i++) {
				random();
			}
			N.push_back(MX); M.push_back(MX);
			N.push_back(MX / 2); M.push_back(MX);

			for (int i = 0; i < 2000; i++) {
				randomSkew();
			}

			for (int i = 0; i < 2000; i++) {
				N.push_back(3); M.push_back(rnd.nextInt(3, MX));
			}

			for (int i = 3; i <= 50; i++) {
				for (int j = i; j <= 50; j++) {
					int a = i, b = j;
					if (a > 25) {
						a = MX - (50 - a);
					}
					if (b > 25) {
						b = MX - (50 - b);
					}
					N.push_back(a); M.push_back(b);
				}
			}
			T = N.size();
		}

		void random() {
			int n = rnd.nextInt(3, MX), m = rnd.nextInt(3, MX);
			if (n > m) swap(n, m);
			N.push_back(n); M.push_back(m);
		}

		void randomSkew() {
			int n = min(rnd.nextInt(3, MX / 2), rnd.nextInt(3, MX / 2));
			int m = max(rnd.nextInt(MX / 2, MX), rnd.nextInt(MX / 2, MX));
			N.push_back(n); M.push_back(m);
		}
};
