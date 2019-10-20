#include <bits/stdc++.h>
using namespace std;

int n, c, a[6];
long long f[1 << 5][1 << 5][305];

int main() {
  scanf("%d%d", &n, &c);
  c *= n;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i] *= n;
  }
  sort(a, a + n);
  f[0][0][a[n - 1]] = 1;
  long long ans = 0, all = 1;
  for (int x = 1; x < c; x++) if (x % n) {
    for (int l = x + 1; l <= c; l++) {
      for (int i = 0; i < 1 << n - 1; i++) if (!(i >> (x % n - 1) & 1)) {
        for (int j = 0; j < 1 << n - 1; j++) if (f[i][j][l]) {
          for (int y = 0; y < n - 1; y++) if (!(j >> y & 1)) {
            f[i | 1 << (x % n - 1)][j | 1 << y][min(c, max(x + a[y], l))] += f[i][j][l];
          }
        }
      }
    }
  }
  ans = f[(1 << n - 1) - 1][(1 << n - 1) - 1][c];
  for (int i = 1; i < n; i++) {
    all *= i * c / n;
  }
  printf("%.13Lf\n", (long double) ans / all);
}

