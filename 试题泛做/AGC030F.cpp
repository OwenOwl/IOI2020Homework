#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 666, mod = 1000000007;
int n, m, f[N][N], g[N][N];
bool fix[N], banned[N];
int main() {
  scanf("%d", &n);
  int t = 1;
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d", &x, &y);
    if (~x && ~y) {
      fix[x] = fix[y] = true;
    } else if (~x || ~y) {
      banned[x + y + 1] = true;
    } else {
      t = (ll) t * (++m) % mod;
    }
  }
  f[0][0] = 1;
  for (int x = n * 2; x; x--) if (!fix[x]) {
    memset(g, 0, sizeof g);
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) if (f[i][j]) {
        if (banned[x]) {
          g[i][j + 1] = (g[i][j + 1] + f[i][j]) % mod;
          if (i) g[i - 1][j] = (g[i - 1][j] + f[i][j]) % mod;
        } else {
          g[i + 1][j] = (g[i + 1][j] + f[i][j]) % mod;
          if (i) g[i - 1][j] = (g[i - 1][j] + f[i][j]) % mod;
          if (j) g[i][j - 1] = (g[i][j - 1] + (ll) f[i][j] * j) % mod;
        }
      }
    }
    memcpy(f, g, sizeof g);
  }
  int ans = (ll) f[0][0] * t % mod;
  printf("%d\n", ans);
}
