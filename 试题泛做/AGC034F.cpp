#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1 << 18, mod = 998244353;
int n, x[N], p[N];
int qpow(int b, int p) {int r = 1; for (; p; p >>= 1, b = (ll) b * b % mod) if (p & 1) r = (ll) r * b % mod; return r;}
void FWT(int *a, int fl) {
  for (int k = 1; k < 1 << n; k <<= 1) {
    for (int i = 0; i < 1 << n; i += k << 1) {
      for (int j = 0; j < k; j++) {
        int x = a[i + j], y = a[i + j + k];
        a[i + j] = (x + y) % mod;
        a[i + j + k] = (x - y + mod) % mod;
        if (fl) {
          a[i + j] = (ll) a[i + j] * (mod + 1) / 2 % mod;
          a[i + j + k] = (ll) a[i + j + k] * (mod + 1) / 2 % mod;
        }
      }
    }
  }
}
int main() {
  scanf("%d", &n);
  int s = 0;
  for (int i = 0; i < 1 << n; i++) {
    scanf("%d", &p[i]);
    s += p[i];
  }
  for (int i = 0; i < 1 << n; i++) {
    p[i] = (ll) p[i] * qpow(s, mod - 2) % mod;
    x[i] = i == 0 ? (1 << n) - 1 : mod - 1;
  }
  p[0] = (p[0] - 1 + mod) % mod;
  FWT(x, 0);
  FWT(p, 0);
  for (int i = 0; i < 1 << n; i++) {
    x[i] = (ll) x[i] * qpow(p[i], mod - 2) % mod;
  }
  FWT(x, 1);
  for (int i = 0; i < 1 << n; i++) {
    printf("%d\n", (x[i] - x[0] + mod) % mod);
  }
}
