#include <bits/stdc++.h>
using namespace std;

const int N = 3033;
int n, m, q, k;
vector<int> row[N];
int cnt[N], lef[N], rit[N], pos[N], p, cur;
long long sum = 0, ans = 0;
void calc(int x) {
  cur += cnt[x];
  while (cur - cnt[p] >= k) {
    cur -= cnt[p];
    p = lef[p];
  }
  int delta = pos[x] - p;
  pos[x] = p;
  sum += delta * (x - lef[x]);
}
int main() {
  scanf("%d%d%d%d", &n, &m, &q, &k);
  for (int i = 1, x, y; i <= q; i++) {
    scanf("%d%d", &x, &y);
    row[x].push_back(y);
  }
  for (int up = 1; up <= n; up++) {
    for (int i = 1; i <= m; i++) {
      cnt[i] = 0;
    }
    for (int i = up; i <= n; i++) {
      for (auto x : row[i]) {
        cnt[x]++;
      }
    }
    for (int i = 1, lst = 0; i <= m + 1; i++) if (cnt[i] || i == m + 1) {
      lef[i] = lst;
      rit[lst] = i;
      pos[i] = m + 1;
      lst = i;
    }
    p = m + 1, cur = 0, sum = 0;
    for (int i = lef[m + 1]; i; i = lef[i]) {
      calc(i);
    }
    for (int dw = n; dw >= up; dw--) {
      ans += sum;
      for (auto x : row[dw]) {
        cnt[x]--;
        p = x, cur = 0;
        for (; p != (pos[x] == m + 1 ? m + 1 : rit[pos[x]]); p = rit[p], cur += cnt[p]);
        for (int y = x, tm = k; tm && y; tm--, y = lef[y]) {
          calc(y);
        }
        if (cnt[x] == 0) {
          rit[lef[x]] = rit[x];
          lef[rit[x]] = lef[x];
        }
      }
    }
  }
  printf("%lld\n", ans);
}
