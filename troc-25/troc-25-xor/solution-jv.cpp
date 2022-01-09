#include <bits/stdc++.h>
using namespace std;

vector<int> find_all(const vector<int> &v, int K) 
{
  int N = v.size();
  int sum = 0;
  vector<int> ret;

  for(int i = 0; i < K; i++) 
  {
    sum += v[i];
  }

  ret.push_back(sum);
  for (int i = K; i < N; ++i) 
  {
    sum += v[i] - v[i - K];
    ret.push_back(sum);
  }

  return ret;
}

long long calc_ans(int cntA, int cntB, int K)
{
    return 1LL * cntA * (K - cntB) + 1LL * (K - cntA) * cntB;
}

int main() 
{
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> A(N), B(M);
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int j = 0; j < M; j++) cin >> B[j];

  vector<int> all_A = find_all(A,K);
  vector<int> all_B = find_all(B,K);

  int mxB = 0; int mnB = 1e9;
  for(auto b: all_B)
  {
    mxB = max(mxB,b);
    mnB = min(mnB,b);
  }

  long long best = 0;
  for (auto a: all_A)
  {
    best = max(best, calc_ans(a, mnB, K));
    best = max(best, calc_ans(a, mxB, K));
  }
  
  cout << best << endl;
  return 0;
}
