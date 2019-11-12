#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 301, mod = 1000000007;
int n, k, ans = 0;
char s[N];
int fac[N], inv[N];

int f[N], m = 0, r[N], b[N], visit[N];
inline void solve() {
  for (int i = 1; i <= k; i++) visit[i] = 0;
  for (int i = 1, j = 1; i <= m; i++, j++) {
    while (j <= k && s[j] != 'r') j++;
    if (j > k) return;
    r[i] = j;
    visit[j] = 1;
  }
  for (int i = 1, j = 1; i <= m; i++, j++) if (f[i] >= 2) {
    j = max(j, r[i]);
    while (j <= k && s[j] != 'b') j++;
    if (j > k) return;
    b[i] = j;
    visit[j] = 1;
  }
  for (int i = 1, j = 1; i <= m; i++) if (f[i] >= 3) {
    int x = f[i] - 2;
    j = max(j, b[i]);
    while (x--) {
      while (j <= k && visit[j]) j++;
      if (j > k) return;
      visit[j] = 1;
      j++;
    }
  }
  int coef = fac[m];
  for (int i = 1, j = 0; i <= m; i++) {
    j = f[i] != f[i - 1] ? 1 : j + 1;
    coef = (ll) coef * fac[j - 1] % mod * inv[j] % mod;
  }
  int upper = n + 1, lower = 0;
  for (int i = 1; i <= m; i++) {
    if (f[i] >= 2) upper += 2;
    lower += f[i] * 2;
  }
  if (upper < lower) return;
  coef = (ll) coef * fac[upper] % mod * inv[lower] % mod * inv[upper - lower] % mod;
  ans = (ans + coef) % mod;
}
void dfs(int x, int last) {
  solve();
  for (int i = last; i; i--) {
    int y = (i == 1 ? 1 : 2 * i - 3) + 1;
    if (x >= y) {
      f[++m] = i;
      dfs(x - y, i);
      --m;
    }
  }
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = (ll) fac[i - 1] * i % mod;
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  for (int i = 2; i < N; i++) {
    inv[i] = (ll) inv[i] * inv[i - 1] % mod;
  }
  dfs(n + 1, n + 1);
  printf("%d\n", ans);
}
