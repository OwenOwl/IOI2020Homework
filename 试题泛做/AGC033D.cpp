#include <bits/stdc++.h>
using namespace std;

const int N = 187;
int n, m;
char s[N][N];
int f[2][N][N][N], g[2][N][N][N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
  }
  memset(f, -1, sizeof f);
  memset(g, -1, sizeof g);
  for (int k = n; k; k--) {
    for (int l = 1; l <= m; l++) {
      int same = 1;
      for (int r = l; r <= m; r++) {
        if (s[k][r] != s[k][l]) same = 0;
        if (!same) {
          f[0][k][l][r] = -1;
        } else if (k == n || s[k + 1][l] != s[k][l] || f[0][k + 1][l][r] == -1) {
          f[0][k][l][r] = k;
        } else {
          f[0][k][l][r] = f[0][k + 1][l][r];
        }
      }
    }
  }
  for (int k = m; k; k--) {
    for (int l = 1; l <= n; l++) {
      int same = 1;
      for (int r = l; r <= n; r++) {
        if (s[l][k] != s[r][k]) same = 0;
        if (!same) {
          g[0][k][l][r] = -1;
        } else if (k == m || s[l][k + 1] != s[l][k] || g[0][k + 1][l][r] == -1) {
          g[0][k][l][r] = k;
        } else {
          g[0][k][l][r] = g[0][k + 1][l][r];
        }
      }
    }
  }
  for (int tim = 0, p = 0; ; tim++, p = !p) {
    if (f[p][1][1][m] == n) {
      printf("%d\n", tim);
      return 0;
    }
    memset(f[!p], -1, sizeof f[!p]);
    memset(g[!p], -1, sizeof g[!p]);
    for (int k = n; k; k--) {
      for (int l = 1; l <= m; l++) {
        for (int r = l; r <= m; r++) if (f[p][k][l][r] != -1) {
          int s = f[p][k][l][r];
          f[!p][k][l][r] = max(f[!p][k][l][r], s == n || f[p][s + 1][l][r] == -1 ? s : f[p][s + 1][l][r]);
          g[!p][l][k][f[!p][k][l][r]] = max(g[!p][l][k][f[!p][k][l][r]], r);
        }
      }
    }
    for (int k = m; k; k--) {
      for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) if (g[p][k][l][r] != -1) {
          int s = g[p][k][l][r];
          g[!p][k][l][r] = max(g[!p][k][l][r], s == m || g[p][s + 1][l][r] == -1 ? s : g[p][s + 1][l][r]);
          f[!p][l][k][g[!p][k][l][r]] = max(f[!p][l][k][g[!p][k][l][r]], r);
        }
      }
    }
    for (int k = 1; k <= n; k++) {
      for (int t = m; t; t--) {
        for (int l = 1, r = t; r <= m; l++, r++) {
          if (l > 1) f[!p][k][l][r] = max(f[!p][k][l][r], f[!p][k][l - 1][r]);
          if (r < m) f[!p][k][l][r] = max(f[!p][k][l][r], f[!p][k][l][r + 1]);
        }
      }
    }
    for (int k = 1; k <= m; k++) {
      for (int t = n; t; t--) {
        for (int l = 1, r = t; r <= n; l++, r++) {
          if (l > 1) g[!p][k][l][r] = max(g[!p][k][l][r], g[!p][k][l - 1][r]);
          if (r < n) g[!p][k][l][r] = max(g[!p][k][l][r], g[!p][k][l][r + 1]);
        }
      }
    }
  }
}
