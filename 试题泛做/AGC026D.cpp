#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 105, mod = 1000000007;
int n, h[N];

inline int qpow(int b, int p) {
  int r = 1;
  for (; p; p >>= 1) {
    if (p & 1) r = (ll) r * b % mod;
    b = (ll) b * b % mod;
  }
  return r;
}

pair<int, int> solve(int l, int r, int x) {
  int mn = mod;
  for (int i = l; i <= r; i++) {
    mn = min(mn, h[i]);
  }
  pair<int, int> p = make_pair(2, 1);
  for (int i = l; i <= r; i++) {
    if (h[i] == mn) {
      p.second = p.second * 2 % mod;
    } else {
      int j = i;
      for (; j < r && h[j + 1] > mn; j++);
      auto q = solve(i, j, mn);
      p.first = (ll) p.first * q.first % mod;
      p.second = (ll) p.second * (q.first * 2 % mod + q.second) % mod;
      i = j;
    }
  }
  p.second = (p.second + mod - p.first) % mod;
  p.first = (ll) p.first * qpow(2, mn - x - 1) % mod;
  return p;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &h[i]);
  }
  auto p = solve(1, n, 0);
  printf("%d\n", (p.first + p.second) % mod);
}
