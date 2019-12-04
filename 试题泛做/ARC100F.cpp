#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 25020, K = 404, mod = 1000000007;
int n, k, m, a[N], vis[K], fw[K], ft[K], gw[K], gt[K], f[N][K], g[N][K];
int qpow(int b, int p) {
  int r = 1;
  for (; p; p >>= 1, b = (ll) b * b % mod) if (p & 1) r = (ll) r * b % mod;
  return r;
}
int main() {
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d", &a[i]);
  }
  int ans = (ll) (n - m + 1) * qpow(k, n - m) % mod;
  if (m >= k) {
    int ok = 0;
    for (int i = 1; i + k - 1 <= m; i++) {
      for (int j = 1; j <= k; j++) vis[j] = 0;
      for (int j = 1; j <= k; j++) vis[a[i + j - 1]] = 1;
      ok |= *min_element(vis + 1, vis + 1 + k);
    }
    if (ok) return printf("%d\n", ans), 0;
  }
  int tl = 0, tr = 0;
  for (int j = 1; j <= k; j++) vis[j] = 0;
  for (int i = 1; i <= m; i++) {
    if (!tl && vis[a[i]]) tl = i - 1;
    vis[a[i]] = 1;
  }
  for (int j = 1; j <= k; j++) vis[j] = 0;
  for (int i = m; i; i--) {
    if (!tr && vis[a[i]]) tr = m - i;
    vis[a[i]] = 1;
  }
  int ret = 0;
  if (tl) {
    f[0][tl] = 1;
    g[0][tr] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < k; j++) {
        f[i][1] = (f[i][1] + f[i - 1][j]) % mod;
        g[i][1] = (g[i][1] + g[i - 1][j]) % mod;
        if (j + 1 < k) f[i][j + 1] = (f[i][j + 1] + (ll) f[i - 1][j] * (k - j - 1)) % mod;
        if (j + 1 < k) g[i][j + 1] = (g[i][j + 1] + (ll) g[i - 1][j] * (k - j - 1)) % mod;
        if (j + 2 < k) f[i][j + 2] = (f[i][j + 2] + (ll) f[i - 1][j] * (mod - k + j)) % mod;
        if (j + 2 < k) g[i][j + 2] = (g[i][j + 2] + (ll) g[i - 1][j] * (mod - k + j)) % mod;
      }
      for (int j = 1; j < k; j++) {
        f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
        g[i][j] = (g[i][j] + g[i][j - 1]) % mod;
      }
    }
    for (int i = 0; i <= n - m; i++) {
      int lt = 0, rt = 0;
      for (int j = 1; j < k; j++) {
        lt = (lt + f[i][j]) % mod;
        rt = (rt + g[n - m - i][j]) % mod;
      }
      ret = (ret + (ll) lt * rt) % mod;
    }
  } else {
    fw[1] = k;
    ft[1] = m == 1 ? k : 0;
    for (int td = 2; td <= n; td++) {
      memset(gw, 0, sizeof gw);
      memset(gt, 0, sizeof gt);
      for (int j = 1; j < k; j++) {
        gw[1] = (gw[1] + fw[j]) % mod;
        gt[1] = (gt[1] + ft[j]) % mod;
        if (j + 1 < k) gw[j + 1] = (gw[j + 1] + (ll) fw[j] * (k - j - 1)) % mod;
        if (j + 1 < k) gt[j + 1] = (gt[j + 1] + (ll) ft[j] * (k - j - 1)) % mod;
        if (j + 2 < k) gw[j + 2] = (gw[j + 2] + (ll) fw[j] * (mod - k + j)) % mod;
        if (j + 2 < k) gt[j + 2] = (gt[j + 2] + (ll) ft[j] * (mod - k + j)) % mod;
      }
      for (int j = 1; j < k; j++) {
        gw[j] = (gw[j] + gw[j - 1]) % mod;
        gt[j] = (gt[j] + gt[j - 1]) % mod;
      }
      for (int j = m; j < k; j++) {
        gt[j] = (gt[j] + gw[j]) % mod;
      }
      memcpy(fw, gw, sizeof fw);
      memcpy(ft, gt, sizeof ft);
    }
    for (int j = 1; j < k; j++) {
      ret = (ret + ft[j]) % mod;
    }
    for (int j = k; j > k - m; j--) {
      ret = (ll) ret * qpow(j, mod - 2) % mod;
    }
  }
  ans = (ans + mod - ret) % mod;
  printf("%d\n", ans);
}
