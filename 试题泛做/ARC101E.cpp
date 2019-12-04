#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5010, mod = 1000000007;
int n, size[N], f[N][N], g[N], h[N];
vector<int> G[N];
void dfs(int x, int pre) {
  size[x] = 1;
  f[x][1] = 1;
  for (auto y : G[x]) if (y ^ pre) {
    dfs(y, x);
    for (int i = 1; i <= size[x]; i++) {
      for (int j = 0; j <= size[y]; j++) {
        h[i + j] = (h[i + j] + (ll) f[x][i] * f[y][j]) % mod;
      }
    }
    for (int i = 1; i <= size[x] + size[y]; i++) {
      f[x][i] = h[i];
      h[i] = 0;
    }
    size[x] += size[y];
  }
  for (int i = 2; i <= size[x]; i += 2) {
    f[x][0] = (f[x][0] + mod - (ll) f[x][i] * g[i] % mod) % mod;
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  g[0] = 1;
  for (int i = 2; i <= n; i += 2) {
    g[i] = (ll) g[i - 2] * (i - 1) % mod;
  }
  dfs(1, 0);
  int ans = (mod - f[1][0]) % mod;
  printf("%d\n", ans);
}
