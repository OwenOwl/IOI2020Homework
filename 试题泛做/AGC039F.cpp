#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 103;
int n, m, K, mod, f[N][N], fac[N], inv[N];
int qpow(int b, int p) {
  int r = 1;
  for (; p; p >>= 1, b = (ll) b * b % mod) if (p & 1) {
    r = (ll) r * b % mod;
  }
  return r;
}
int main() {
  scanf("%d%d%d%d", &n, &m, &K, &mod);
  f[0][0] = 1;
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i <= max(n, m); i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i <= max(n, m); i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  for (int step = 0; step < K << 1; step++) {
    int cnt1 = (step >> 1) + 1, cnt2 = K - (step >> 1);
    if (!(step & 1)) {
      for (int i = n; ~i; i--) {
        for (int j = m; ~j; j--) if (f[i][j]) {
          int coef = (ll) (qpow(cnt1, m - j) + mod - qpow(cnt1 - 1, m - j)) * qpow(cnt2, j) % mod;
          for (int l = 1, c = (ll) coef * f[i][j] % mod * inv[i] % mod; i + l <= n; l++, c = (ll) c * coef % mod) {
            f[i + l][j] = (f[i + l][j] + (ll) c * fac[i + l] % mod * inv[l]) % mod;
          }
        }
      }
    } else {
      for (int j = m; ~j; j--) {
        for (int i = n; ~i; i--) if (f[i][j]) {
          int coef = (ll) qpow(cnt1, n - i) * (qpow(cnt2, i) + mod - qpow(cnt2 - 1, i)) % mod;
          for (int l = 1, c = (ll) coef * f[i][j] % mod * inv[j] % mod; j + l <= m; l++, c = (ll) c * coef % mod) {
            f[i][j + l] = (f[i][j + l] + (ll) c * fac[j + l] % mod * inv[l]) % mod;
          }
        }
      }
    }
  }
  printf("%d\n", f[n][m]);
}
