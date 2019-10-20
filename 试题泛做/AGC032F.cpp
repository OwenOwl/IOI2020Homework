#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int main() {
  int n;
  scanf("%d", &n);
  vector<int> inv(max(n + 1, 4));
  inv[0] = inv[1] = 1;
  for (int i = 2; i <= max(n, 3); i++) {
    inv[i] = mod - (ll) mod / i * inv[mod % i] % mod;
  }
  int ans = 0, coef = inv[n];
  for (int i = 0; i < n; i++) {
    coef = (ll) coef * inv[3] % mod;
    ans = (ans + (ll) coef * inv[n - i]) % mod;
  }
  printf("%d\n", ans);
}

