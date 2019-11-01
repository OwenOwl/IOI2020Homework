#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3002, mod = 1000000007;
int n, q, a[N], f[N][N];
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    for (int j = 1; j < i; j++) {
      if (a[j] < a[i]) f[i][j] = 1;
      if (a[j] > a[i]) f[j][i] = 1;
    }
  }
  int ans = 0, t = 1;
  while (q--) {
    (t <<= 1) %= mod;
    int x, y;
    scanf("%d%d", &x, &y);
    f[y][x] = f[x][y] = (ll) (f[x][y] + f[y][x]) * (mod + 1) / 2 % mod;
    for (int i = 1; i <= n; i++) if (i != x && i != y) {
      f[x][i] = f[y][i] = (ll) (f[x][i] + f[y][i]) * (mod + 1) / 2 % mod;
      f[i][x] = f[i][y] = (ll) (f[i][x] + f[i][y]) * (mod + 1) / 2 % mod;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ans = (ans + (ll) f[j][i] * t) % mod;
    }
  }
  printf("%d\n", ans);
}
