#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
char s[104];
const int mod = 998244353;
map<ll, int> f[52];
int n, g[104];
int calc(ll d, int m) {
  if (!m) return 1;
  if (f[m].find(d) != f[m].end()) return f[m][d];
  int ret = ((d & 1) + 1) * calc(d >> 1, m - 1) % mod;
  for (int j = 1; j <= m; j++) {
    for (int k = 2; k * j <= m; k++) {
      ll d2 = (1LL << j) - 1, d3 = d;
      for (int s = 1; s <= k; s++) {
        d2 &= d3;
        d3 >>= j;
      }
      ret = (ret + (ll) calc(d2, j) * calc(d3, m - k * j)) % mod;
    }
  }
  return f[m][d] = ret;
}

int main() {
  scanf("%s", s);
  n = (int) strlen(s);
  for (int i = 0; i < n; i++) {
    s[i] = s[i] - '0';
  }
  g[n] = 1;
  for (int i = n - 1; ~i; i--) {
    g[i] = (s[i] + 1) * g[i + 1] % mod;
    for (int j = 1; j <= n - i; j++) {
      for (int k = 2; k * j <= n - i; k++) {
        ll d = (1LL << j) - 1;
        for (int u = 0; u < k * j; u++) {
          d &= ~((ll) !s[i + u] << (u % j));
        }
        g[i] = (g[i] + (ll) calc(d, j) * g[i + k * j]) % mod;
      }
    }
  }
  printf("%d\n", g[0]);
}
