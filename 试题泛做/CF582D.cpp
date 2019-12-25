#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 4050, mod = 1000000007;
int p, a, f[N][2][2], g[N][2][2];
string s2;
vector<int> s;
void add(int &x, int y) {
  x = (x + y) % mod;
}
int main() {
  cin >> p >> a >> s2;
  reverse(s2.begin(), s2.end());
  if (s2.back() == '0') s2.pop_back();
  while (!s2.empty()) {
    int x = 0;
    ll y = 0;
    for (int i = (int) s2.length() - 1; i >= 0; i--) {
      x = ((ll) x * 10 + s2[i] - '0') % p;
      y = y * 10 + s2[i] - '0';
      s2[i] = y / p + '0';
      y %= p;
    }
    s.push_back(x);
    while (!s2.empty() && s2.back() == '0') s2.pop_back();
  }
  if (s.empty()) s.push_back(0);
  f[0][0][0] = 1;
  for (int i = 0; i < (int) s.size(); i++) {
    memset(g, 0, sizeof g);
    for (int x = 0; x <= 1; x++) {
      for (int y = 0; y <= 1; y++) {
        for (int j = 0; j <= i; j++) if (f[j][x][y]) {
          // y + a + b <=> s[i]
          int z = f[j][x][y], v = s[i] - x - y;
          v = min(v, p - 2);
          v = max(v, -1);
          add(g[j + 0][0][0], (ll) (v + 1) * (v + 2) / 2 % mod * z % mod);          // a + b <= v
          add(g[j + 0][1][0], (ll) (p + v + 1) * (p - 2 - v) / 2 % mod * z % mod);  // a + b > v, a + b < p - 1
          int t = x ? (y + p - 1) % p >= s[i] : (y + p - 1) % p > s[i];
          add(g[j + y][t][y], (ll) p * z % mod); // a + b = p - 1
          add(g[j + 1][0][1], (ll) (p * 2 - 2 - v) * (v + 1) / 2 % mod * z % mod); // a + b >= p, a + b - p <= v
          add(g[j + 1][1][1], (ll) (p - 1 - v) * (p - 2 - v) / 2 % mod * z % mod); // a + b >= p, a + b - p > v
        }
      }
    }
    memcpy(f, g, sizeof g);
  }
  int ans = 0;
  for (int j = a; j <= (int) s.size(); j++) {
    ans = (ans + f[j][0][0]) % mod;
  }
  printf("%d\n", ans);
}
