#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;
int n, m, fa[N], p[N], visit[N];
ll a[N], b[N], f[N], s[N];
vector<int> G[N], E[N];
int F(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &a[i], &b[i]);
  }
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    fa[i] = p[i] = i;
  }
  sort(p + 1, p + 1 + n, [&](const int &x, const int &y){return a[x] - b[x] < a[y] - b[y];});
  for (int i = 1; i <= n; i++) {
    int x = p[i], z;
    visit[x] = 1;
    s[x] = b[x];
    for (auto y : G[x]) if (visit[y]) {
      if ((z = F(y)) == x) continue;
      fa[z] = x;
      s[x] += s[z];
      E[x].push_back(z);
    }
  }
  for (int i = 1; i <= n; i++) {
    int x = p[i];
    if (E[x].empty()) f[x] = max(a[x], b[x]);
    else f[x] = 1ll << 60;
    for (auto y : E[x]) {
      f[x] = min(f[x], max(f[y], a[x] - b[x]) + s[x] - s[y]);
    }
  }
  printf("%lld\n", f[p[n]]);
}
