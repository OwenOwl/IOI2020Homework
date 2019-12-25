#include <bits/stdc++.h>
using namespace std;

const int N = 400233;
int n, m, q, to[N], nxt[N], hed[N], en = 1;
vector<int> G[N];
int dfn[N], low[N], dfc = 0;
int bel[N], bcnt = 0, ban[N];
int rt[N], fa[N][20], dep[N];
int s1[N], s2[N], fail[N];

void tarjan(int x, int pre) {
  dfn[x] = low[x] = ++dfc;
  for (int e = hed[x]; e; e = nxt[e]) if ((e >> 1) != pre) {
    int y = to[e];
    if (!dfn[y]) {
      tarjan(y, e >> 1);
      low[x] = min(low[x], low[y]);
      if (low[y] > dfn[x]) {
        ban[e >> 1] = 1;
      }
    } else {
      low[x] = min(low[x], dfn[y]);
    }
  }
}
void cont(int x) {
  bel[x] = bcnt;
  for (int e = hed[x]; e; e = nxt[e]) if (!ban[e >> 1] && !bel[to[e]]) {
    cont(to[e]);
  }
}
void pdfs(int x, int pre, int root) {
  rt[x] = root;
  fa[x][0] = pre;
  dep[x] = dep[pre] + 1;
  for (int k = 1; k <= 19; k++) {
    fa[x][k] = fa[fa[x][k - 1]][k - 1];
  }
  for (auto y : G[x]) if (y != fa[x][0]) {
    pdfs(y, x, root);
  }
}
int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int k = 19; k >= 0; k--) {
    if (dep[fa[x][k]] >= dep[y]) {
      x = fa[x][k];
    }
  }
  if (x == y) return x;
  for (int k = 19; k >= 0; k--) {
    if (fa[x][k] != fa[y][k]) {
      x = fa[x][k];
      y = fa[y][k];
    }
  }
  return fa[x][0];
}
void calc(int x) {
  for (auto y : G[x]) if (y != fa[x][0]) {
    calc(y);
    if (s1[y] && s2[y]) fail[x] = 1;
    s1[x] += s1[y];
    s2[x] += s2[y];
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    to[++en] = y;
    nxt[en] = hed[x];
    hed[x] = en;
    to[++en] = x;
    nxt[en] = hed[y];
    hed[y] = en;
  }
  for (int i = 1; i <= n; i++) if (!dfn[i]) {
    tarjan(i, 0);
  }
  for (int i = 1; i <= n; i++) if (!bel[i]) {
    ++bcnt;
    cont(i);
  }
  for (int e = 2; e <= en; e += 2) if (ban[e >> 1]) {
    G[bel[to[e]]].push_back(bel[to[e ^ 1]]);
    G[bel[to[e ^ 1]]].push_back(bel[to[e]]);
  }
  for (int i = 1; i <= bcnt; i++) if (!rt[i]) {
    pdfs(i, 0, i);
  }
  while (q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    x = bel[x], y = bel[y];
    if (rt[x] != rt[y]) {
      puts("No");
      return 0;
    }
    int g = lca(x, y);
    s1[g]--;
    s1[x]++;
    s2[g]--;
    s2[y]++;
  }
  for (int i = 1; i <= bcnt; i++) {
    if (rt[i] == i) {
      calc(i);
    }
  }
  puts(*max_element(fail + 1, fail + 1 + bcnt) == 1 ? "No" : "Yes");
  return 0;
}
