#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353, N = 500123;;
int fac[N], inv[N], n, k;
int C(int x, int y) {
  if (y < 0 || x < y) return 0;
  return (ll) fac[x] * inv[y] % mod * inv[x - y] % mod;
}
int calc(int x, int y, int l) {
  if (l <= 0) return 0;
  return (mod + C(x + y, x) - C(x + y, x + l)) % mod;
}
int main() {
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i < N; i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  scanf("%d%d", &n, &k);
  int ans = 0;
  for (int r = 0; r <= k; r++) {
    int b = k - r;
    if (r < b) continue;
    if (r == b) {
      ans = (ans + calc(r, b - 1, r - n + 1)) % mod;
    } else {
      ans = (ans + calc(r, b, r - n + 1)) % mod;
    }
  }
  printf("%d\n", ans);
}
