#include <bits/stdc++.h>
using namespace std;

const int N = 2003;
int n, m;
vector<int> G[N];
int fa[N][N], tp[N][N];
vector<pair<int, int>> event;

void dfsi(int x, int pre, int rt) {
  fa[rt][x] = pre;
  for (auto y : G[x]) if (y != pre) {
    dfsi(y, x, rt);
  }
}
void dfsx(int x, int md, int rt) {
  for (auto y : G[x]) if (y != fa[rt][x]) {
    if (~tp[rt][y]) {
      event.emplace_back(y, md);
    } else {
      tp[rt][y] = md;
      dfsx(y, md, rt);
    }
  }
}
void connect(int a, int b) {
  if (tp[a][b] == b || tp[b][a] == a) return;
  if (~tp[a][b]) {connect(tp[a][b], b); return;}
  if (~tp[b][a]) {connect(tp[b][a], a); return;}
  tp[a][b] = b;
  tp[b][a] = a;
  dfsx(b, b, a);
  dfsx(a, a, b);
}
int ans = 0;
void dfs(int x, int pre, int ls) {
  if (ls != x && tp[ls][x] == x) {
    ans++;
    ls = x;
  }
  for (auto y : G[x]) if (y != pre) {
    dfs(y, x, ls);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    dfsi(i, 0, i);
  }
  memset(tp, -1, sizeof tp);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    event.emplace_back(x, y);
    do {
      x = event.back().first, y = event.back().second;
      event.pop_back();
      connect(x, y);
    } while (!event.empty());
  }
  for (int i = 1; i <= n; i++) {
    dfs(i, -1, i);
  }
  printf("%d\n", ans >> 1);
}
