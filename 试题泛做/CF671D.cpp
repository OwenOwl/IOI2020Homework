#include <bits/stdc++.h>
using namespace std;

const int N = 300233;
int n, m, s[N];
vector<int> G[N];
vector<pair<int, int>> P[N];
int np = 0, val[N], cov[N], dis[N], tag[N], ch[N][2];
long long ans;

void md(int x, int v) {
  if (!x) return;
  tag[x] += v;
  val[x] += v;
}
void pd(int x) {
  if (!tag[x]) return;
  md(ch[x][0], tag[x]);
  md(ch[x][1], tag[x]);
  tag[x] = 0;
}
int merge(int x, int y) {
  if (!x || !y) return x | y;
  pd(x), pd(y);
  if (val[x] > val[y]) swap(x, y);
  ch[x][1] = merge(ch[x][1], y);
  if (dis[ch[x][0]] < dis[ch[x][1]]) swap(ch[x][0], ch[x][1]);
  dis[x] = dis[ch[x][0]] + 1;
  return x;
}

int dep[N];
int dfs(int x, int pre) {
  int v = 0;
  dep[x] = dep[pre] + 1;
  for (auto y : G[x]) if (y != pre) {
    v = merge(v, dfs(y, x));
    if (!s[y]) {
      puts("-1");
      exit(0);
    }
    s[x] += s[y];
  }
  for (auto e : P[x]) {
    ++np;
    val[np] = e.second;
    cov[np] = dep[e.first];
    v = merge(v, np);
  }
  while (cov[v] >= dep[x]) {
    pd(v);
    v = merge(ch[v][0], ch[v][1]);
  }
  if (v) {
    ans += val[v];
    md(v, -val[v]);
  }
  return v;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1, u, v, w; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    s[u]++;
    s[v]--;
    P[u].emplace_back(v, w);
  }
  dfs(1, 0);
  printf("%lld\n", ans);
}
