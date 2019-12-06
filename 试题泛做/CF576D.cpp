#include <bits/stdc++.h>
using namespace std;

const int N = 150;
bitset<N> a[N], b[N], bb[N], c, cc;
int n, m, d[N];
pair<int, pair<int, int>> e[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &e[i].second.first, &e[i].second.second, &e[i].first);
    --e[i].second.first;
    --e[i].second.second;
  }
  sort(e, e + m);
  c.set(0);
  int ans = 0x70000000;
  for (int t = 0; t < m; t++) {
    for (int i = 0; i < n; i++) b[i] = a[i];
    for (int p = e[t].first - (t == 0 ? 0 : e[t - 1].first); p; p >>= 1) {
      if (p & 1) {
        cc.reset();
        for (int i = 0; i < n; i++) {
          if ((b[i] & c).any()) cc.set(i);
        }
        c = cc;
      }
      for (int i = 0; i < n; i++) bb[i].reset();
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (b[i].test(j)) {
          bb[i] |= b[j];
        }
      }
      for (int i = 0; i < n; i++) b[i] = bb[i];
    }
    a[e[t].second.second].set(e[t].second.first);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (c.test(i)) {
        q.push(i);
        d[i] = e[t].first;
      } else {
        d[i] = -1;
      }
    }
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int y = 0; y < n; y++) if (a[y].test(x) && !~d[y]) {
        d[y] = d[x] + 1;
        q.push(y);
      }
    }
    if (~d[n - 1]) ans = min(ans, d[n - 1]);
  }
  if (ans == 0x70000000) {
    puts("Impossible");
  } else {
    printf("%d\n", ans);
  }
}
