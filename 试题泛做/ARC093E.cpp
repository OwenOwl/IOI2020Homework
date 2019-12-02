#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2022, mod = 1000000007;
int n, m, fa[N], pw[N];
pair<ll, pair<int, int>> e[N];
vector<pair<int, ll>> G[N];
ll x, s;

ll dfs(int x, int pre, int g) {
  if (x == g) return 0;
  for (auto y : G[x]) if (y.first != pre) {
    ll t = dfs(y.first, x, g);
    if (~t) return max(t, y.second);
  }
  return -1;
}

int F(int x) {while (fa[x] != x) x = fa[x] = fa[fa[x]]; return x;}
int main() {
  scanf("%d%d%lld", &n, &m, &x);
  pw[0] = 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%lld", &e[i].second.first, &e[i].second.second, &e[i].first);
    pw[i] = (pw[i - 1] << 1) % mod;
  }
  sort(e + 1, e + 1 + m);
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u = F(e[i].second.first), v = F(e[i].second.second);
    if (u != v) {
      fa[u] = v;
      G[u].emplace_back(v, e[i].first);
      G[v].emplace_back(u, e[i].first);
      s += e[i].first;
      e[i].first = -1;
    }
  }
  if (x < s) return puts("0"), 0;
  int b = 0, c = 0;
  for (int i = 1; i <= m; i++) if (~e[i].first) {
    ll t = e[i].first - dfs(e[i].second.first, 0, e[i].second.second);
    if (t == x - s) b++;
    else if (t > x - s) c++;
  }
  int ans = 0;
  if (n == 1) {
    printf("%d\n", x == s);
    return 0;
  }
  if (x == s) {
    ans = (ll) (pw[n - 1] + mod - 2) * pw[m - n + 1] % mod;
  }
  ans = (ans + 2LL * (pw[b] - 1) * pw[c]) % mod;
  printf("%d\n", ans);
}
