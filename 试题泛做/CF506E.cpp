#include <bits/stdc++.h>
using namespace std;

const int N = 305, mod = 10007;
char s[N];
int n, m, M, f[N][N][N], g[N], h[N];

struct matrix {
  int a[N][N];
  matrix () {memset(a, 0, sizeof a);}
  matrix operator * (const matrix &d) const {
    matrix t;
    for (int i = 0; i <= M; i++) {
      for (int j = 0; j <= M; j++) {
        for (int k = 0; k <= M; k++) {
          t.a[i][k] = (t.a[i][k] + a[i][j] * d.a[j][k]) % mod;
        }
      }
    }
    return t;
  }
};
matrix qpow(matrix b, int p) {
  ++p;
  matrix r;
  for (int i = 0; i <= M; i++) r.a[i][i] = 1;
  for (; p; p >>= 1) {
    if (p & 1) r = r * b;
    b = b * b;
  }
  return r;
}

int main() {
  scanf("%s%d", s, &m);
  n = (int) strlen(s);
  f[0][n - 1][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = n - 1; j >= i; j--) {
      for (int k = 0; k <= n; k++) if (f[i][j][k]) {
        if (s[i] == s[j]) {
          f[i + 1][j - 1][k] = (f[i + 1][j - 1][k] + f[i][j][k]) % mod;
          if (i + 1 > j - 1) {
            g[k] = (g[k] + f[i][j][k]) % mod;
          }
          if (i + 1 == j) {
            h[k] = (h[k] + f[i][j][k]) % mod;
          }
        } else {
          f[i + 1][j][k + 1] = (f[i + 1][j][k + 1] + f[i][j][k]) % mod;
          f[i][j - 1][k + 1] = (f[i][j - 1][k + 1] + f[i][j][k]) % mod;
        }
      }
    }
  }
  int ans = 0;
  M = n + (n + 1 >> 1) + 1;
  {
    matrix T;
    T.a[M][M] = 26;
    for (int i = 0; i <= n; i++) {
      if (i) T.a[i][i] = 24;
      T.a[i][M - (n - i + 1 >> 1)] = g[i];
      if (i < n) T.a[i][i + 1] = 1;
    }
    for (int i = n + 1; i < M; i++) {
      T.a[i][i] = 25;
      T.a[i][i + 1] = 1;
    }
    T = qpow(T, (n + m + 1) >> 1);
    ans = (ans + T.a[0][M]) % mod;
  }
  if ((n + m) & 1) {
    matrix T;
    T.a[M][M] = 0;
    for (int i = 0; i <= n; i++) {
      if (i) T.a[i][i] = 24;
      T.a[i][M - (n - i + 1 >> 1)] = h[i];
      if (i < n) T.a[i][i + 1] = 1;
    }
    for (int i = n + 1; i < M; i++) {
      T.a[i][i] = 25;
      T.a[i][i + 1] = 1;
    }
    T = qpow(T, (n + m + 1) >> 1);
    ans = (ans + mod - T.a[0][M]) % mod;
  }
  printf("%d\n", ans);
}
