#include <bits/stdc++.h>
using namespace std;

const int N = 100233;
int n, color[N], deg[N], ban[N], val[N], f[N], ret;
vector<int> G[N];
char s[N];
void dfs(int x, int pre) {
  int mx = 0, smx = 0;
  for (auto y : G[x]) if (y != pre) {
    dfs(y, x);
    smx = max(smx, f[y]);
    if (smx > mx) swap(smx, mx);
  }
  ret = max(ret, mx + smx + val[x]);
  f[x] = val[x] + mx;
}
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
    deg[x]++;
    deg[y]++;
  }
  scanf("%s", s + 1);
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    color[i] = s[i] == 'W';
    if (!color[i] && deg[i] <= 1) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int x = q.front(); q.pop();
    ban[x] = 1;
    for (auto y : G[x]) if (!ban[y]) {
      if (--deg[y] == 1 && !color[y]) {
        q.push(y);
      }
    }
  }
  int ans = -2, all = 0;
  for (int i = 1; i <= n; i++) if (!ban[i]) {
    all++;
    ans += 2;
    if (deg[i] != 1 && color[i] ^ (deg[i] & 1)) {
      ans++;
      val[i] = 2;
    }
  }
  if (!all) return puts("0"), 0;
  else if (all == 1) return puts("1"), 0;
  dfs(1, 0);
  printf("%d\n", ans - ret);
}
