#include <bits/stdc++.h>
using namespace std;

const int N = 2022;
int n, m, u[N], v[N], col[N], ans = 0;
vector<int> G[N];
vector<pair<int, int>> E[N];

int dep[N], fa[N], has[N][N], ig[N];
vector<pair<int, int>> cov[N];
inline void dfs1(int x, int pre) {
  dep[x] = dep[pre] + 1;
  fa[x] = pre;
  for (auto y : G[x]) if (y != pre) {
    dfs1(y, x);
  }
}
inline void label(int x, int y, int id) {
  while (x != y) {
    if (dep[x] >= dep[y]) {
      has[x][id] = 1;
      cov[x].emplace_back(id, 1);
      x = fa[x];
    } else {
      has[y][id] = 1;
      cov[y].emplace_back(id, 0);
      y = fa[y];
    }
  }
}
inline void dfs2(int x) {
  for (auto y : G[x]) if (y != fa[x]) {
    dfs2(y);
  }
  if (x != 1) {
    ans += (cov[x].size() >= 1) + (cov[x].size() >= 2);
    if (ig[x] || cov[x].size() < 2) return;
    int p = cov[x][0].first, q = cov[x][1].first;
    E[p].emplace_back(q, cov[x][0].second == cov[x][1].second);
    E[q].emplace_back(p, cov[x][0].second == cov[x][1].second);
    for (int y = 2; y <= n; y++) {
      if (has[y][p] && has[y][q]) {
        ig[y] = 1;
      }
    }
  }
}
inline void dfs3(int x) {
  for (auto y : E[x]) if (!~col[y.first]) {
    col[y.first] = col[x] ^ y.second;
    dfs3(y.first);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs1(1, 0);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u[i], &v[i]);
    label(u[i], v[i], i);
  }
  dfs2(1);
  printf("%d\n", ans);
  memset(col, -1, sizeof col);
  for (int i = 1; i <= m; i++) {
    if (!~col[i]) {
      col[i] = 0;
      dfs3(i);
    }
    if (col[i]) {
      printf("%d %d\n", v[i], u[i]);
    } else {
      printf("%d %d\n", u[i], v[i]);
    }
  }
}
