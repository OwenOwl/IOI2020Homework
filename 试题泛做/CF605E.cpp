#include <bits/stdc++.h>
using namespace std;

const int N = 1002;
int n, m, q[N], vis[N];
double p[N][N], f[N], prod[N], sum[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x;
      scanf("%d", &x);
      p[i][j] = x / 100.0;
    }
    prod[i] = 1;
  }
  f[n] = 0;
  vis[n] = 1;
  q[++m] = n;
  while (m < n) {
    double g = 0;
    int v = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
      sum[i] += f[q[m]] * p[i][q[m]] * prod[i];
      prod[i] *= 1 - p[i][q[m]];
      double cur = (sum[i] + 1) / (1 - prod[i]);
      if (!v || cur < g) {
        g = cur;
        v = i;
      }
    }
    f[v] = g;
    vis[v] = 1;
    q[++m] = v;
  }
  printf("%.10lf\n", f[1]);
}
