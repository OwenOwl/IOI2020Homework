#include <bits/stdc++.h>
using namespace std;
const int N = 42;
int n;
string s[N];
typedef long long ll;
ll ans, f[N][N][N], g[N][N][N][N];
ll F(int l, int r, int p);
ll G(int a, int b, int c, int d) {
  if (~g[a][b][c][d]) return g[a][b][c][d];
  ll ret = 0;
  for (int i = a; i <= b; i++) {
    for (int j = c; j <= d; j++) if (s[i][j] == '1') {
      ret += F(a, b, i) * F(c, d, j);
    }
  }
  return g[a][b][c][d] = ret;
}
ll F(int l, int r, int p) {
  if (l == r) return 1;
  if (~f[l][r][p]) return f[l][r][p];
  ll ret = 0;
  for (int i = l + 1; i <= p; i++) {
    for (int j = p; j < r; j++) {
      ret += G(l, i - 1, j + 1, r) * F(i, j, p);
    }
  }
  return f[l][r][p] = ret;
}
int main() {
  memset(f, -1, sizeof f);
  memset(g, -1, sizeof g);
  cin >> n;
  n <<= 1;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  for (int p = 1; p < n; p++) if (s[0][p] == '1') {
    ans += F(1, n - 1, p);
  }
  printf("%lld\n", ans);
}
