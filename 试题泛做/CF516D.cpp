#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;
int n, q, a[N], ff[N], sz[N], vis[N];
vector<pair<int, ll>> G[N];
ll mx[N], smx[N];
int F(int x) {while (x != ff[x]) x = ff[x] = ff[ff[x]]; return x;}
void dp(int x, int pre) {
  for (auto y : G[x]) if (y.first != pre) {
    dp(y.first, x);
    smx[x] = max(smx[x], mx[y.first] + y.second);
    if (smx[x] > mx[x]) swap(smx[x], mx[x]);
  }
}
void dp2(int x, int pre) {
  for (auto y : G[x]) if (y.first != pre) {
    smx[y.first] = max(smx[y.first], (mx[x] == mx[y.first] + y.second ? smx[x] : mx[x]) + y.second);
    if (smx[y.first] > mx[y.first]) swap(smx[y.first], mx[y.first]);
    dp2(y.first, x);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y, z; i < n; i++) {
    scanf("%d%d%d", &x, &y, &z);
    G[x].emplace_back(y, z);
    G[y].emplace_back(x, z);
  }
  dp(1, 0);
  dp2(1, 0);
  for (int i = 1; i <= n; i++) a[i] = i;
  sort(a + 1, a + 1 + n, [&](const int &a, const int &b){return mx[a] > mx[b];});
  scanf("%d", &q);
  while (q--) {
    ll li;
    scanf("%lld", &li);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      ff[i] = i;
      sz[i] = 1;
      vis[i] = 0;
    }
    for (int l = 1, r = 0; l <= n; l++) {
      while (r < n && mx[a[l]] - mx[a[r + 1]] <= li) {
        int x = a[++r];
        vis[x] = 1;
        for (auto y : G[x]) if (vis[y.first]) {
          int u = F(x), v = F(y.first);
          if (sz[u] > sz[v]) swap(u, v);
          ff[u] = v;
          sz[v] += sz[u];
          ans = max(ans, sz[v]);
        }
      }
      sz[F(a[l])]--;
    }
    printf("%d\n", ans);
  }
}
