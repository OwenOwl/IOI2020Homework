#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 555;
int n, mod, f[N], g[N], dp[N][N];
vector<pair<int, int>> a;

int main() {
  scanf("%d%d", &n, &mod);
  for (int i = 0; i < n << 1; i++) {
    for (int j = 0; j < n << 1; j++) if (i * i + j * j < n * n) f[i] = j + 1;
    for (int j = 0; j < n << 1; j++) if (i * i + j * j <= (n << 1) * (n << 1)) g[i] = j + 1;
  }
  for (int i = 0; i < n; i++) {
    a.emplace_back(f[i], i);
  }
  for (int i = n; i < n << 1; i++) {
    a.emplace_back(g[i], i);
  }
  sort(a.begin(), a.end(), [&](pair<int, int> &a, pair<int, int> &b){return a.first == b.first ? a.second > b.second : a.first < b.first;});
  int ans = 0;
  for (int k = 0; k <= n; k++) {
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < n << 1; i++) {
      for (int j = 0; j <= i; j++) if (dp[i][j]) {
        dp[i + 1][j] = (dp[i + 1][j] + (ll) dp[i][j] * max(0, a[i].first - (i - j))) % mod;
        if (a[i].second < n) {
          dp[i + 1][j + 1] = (dp[i + 1][j + 1] + (ll) dp[i][j] * max(0, g[a[i].second] - (k + n + j))) % mod;
        }
      }
    }
    if (k & 1) {
      ans = (ans + mod - dp[n << 1][n - k]) % mod;
    } else {
      ans = (ans + dp[n << 1][n - k]) % mod;
    }
  }
  printf("%d\n", ans);
}
