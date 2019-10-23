#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 123;
int n, dep[N];
vector<int> G[N], diam;
void dfs(int x, int pr) {
  dep[x] = dep[pr] + 1;
  for (auto y : G[x]) if (y != pr) {
    dfs(y, x);
  }
}
bool dfs2(int x, int tar, int pr) {
  diam.push_back(x);
  if (x == tar) return true;
  for (auto y : G[x]) if (y != pr) {
    if (dfs2(y, tar, x)) return true;
  }
  diam.pop_back();
  return false;
}
int cnt[N];
void dfs3(int x, int pr, int d) {
  cnt[d] = max(cnt[d], (int) G[x].size() - 1);
  for (auto y : G[x]) if (y != pr) {
    dfs3(y, x, d + 1);
  }
}

inline ll solve(int x, int y) {
  for (int i = 1; i <= n; i++) {
    cnt[i] = 1;
  }
  dfs3(x, y, 0);
  if (~y) dfs3(y, x, 0);
  cnt[0] = ~y ? (int) max(G[x].size(), G[y].size()) - 1 : (int) G[x].size();
  ll ret = 1;
  for (int i = 0; i <= n; i++) {
    ret *= cnt[i];
  }
  return ret * (~y ? 2 : 1);
}

int main() {
  scanf("%d", &n);
  if (n == 2) {
    puts("1 2");
    return 0;
  }
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs(1, 0);
  int g = 0, h = 0;
  for (int i = 1; i <= n; i++) {
    if (dep[i] > dep[g]) g = i;
  }
  dfs(g, 0);
  for (int i = 1; i <= n; i++) {
    if (dep[i] > dep[h]) h = i;
  }
  dfs2(g, h, 0);
  printf("%d ", (int) (diam.size() + 1) / 2);
  if ((int) diam.size() & 1) {
    int x = diam[diam.size() / 2];
    ll ans = solve(x, -1);
    for (auto y : G[x]) {
      ans = min(ans, solve(x, y));
    }
    printf("%lld\n", ans);
  } else {
    printf("%lld\n", solve(diam[diam.size() / 2 - 1], diam[diam.size() / 2]));
  }
}
