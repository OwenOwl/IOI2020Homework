#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 505;
int n;
ll inf, v1[N][N], v2[N][N], f[N][N];
ll get(ll v[N][N], int x1, int x2, int y1, int y2) {
  return v[x2][y2] - v[x1][y2] - v[x2][y1] + v[x1][y1];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      scanf("%lld", &v1[j][i]);
    }
    for (int j = i + 1; j <= n; j++) {
      scanf("%lld", &v2[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      v1[i][j] = v1[i][j] + v1[i - 1][j] + v1[i][j - 1] - v1[i - 1][j - 1];
      v2[i][j] = v2[i][j] + v2[i - 1][j] + v2[i][j - 1] - v2[i - 1][j - 1];
    }
  }
  memset(f, 0x3f, sizeof f);
  inf = f[0][0];
  f[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i + !i; j++) if (f[i][j] != inf) {
      for (int k = i + 1; k <= n; k++) {
        f[k][i] = min(f[k][i], f[i][j] + get(v1, j, i, k, n) + get(v2, i, k, i, k));
      }
    }
  }
  ll ans = inf;
  for (int j = 0; j < n; j++) {
    ans = min(ans, f[n][j]);
  }
  printf("%lld\n", ans);
}
