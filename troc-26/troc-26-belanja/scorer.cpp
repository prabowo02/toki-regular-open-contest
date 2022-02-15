// unused

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void WA(string reason) {
	cout << "WA" << endl;
	exit(0);
}

void AC() {
	cout << "AC" << endl;
	exit(0);
}

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ifstream tc_in(argv[1]);
	ifstream tc_out(argv[2]);
	ifstream con_out(argv[3]);

	int N, M;
	tc_in >> N >> M;
	long long judge_answer_total, con_answer_total;
	tc_out >> judge_answer_total;
	if (!(con_out >> con_answer_total)) WA("Invalid output format");
	
	long long judge_answer = 0, con_answer = 0;
	vector<bool> judge_shop(M), con_shop(M);

	for (int i = 0; i < N; i++) {
		int judge_index, con_index;
		tc_out >> judge_index;
		if (!(con_out >> con_index)) WA("Invalid output format");
		if (con_index < 1 || con_index > M) WA("Invalid shop index");

		for (int j = 0; j < M; j++) {
			int price;
			tc_in >> price;
			if (j + 1 == judge_index) {
				judge_answer += price;
				judge_shop[j] = true;
			}
			if (j + 1 == con_index) {
				con_answer += price;
				con_shop[j] = true;
			}
		}
	}

	string eof;
	if (con_out >> eof) {
		WA("Invalid output format");
	}

	for (int j = 0; j < M; j++) {
		int price;
		tc_in >> price;
		if (judge_shop[j]) judge_answer += price;
		if (con_shop[j]) con_answer += price;
	}
	
	if (judge_answer < con_answer || con_answer_total != con_answer) WA("Wrong answer");
	else {
		assert(judge_answer_total == judge_answer && judge_answer == con_answer);
		AC();
	}
}
