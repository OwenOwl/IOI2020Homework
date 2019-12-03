#include <bits/stdc++.h>
using namespace std;

const int N = 100233;
int n, u, v, p, dep[N], vis[N], size[N];
vector<int> G[N], t(1, 1);
void dfs(int x, int pre) {
  dep[x] = dep[pre] + 1;
  for (auto y : G[x]) if (y != pre) {
    dfs(y, x);
  }
}
bool dfs(int x, int pre, int g) {
  vis[x] = ++p;
  if (x == g) return true;
  for (auto y : G[x]) if (y != pre) {
    if (dfs(y, x, g)) return true;
  }
  vis[x] = 0;
  --p;
  return false;
}
void get() {
  vector<int> f(1, 0);
  for (int i = 1, a = 0; i <= p; i++) {
    for (int j = 1; j <= size[i]; j++) f.push_back(a + j + 1);
    f.push_back(a + 1);
    a += size[i] + 1;
  }
  t = min(t, f);
}
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++) if (dep[i] > dep[u]) {
    u = i;
  }
  dfs(u, 0);
  for (int i = 1; i <= n; i++) if (dep[i] > dep[v]) {
    v = i;
  }
  dfs(u, 0, v);
  for (int i = 1; i <= n; i++) if (!vis[i]) {
    if (G[i].size() > 1) return puts("-1"), 0;
    size[vis[G[i][0]]]++;
  }
  get();
  reverse(size + 1, size + 1 + p);
  get();
  for (int i = 1; i <= n; i++) {
    printf("%d%c", t[i], i == n ? '\n' : ' ');
  }
}
