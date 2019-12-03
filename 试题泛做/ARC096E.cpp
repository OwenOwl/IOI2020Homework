#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3022;
int n, mod, C[N][N], S[N][N], ans;
int qpow(int b, int p, int d) {
  int r = 1;
  for (; p; p >>= 1, b = (ll) b * b % d) if (p & 1) {
    r = (ll) r * b % d;
  }
  return r;
}
int main() {
  scanf("%d%d", &n, &mod);
  C[0][0] = S[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    S[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
      S[i][j] = (S[i - 1][j - 1] + (ll) S[i - 1][j] * (j + 1)) % mod;
    }
  }
  for (int i = 0; i <= n; i++) {
    int c = qpow(2, qpow(2, n - i, mod - 1), mod), coef = qpow(2, n - i, mod);
    for (int j = 0; j <= i; j++, c = (ll) c * coef % mod) {
      ans = (ans + (ll) (i & 1 ? mod - 1 : 1) * C[n][i] % mod * S[i][j] % mod * c) % mod;
    }
  }
  printf("%d\n", ans);
}
