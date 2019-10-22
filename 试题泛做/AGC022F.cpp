#include <bits/stdc++.h>
using namespace std;
const int N = 52, mod = 1000000007;
int n, f[N][N * 2 + 5], c[N][N];
int main() {
  scanf("%d", &n);
  c[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
  }
  f[1][N + 0] = 1;
  f[1][N + (-2)] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = -n - 1; j <= n + 1; j++) if (!(j & 1) && f[i][N + j]) {
      for (int k1 = 0; k1 <= n - i; k1++) {
        for (int k2 = 0; k1 + k2 <= n - i; k2++) {
          if (!(k1 + k2) || (j / 2 + k2 - k1) & 1 || k1 + k2 < abs(j / 2)) continue;
          (f[i + k1 + k2][N + j / 2 + k2 - k1] += (long long) f[i][N + j] * c[i + k1 + k2][k2] % mod * c[i + k1][k1] % mod) %= mod;
        }
      }
    }
  }
  printf("%d\n", f[n][N]);
}
