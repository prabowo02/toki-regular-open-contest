#include <algorithm>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
	vector<vector<int>> A;
	vector<int> B;

	long long ANS;

	void InputFormat() {
		LINE(N, M);
		GRID(A) % SIZE(N, M);
		LINE(B % SIZE(M));
	}

	void OutputFormat() {
		LINE(ANS);
	}

	void Constraints() {
		CONS(1 <= N && N <= MAX_N);
		CONS(1 <= M && M <= MAX_M);
		CONS(isGridValid(A, N, M, 1, MAX_VAL));
		CONS(isArrayValid(B, M, 1, MAX_VAL));
	}

	void Subtask1() {
		Points(100);
	}

	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(512);
	}

	/*
	void StyleConfig() {
		CustomScorer();
	}
	*/

private:
	const int MAX_N = 1e5;
	const int MAX_M = 16;
	const int MAX_VAL = 1e9;

	bool isGridValid(const vector<vector<int>>& X, int row, int col, int lo, int hi) {
		if (X.size() != row) return false;
		for (auto xx : X) {
			if (xx.size() != col) return false;
			for (auto x : xx) {
				if (x < lo || x > hi) {
					return false;
				}
			}
		}
		return true;
	}

	bool isArrayValid(const vector<int>& X, int size, int lo, int hi) {
		if (X.size() != size) return false;
		for (auto x : X) {
			if (x < lo || x > hi) {
				return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({ 1 });
		Input({
			"2 3",
			"1 1 2",
			"1 3 5",
			"5 1 1"
			});
		Output({
			"5"
			// ,"2 2"
			});
	}

	void SampleTestCase2() {
		Subtasks({ 1 });
		Input({
			"5 5",
			"7 5 5 5 1",
			"6 4 1 1 5",
			"1 5 4 2 5",
			"3 4 5 2 1",
			"8 2 5 4 2",
			"8 8 2 1 3"
			});
		Output({
			"11"
			// , "5 4 4 5 5"
			});
	}

	void TestGroup1() {
		Subtasks({ 1 });

		// handmade
		CASE(N = 5, M = 5,
			A = {	{2, 4, 2, 3, 2},
					{2, 2, 3, 3, 3},
					{2, 3, 1, 2, 1},
					{2, 4, 1, 2, 2},
					{2, 1, 3, 2, 4} },
			B =		{3, 2, 3, 1, 2}
		);

		// max tests (5)
		CASE(N = 1, M = 1, A = { {1} }, B = { 1 });
		CASE(N = 1, M = 1, A = { {MAX_VAL} }, B = { MAX_VAL });
		CASE(N = 1, M = MAX_M, generateRandom({ MAX_VAL, MAX_VAL }, { MAX_VAL, MAX_VAL }));
		CASE(N = MAX_N, M = 1, generateRandom({ MAX_VAL, MAX_VAL }, { MAX_VAL, MAX_VAL }));
		CASE(N = MAX_N, M = MAX_M, generateRandom({ MAX_VAL, MAX_VAL }, { MAX_VAL, MAX_VAL }));

		// fully randomized (4)
		CASE(N = 10, M = 5, generateRandom({ 1, 3 }, { 1, 3 }));
		CASE(N = 10, M = 8, generateRandom({ 1, 3 }, { 30, 50 }));
		CASE(N = 50095, M = MAX_M, generateRandom({ 1, 1000000 }, { 1000, 1000000000 }));
		CASE(N = MAX_N, M = MAX_M, generateRandom({ MAX_VAL / 1000000, MAX_VAL / 100000 }, { MAX_VAL / 1000, MAX_VAL }));

		// random + partition (7)
		CASE(N = MAX_N, M = MAX_M, generateRandomWithPartitions({ {1, 1000}, {500, 2000}, {1500, 4000} }, { {1000, 5000}, {4000, 8000}, {5000, 10000} }, generatePartition(3, {})));
		for (int i = 3; i <= MAX_M; i += 6) {
			CASE(N = MAX_N, M = MAX_M, generateRandomWithPartitions(generateRanges(i, 1, 1000, 0.8), generateRanges(i, 1000, 100000, 0.3), generatePartition(i, {})));
			CASE(N = MAX_N, M = MAX_M, generateRandomWithPartitions(generateRanges(i, 1, 1000000, 0.6), generateRanges(i, 300000000, MAX_VAL, 0.3), generatePartition(i, {})));
		}

		// random + antiGreedy (16)
		for (int i = 4; i <= MAX_M; i += 4) {
			CASE(N = MAX_N, M = MAX_M, generateRandomAntiGreedy({ 2, 3 }, { 200000, 200001 }, 1, 1, i));
			CASE(N = MAX_N, M = MAX_M, generateRandomAntiGreedy({ 1, 1000 }, { 1, 100000 }, 10, 1, i));
			CASE(N = MAX_N, M = MAX_M, generateRandomAntiGreedy({ 1, 1000000 }, { 100000000, MAX_VAL }, 100000, 10000, i));
			CASE(N = MAX_N, M = MAX_M, generateRandomAntiGreedy({ 1, MAX_VAL }, { 300000000, MAX_VAL }, 100000000, 1000000, i));
		}
		
		// permutation
		CASE(N = 5, M = 5, generatePermutation());
		CASE(N = MAX_N, M = MAX_M, generatePermutation());
	}

	void BeforeTestCase() {
		A.clear();
		B.clear();
	}

	void AfterTestCase() {
		for (int i = 1; i < N; i++) {
			int p = rnd.nextInt(0, i);
			for (int j = 0; j < M; j++) {
				int tmp = A[i][j];
				A[i][j] = A[p][j];
				A[p][j] = tmp;
			}
		}

		for (int j = 1; j < M; j++) {
			int p = rnd.nextInt(0, j);
			for (int i = 0; i < N; i++) {
				int tmp = A[i][j];
				A[i][j] = A[i][p];
				A[i][p] = tmp;
			}
			int tmp = B[j];
			B[j] = B[p];
			B[p] = tmp;
		}
	}

private:
	const int MAX_N = 1e5;
	const int MAX_M = 16;
	const int MAX_VAL = 1e9;

	// fully randomized
	void generateRandom(pair<int,int> rangeA, pair<int,int> rangeB) {
		A = vector<vector<int>>(N, vector<int>(M));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				A[i][j] = rnd.nextInt(rangeA.first, rangeA.second);
			}
		}

		B = vector<int>(M);
		for (int j = 0; j < M; j++) {
			B[j] = rnd.nextInt(rangeB.first, rangeB.second);
		}
	}

	// sorting the sum of A[i][j] plus B[j] for a store j then greedily taking the stores
	void generateRandomAntiGreedy(pair<int,int> rangeA, pair<int,int> rangeB, int add, int sub, int num_chosen) {
		A = vector<vector<int>>(N, vector<int>(M));
		for (int i = 0; i < N; i++) {
			int minA = 1e9;
			for (int j = 0; j < num_chosen; j++) {
				if (j == 0) A[i][j] = rnd.nextInt(rangeA.first, rangeA.second);
				else A[i][j] = min(MAX_VAL, A[i][j - 1] + rnd.nextInt(0, add));
				minA = min(minA, A[i][j]);
			}
			rnd.shuffle(A[i].begin(), A[i].begin() + num_chosen);
			
			for (int j = num_chosen; j < M; j++) {
				if (j == num_chosen) A[i][j] = max(1, min(MAX_VAL, minA + rnd.nextInt(-sub, add)));
				else A[i][j] = max(1, min(MAX_VAL, A[i][j - 1] + rnd.nextInt(0, add)));
			}
			rnd.shuffle(A[i].begin() + num_chosen, A[i].end());
		}

		B = vector<int>(M);
		int minB = 1e9;
		for (int j = 0; j < num_chosen; j++) {
			B[j] = rnd.nextInt(rangeB.first, rangeB.second);
			minB = min(minB, B[j]);
		}
		for (int j = num_chosen; j < M; j++) {
			B[j] = min(1, max(MAX_VAL, minB + rnd.nextInt(-rangeB.first, rangeB.second)));
		}
		rnd.shuffle(B.begin() + num_chosen, B.end());
	}

	// a set of shops has lower expected price than other set(s) of shops
	void generateRandomWithPartitions(vector<pair<int,int>> rangeA, vector<pair<int,int>> rangeB, vector<int> partition) {
		int p_num = partition.size();
		vector<int> par(M);
		for (int p = 0, i = 0; p < p_num; p++) {
			int j = i + partition[p];
			while (i < j) {
				par[i] = p;
				i++;
			}
		}

		A = vector<vector<int>>(N, vector<int>(M));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				A[i][j] = rnd.nextInt(rangeA[par[j]].first, rangeA[par[j]].second);
			}
		}
		
		B = vector<int>(M);
		for (int j = 0; j < M; j++) {
			B[j] = rnd.nextInt(rangeB[par[j]].first, rangeB[par[j]].second);
		}
	}

	// generate partition for RandomWithPartitions
	vector<int> generatePartition(int partition_num, vector<int> partition) {
		int m = M;
		for (int i = 0; i < partition.size(); i++) m -= partition[i];
		
		int partition_next_num = partition_num - partition.size();
		vector<int> partition_next;
		for (int i = 0; i < partition_next_num; i++) {
			int cur_partition = rnd.nextInt(1, m - (partition_next_num - i - 1));
			partition_next.push_back(cur_partition);
			m -= cur_partition;
		}

		rnd.shuffle(partition_next.begin(), partition_next.end());
		for (int i = 0; i < partition_next_num; i++) {
			partition.push_back(partition_next[i]);
		}
		return partition;
	}

	// generate range for RandomWithPartitions. overlap [0, 1] indicates where the range start based on the previous range.
	vector<pair<int,int>> generateRanges(int partition_num, int start, int add, double overlap = 1.0) {
		vector<pair<int, int>> range;
		for (int i = 0; i < partition_num; i++) {
			if (i == 0) range.push_back({ start, min(start + add, MAX_VAL) });
			else {
				int start_now = range[i - 1].first + floor((range[i - 1].second - range[i - 1].first) * overlap);
				range.push_back({ start_now, min(start_now + add, MAX_VAL) });
			}
		}
		return range;
	}

	void generatePermutation() {
		A = vector<vector<int>>(N, vector<int>(M));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				A[i][j] = j + 1;
			}
			rnd.shuffle(A[i].begin(), A[i].end());
		}
		B = vector<int>(M);
		for (int j = 0; j < M; j++) {
			B[j] = j + 1;
		}
		rnd.shuffle(B.begin(), B.end());
	}
};