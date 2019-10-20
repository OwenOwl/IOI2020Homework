#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 500233, V = 10000003, mod = 1000000007;
int n, a[N], pw[N];

int notp[V], pri[V], pc = 0, minp[V], mu[V];
int cnt[V];

int main() {
  scanf("%d", &n);
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    pw[i] = (pw[i - 1] << 1) % mod;
  }
  notp[1] = 1;
  mu[1] = 1;
  for (int i = 1; i < V; i++) {
    if (!notp[i]) {
      pri[++pc] = i;
      minp[i] = i;
      mu[i] = mod - 1;
    }
    for (int j = 1; j <= pc && i * pri[j] < V; j++) {
      notp[i * pri[j]] = true;
      minp[i * pri[j]] = pri[j];
      if (!(i % pri[j])) {
        mu[i * pri[j]] = 0;
        break;
      } else {
        mu[i * pri[j]] = (mod - mu[i]) % mod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    vector<int> s;
    while (x != 1) {
      int y = minp[x];
      s.push_back(y);
      while (!(x % y)) {
        x /= y;
      }
    }
    for (int S = 0; S < 1 << (int) s.size(); S++) {
      int z = 1;
      for (int j = 0; j < (int) s.size(); j++) if ((S >> j) & 1) {
        z *= s[j];
      }
      cnt[z]++;
    }
  }
  int A = 0, B = 0;
  for (int i = 1; i < V; i++) if (mu[i]) {
    A = (A + (ll) mu[i] * (pw[cnt[i]] - (i != 1))) % mod;
  }
  B = (mod + pw[n] - A) % mod;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + B) % mod;
    int x = a[i];
    vector<int> s;
    while (x != 1) {
      int y = minp[x];
      s.push_back(y);
      while (!(x % y)) {
        x /= y;
      }
    }
    for (int S = 1; S < 1 << (int) s.size(); S++) {
      int z = 1;
      for (int j = 0; j < (int) s.size(); j++) if ((S >> j) & 1) {
        z *= s[j];
      }
      ans = (ans + (ll) mu[z] * (pw[cnt[z]] - 1)) % mod;
    }
  }
  printf("%d\n", ans);
}
