#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 500233;
int n, q, type[N], qx[N], qy[N];
vector<int> query[N], st[N];
int tim[N], com[N], bel[N], tag[N];
ll cur[N], add[N], ans[N];

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= q; i++) {
    char s[4];
    scanf("%s", s);
    if (s[0] == 'U') {
      type[i] = 1;
      scanf("%d%d", &qx[i], &qy[i]);
    } else if (s[0] == 'M') {
      type[i] = 2;
      scanf("%d%d", &qx[i], &qy[i]);
    } else if (s[0] == 'A') {
      type[i] = 3;
      scanf("%d", &qx[i]);
    } else if (s[0] == 'Z') {
      type[i] = 4;
      scanf("%d", &qx[i]);
    } else if (s[0] == 'Q') {
      type[i] = 5;
      scanf("%d", &qx[i]);
    }
  }
  for (int i = 1; i <= n; i++) {
    st[i].clear();
    st[i].push_back(i);
    bel[i] = i;
    tag[i] = tim[i] = com[i] = 0;
  }
  for (int i = 1; i <= q; i++) {
    if (type[i] == 2) {
      int x = bel[qx[i]], y = bel[qy[i]];
      if (st[x].size() < st[y].size()) swap(x, y);
      for (auto d : st[y]) {
        if (com[d] < tag[y]) tim[d] = tag[y];
        com[d] = i;
        bel[d] = x;
        st[x].push_back(d);
      }
    } else if (type[i] == 4) {
      int x = bel[qx[i]];
      tag[x] = i;
    } else if (type[i] == 5) {
      int x = qx[i];
      int t = tim[x];
      if (com[x] < tag[bel[x]]) t = tag[bel[x]];
      query[t].push_back(-i);
      query[i].push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    st[i].clear();
    st[i].push_back(i);
    bel[i] = i;
    cur[i] = add[i] = 0;
  }
  for (int i = 1; i <= q; i++) {
    if (type[i] == 1) {
      int x = bel[qx[i]], y = bel[qy[i]];
      if (st[x].size() < st[y].size()) swap(x, y);
      for (auto d : st[y]) {
        cur[d] += add[y] - add[x];
        bel[d] = x;
        st[x].push_back(d);
      }
    } else if (type[i] == 3) {
      int x = bel[qx[i]];
      add[x] += (ll) st[x].size();
    }
    for (auto x : query[i]) {
      int y = qx[abs(x)];
      ll t = add[bel[y]] + cur[y];
      ans[abs(x)] += x < 0 ? -t : t;
    }
  }
  for (int i = 1; i <= q; i++) if (type[i] == 5) {
    printf("%lld\n", ans[i]);
  }
}
