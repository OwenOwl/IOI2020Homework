#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 404, mod = 998244353;
int fac[N], inv[N];
inline int qpow(int b, int p) {
  int r = 1;
  for (; p; p >>= 1, b = (ll) b * b % mod) if (p & 1) {
    r = (ll) r * b % mod;
  }
  return r;
}
int n, p, s, a[N], b[N], f[N][N];

int main() {
  scanf("%d", &n);
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i < N; i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i], &b[i]);
  }
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = p; j >= 0; j--) {
      int p1 = (ll) j * qpow(j + a[i], mod - 2) % mod, p2 = (mod + 1 - p1) % mod;
      for (int k = 0, c1 = 1; k <= s; k++, c1 = (ll) c1 * p1 % mod) if (f[j][k]) {
        for (int l = 0, c2 = 1; l < b[i]; l++, c2 = (ll) c2 * p2 % mod) {
          f[j + a[i]][k + l] = (f[j + a[i]][k + l] + mod - (ll) f[j][k] * fac[k + l] % mod * inv[k] % mod * inv[l] % mod * c1 % mod * c2 % mod) % mod;
        }
      }
    }
    p += a[i];
    s += b[i] - 1;
  }
  int ans = 0;
  for (int j = 1; j <= p; j++) {
    int c = qpow(j, mod - 2);
    for (int k = 0; k <= s; k++) if (f[j][k]) {
      ans = (ans + (ll) f[j][k] * p % mod * c) % mod;
    }
  }
  printf("%d\n", (mod - ans) % mod);
}
