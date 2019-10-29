#include <bits/stdc++.h>
using namespace std;

const int N = 52;
int n;
vector<int> G1[N], G2[N], T[N];
int fix[N], fa[N], vis[N], ins[N];
void dfs1(int x, int pre, int ign) {
  fa[x] = pre;
  for (auto y : G1[x]) if (y != pre && y != ign) {
    dfs1(y, x, ign);
  }
}
void dfs2(int x, int pre) {
  if (fa[x] != pre) return;
  fix[x] = 1;
  for (auto y : G2[x]) if (y != pre) {
    dfs2(y, x);
  }
}
void dfs3(int x, int pre, int ign) {
  if (!fix[x] && !fix[pre]) T[x].push_back(pre);
  for (auto y : G1[x]) if (y != pre && y != ign) {
    dfs3(y, x, ign);
  }
}
void dfs4(int x, int pre) {
  if (!fix[x] && !fix[pre]) T[pre].push_back(x);
  for (auto y : G2[x]) if (y != pre) {
    dfs4(y, x);
  }
}
int dfs5(int x) {
  vis[x] = ins[x] = 1;
  for (auto y : T[x]) {
    if (ins[y]) {
      return 1;
    } else if (!vis[y] && dfs5(y)) {
      return 1;
    }
  }
  ins[x] = 0;
  return 0;
}
inline int solve(int rt, int rt2) {
  memset(fix, 0, sizeof fix);
  memset(fa, 0, sizeof fa);
  memset(vis, 0, sizeof vis);
  memset(ins, 0, sizeof ins);
  for (int i = 1; i <= n; i++) {
    T[i].clear();
  }
  dfs1(rt2, rt, rt);
  dfs2(rt, 0);
  dfs3(rt2, rt, rt);
  dfs4(rt, 0);
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && dfs5(i)) return -1;
  }
  return n - accumulate(fix + 1, fix + 1 + n, 0);
}
inline void Main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    G1[i].clear();
    G2[i].clear();
  }
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G1[x].push_back(y);
    G1[y].push_back(x);
  }
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G2[x].push_back(y);
    G2[y].push_back(x);
  }
  int ans = 999;
  for (int i = 1; i <= n; i++) if (G1[i].size() == 1) {
    for (int j = 1; j <= n; j++) if (j != i) {
      int x = solve(i, j);
      if (~x) ans = min(ans, x + (j != G1[i][0]));
    }
  }
  printf("%d\n", ans == 999 ? -1 : ans);
}
int main() {
  int Test;
  scanf("%d", &Test);
  while (Test--) {
    Main();
  }
}
