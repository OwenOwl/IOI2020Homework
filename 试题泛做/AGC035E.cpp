#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 160;
int n, k, mod, g[N][N], f[N][N][N];

int main() {
  scanf("%d%d%d", &n, &k, &mod);
  if (!(k & 1)) {
    g[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i && j <= k >> 1; j++) {
        g[i + 1][j + 1] = (g[i + 1][j + 1] + g[i][j]) % mod;
        g[i + 1][0] = (g[i + 1][0] + g[i][j]) % mod;
      }
    }
    int ansx = 0, ansy = 0;
    for (int j = 0; j <= n + 1 >> 1 && j <= k >> 1; j++) {
      ansx = (ansx + g[n >> 1][j]) % mod;
      ansy = (ansy + g[n + 1 >> 1][j]) % mod;
    }
    ansx = (ll) ansx * ansy % mod;
    printf("%d\n", ansx);
  } else {
    f[0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
      bool px = 2 * i + 1 <= n, py = 2 * i + 1 - k >= 2 && 2 * i + 1 - k <= n;
      for (int c = 0; c <= i + 1 && c < k + 2; c++) {
        for (int d = 0; d <= i; d++) {
          if (true   ) f[i + 1][0][0] = (f[i + 1][0][0] + f[i][c][d]) % mod;
          if (px     ) f[i + 1][0][d + 1] = (f[i + 1][0][d + 1] + f[i][c][d]) % mod;
          if (py     ) f[i + 1][c ? c + 1 : 0][0] = (f[i + 1][c ? c + 1 : 0][0] + f[i][c][d]) % mod;
          if (px & py) f[i + 1][max(c + 1, d + 2)][d + 1] = (f[i + 1][max(c + 1, d + 2)][d + 1] + f[i][c][d]) % mod;
        }
      }
    }
    printf("%d\n", f[n + 1][0][0]);
  }
}
