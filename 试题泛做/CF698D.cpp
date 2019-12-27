#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
bool check(int ax, int ay, int bx, int by, int cx, int cy) {
  return (ll) (ax - cx) * (by - cy) - (ll) (ay - cy) * (bx - cx) == 0 && (ll) (ax - cx) * (bx - cx) + (ll) (ay - cy) * (by - cy) < 0;
}
const int K = 10, N = 1033;
int k, n, ax[K], ay[K], bx[N], by[N], p[K], q[K], vis[N], tim = 0;
vector<int> s[N][K];

int main() {
  scanf("%d%d", &k, &n);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &ax[i], &ay[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &bx[i], &by[i]);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      for (int l = 1; l <= n; l++) if (l != i) {
        if (check(bx[i], by[i], ax[j], ay[j], bx[l], by[l])) s[i][j].push_back(l);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) p[j] = j;
    do {
      int l = 1, r = 0;
      q[++r] = i;
      vis[i] = ++tim;
      for (; l <= r && r <= k; l++) {
        int x = q[l], y = p[l];
        for (auto z : s[x][y]) if (vis[z] != tim) {
          q[++r] = z;
          vis[z] = tim;
          if (r > k) break;
        }
      }
      if (r <= k) {
        ans++;
        break;
      }
    } while (next_permutation(p + 1, p + 1 + k));
  }
  printf("%d\n", ans);
}
