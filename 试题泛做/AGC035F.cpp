#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 500233, mod = 998244353;
int n, m, fac[N], inv[N];
int main() {
  scanf("%d%d", &n, &m);
  if (n < m) swap(n, m);
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i <= n; i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  int pn = fac[n], pm = fac[m], ans = 0;
  for (int i = n - m; i; i--) pn = (ll) pn * (m + 1) % mod;
  for (int i = m; ~i; i--) {
    int coef = (ll) pn * pm % mod * inv[n - i] % mod * inv[m - i] % mod * inv[i] % mod * (i & 1 ? mod - 1 : 1) % mod;
    pn = (ll) pn * (m + 1) % mod;
    pm = (ll) pm * (n + 1) % mod;
    ans = (ans + coef) % mod;
  }
  printf("%d\n", ans);
}
