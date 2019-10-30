#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 607, mod = 1000000007;

int n, link, opp[N], g[N], f[N][N], c[N][N];

int main() {
  scanf("%d%d", &n, &link);
  n <<= 1;
  while (link--) {
    int x, y;
    scanf("%d%d", &x, &y);
    opp[x] = y;
    opp[y] = x;
  }
  g[0] = 1;
  for (int i = 2; i <= n; i += 2) {
    g[i] = (ll) g[i - 2] * (i - 1) % mod;
  }
  for (int l = 1; l <= n; l++) {
    for (int r = l; r <= n; r++) {
      c[l][r] = c[l][r - 1] + !opp[r];
    }
  }
  int ans = 0;
  for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1, ok = 1;
      for (int i = l; i <= r; i++) {
        if (opp[i] && (opp[i] < l || opp[i] > r)) {
          ok = 0;
        }
      }
      if (!ok) continue;
      f[l][r] = g[c[l][r]];
      for (int k = l + 1; k < r; k++) {
        f[l][r] = (f[l][r] + mod - (ll) f[l][k] * g[c[k + 1][r]] % mod) % mod;
      }
      ans = (ans + (ll) f[l][r] * g[c[1][l - 1] + c[r + 1][n]]) % mod;
    }
  }
  printf("%d\n", ans);
}
