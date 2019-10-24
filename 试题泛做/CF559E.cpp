#include <bits/stdc++.h>
using namespace std;
const int N = 304;
int m, n, a[N], b[N], x[N], l[N], r[N], s[N][N], t[N], f[N];
int main() {
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a[i], &b[i]);
    x[++n] = a[i];
    x[++n] = a[i] - b[i];
    x[++n] = a[i] + b[i];
  }
  sort(x + 1, x + 1 + n);
  n = int (unique(x + 1, x + 1 + n) - x - 1);
  for (int i = 1; i <= m; i++) {
    int t = int (lower_bound(x + 1, x + 1 + n, a[i]) - x);
    l[t] = int (lower_bound(x + 1, x + 1 + n, a[i] - b[i]) - x);
    r[t] = int (lower_bound(x + 1, x + 1 + n, a[i] + b[i]) - x);
  }
  for (int i = 2; i <= n; i++) if (l[i]) {
    s[i][i] = i;
    for (int j = i + 1, k = i; j <= n; j++) {
      s[i][j] = s[i][j - 1];
      if (j <= r[i] && l[j]) {
        s[i][j] = min(s[i][j], l[j]);
      }
      while (k > s[i][j]) {
        --k;
        if (l[k]) s[i][j] = min(s[i][j], l[k]);
      }
    }
    t[i] = l[i];
    int k = i;
    while (k > t[i]) {
      --k;
      if (l[k]) t[i] = min(t[i], l[k]);
    }
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) if (l[j]) {
      f[i] = max(f[i], f[s[j][i - 1]] + x[min(i, r[j])] - x[s[j][i - 1]]);
      f[i] = max(f[i], f[t[j]] + x[j] - x[t[j]]);
    }
  }
  printf("%d\n", f[n]);
}
