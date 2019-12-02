#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 16, mod = 1000000007;
int n, m, a[N], f[N + 1][1 << N], fac[(1 << N) + 1], inv[(1 << N) + 1];
int C(int x, int y) {return x < y || y < 0 ? 0 : (ll) fac[x] * inv[y] % mod * inv[x - y] % mod;}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &a[i]);
  }
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  for (int i = 2; i <= 1 << n; i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i <= 1 << n; i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  sort(a, a + m, greater<int>());
  f[0][0] = 1;
  for (int i = 0; i < m; i++) {
    for (int s = 0; s < 1 << n; s++) if (f[i][s]) {
      f[i + 1][s] = (f[i + 1][s] + f[i][s]) % mod;
      for (int j = 0; j < n; j++) if (!(s >> j & 1)) {
        f[i + 1][s | 1 << j] = (f[i + 1][s | 1 << j] + (ll) f[i][s] * C((1 << n) - a[i] - s, (1 << j) - 1) % mod * fac[1 << j]) % mod;
      }
    }
  }
  int ans = 0;
  for (int s = 0; s < 1 << n; s++) if (f[m][s]) {
    ans = (ans + (ll) (__builtin_parity(s) ? mod - 1 : 1) * f[m][s] % mod * fac[(1 << n) - s - 1]) % mod;
  }
  ans = (ll) ans * (1 << n) % mod;
  printf("%d\n", ans);
}
