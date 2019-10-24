#include <bits/stdc++.h>
using namespace std;

const int N = 302;
int n, k, mod, c[N][N], f[N][N], g[N][N];

int main() {
  scanf("%d%d%d", &n, &k, &mod);
  c[0][0] = 1;
  for (int i = 1; i <= n + 1; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
  }
  for (int j = 1; j <= k + 1; j++) {
    f[1][j] = 1;
    g[1][j] = j;
  }
  for (int i = 2; i <= n + 1; i++) {
    for (int j = 1; j <= k + 1; j++) {
      for (int l = 1; l <= i - 1; l++) {
        f[i][j] = (f[i][j] + (long long) g[l][j - 1] * f[i - l][j] % mod * c[i - 2][l - 1]) % mod;
      }
      g[i][j] = (g[i][j - 1] + f[i][j]) % mod;
    }
  }
  printf("%d\n", f[n + 1][k + 1]);
}
