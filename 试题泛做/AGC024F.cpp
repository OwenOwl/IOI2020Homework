#include <bits/stdc++.h>
using namespace std;

const int N = 1048576;
int n, K, f[21][N], g[21][N];
char s[N];

int main() {
  scanf("%d%d", &n, &K);
  for (int i = 0; i <= n; i++) {
    scanf("%s", s);
    for (int j = 0; j < 1 << i; j++) {
      f[i][j] = s[j] - '0';
    }
  }
  for (int i = 1; i <= n; i++) {
    g[i][0] = -1;
    for (int j = 1; j < 1 << i - 1; j++) {
      g[i][j] = 32 - __builtin_clz(j);
    }
    for (int j = 1 << i - 1; j < 1 << i; j++) {
      g[i][j] = 32 - __builtin_clz(j ^ (1 << i) - 1);
    }
    g[i][(1 << i) - 1] = -1;
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 1; i + j <= n; j++) {
      for (int k = 0; k < 1 << i + j; k++) {
        f[i][k >> j] += f[i + j][k];
        int r = g[j][k & (1 << j) - 1];
        if (~r) f[i + r][k >> j << r | (k & (1 << r) - 1)] += f[i + j][k];
      }
    }
  }
  int len = 0, ans = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = (1 << i) - 1; ~j; j--) {
      if (f[i][j] >= K) {
        len = i, ans = j;
      }
    }
  }
  for (int j = len - 1; ~j; j--) {
    putchar(48 + (ans >> j & 1));
  }
}
