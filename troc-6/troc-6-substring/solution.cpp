#include <bits/stdc++.h>
using namespace std;

string s, t;
int cnt[26];

int work() {
  for (int i = 1 ; i < t.length() ; i++) {
    if (t[i] != t[i-1]) {
      return 0;
    }
  }

  for (char ch : s) {
    cnt[ch - 'a']++;
  }

  int chCount = cnt[t[0] - 'a'];
  int otherCount = s.length() - chCount;
  
  while (chCount >= t.length() && otherCount > 0) {
    chCount -= (t.length() - 1);
    otherCount--;
  }

  if (chCount < t.length()) {
    return 0;
  } else {
    return 1 + chCount - t.length();
  }
}

int main() {
  cin >> s >> t;
  cout << work() << endl;
  return 0;
}
