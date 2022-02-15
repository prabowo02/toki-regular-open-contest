#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f1 first
#define s2 second

using ll = long long;
using ii = pair<int, int>;

constexpr int MAX = 1e5 + 69;

int n;
int val[MAX], depth[MAX], par[MAX];
ll dp[MAX];

vector<int> child[MAX], pend[MAX];
vector<ll> pfx[MAX];

inline void dfs(int node)
{
  for (int to : child[node])
  {
    depth[to] = depth[node] + 1;
    dfs(to);
  }

  sort(child[node].begin(), child[node].end(), [](int x, int y){
    return val[x] > val[y] || (val[x] == val[y] && x < y);
  });

  pfx[node].pb(val[node]);
  for (int x : child[node])
    pfx[node].pb(val[x]);
  for (int i = 1; i < (int)pfx[node].size(); ++i)
    pfx[node][i] += pfx[node][i-1];
}

int main()
{
  ios :: sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> val[i];
  for (int i = 2; i <= n; ++i)
    cin >> par[i], child[par[i]].pb(i);

  dfs(1);

  vector<int> order, nxt, dead;
  for (int i = 1; i <= n; ++i)
  {
    if (child[i].size() >= 1)
      order.pb(i);
    else dp[i] = val[i];
  }

  sort(order.begin(), order.end(), [](int x, int y){
    return depth[x] > depth[y];
  });

  unsigned long long ans = 0;
  for (int k = 1; k <= n; ++k)
  {
    nxt.clear(); dead.clear();
    for (int node : order)
    {
      sort(pend[node].begin(), pend[node].end(), [&](int x, int y){
        return dp[x] > dp[y] || (dp[x] == dp[y] && x < y); 
      });

      dp[node] = pfx[node][k];

      int i = k;
      set<int> chosen;
      for (int to : pend[node])
      {
        while (chosen.count(child[node][i-1]))
          i--;
        
        if (pfx[node][i] - pfx[node][i-1] < dp[to])
        {
          if (val[to] > pfx[node][i] - pfx[node][i-1]) //node to is among pfx[node][1] .. pfx[node][i]
          {
            dp[node] += dp[to] - val[to];
          }
          else if (val[to] == pfx[node][i] - pfx[node][i-1] && to <= child[node][i-1])
          {
            dp[node] += dp[to] - val[to];
          }
          else //remove the contribution from pfx[node][i]
          {
            dp[node] += dp[to] - (pfx[node][i] - pfx[node][i-1]);
            i--;
          }

          chosen.insert(to);
        }
        else break;

        if ((int)chosen.size() == k)
          break;
      }

      if (node != 1)
        pend[par[node]].pb(node);

      pend[node].clear();
      if ((int)child[node].size() == k)
        dead.pb(node);
      else nxt.pb(node);
    }

    ans += dp[1];
        
    order = nxt;
    for (int node : dead)
      dp[node] = val[node];
  }

  cout << ans << endl;

  return 0;
}