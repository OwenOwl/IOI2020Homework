#include <bits/stdc++.h>
using namespace std;

const int N = 900233;
int p, n, c[N], t[N], pc;
vector<int> E[N], G[N], st, P[N];

void build1() {
  pc = n << 1 | 1;
  for (int i = 1, lst; i <= p; i++) {
    lst = 0;
    for (auto x : E[i]) {
      ++pc;
      if (lst) {
        G[pc].push_back(lst);
        G[x << 1].push_back(lst);
      }
      G[pc].push_back(x << 1 | 1);
      lst = pc;
    }
    reverse(E[i].begin(), E[i].end());
    lst = 0;
    for (auto x : E[i]) {
      ++pc;
      if (lst) {
        G[pc].push_back(lst);
        G[x << 1].push_back(lst);
      }
      G[pc].push_back(x << 1 | 1);
      lst = pc;
    }
  }
  map<int, int> lst;
  for (int i = 1; i <= p; i++) {
    lst.clear();
    for (auto x : E[i]) {
      ++pc;
      if (lst[c[x]]) {
        G[pc].push_back(lst[c[x]]);
        G[x << 1 | 1].push_back(lst[c[x]]);
      }
      G[pc].push_back(x << 1);
      lst[c[x]] = pc;
    }
    reverse(E[i].begin(), E[i].end());
    lst.clear();
    for (auto x : E[i]) {
      ++pc;
      if (lst[c[x]]) {
        G[pc].push_back(lst[c[x]]);
        G[x << 1 | 1].push_back(lst[c[x]]);
      }
      G[pc].push_back(x << 1);
      lst[c[x]] = pc;
    }
  }
}
int tag[N], dfn[N], low[N], bel[N], vis[N], dfc, cnt, tim[N], deg[N];
void tarjan(int x) {
  st.push_back(x);
  vis[x] = 1;
  dfn[x] = low[x] = ++dfc;
  for (auto y : G[x]) {
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (vis[y]) {
      low[x] = min(low[x], dfn[y]);
    }
  }
  if (low[x] == dfn[x]) {
    int y;
    ++cnt;
    do {
      y = st.back();
      st.pop_back();
      bel[y] = cnt;
      vis[y] = 0;
    } while (y != x);
  }
}
void build(int lim) {
  for (int i = 1; i <= n; i++) {
    if (tag[i]) {
      tag[i] = 0;
      G[i << 1].pop_back();
    }
    if (t[i] > lim) {
      tag[i] = 1;
      G[i << 1].push_back(i << 1 | 1);
    }
  }
  for (int i = 1; i <= pc; i++) {
    dfn[i] = low[i] = bel[i] = vis[i] = 0;
  }
  dfc = cnt = 0;
  st.clear();
  for (int i = 1; i <= pc; i++) if (!dfn[i]) {
    tarjan(i);
  }
}
bool ok() {
  for (int i = 1; i <= n; i++) {
    if (bel[i << 1] == bel[i << 1 | 1]) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d%d", &p, &n);
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d%d%d", &x, &y, &c[i], &t[i]);
    E[x].push_back(i);
    E[y].push_back(i);
  }
  build1();
  int l = 0, r = 1000000000;
  build(r);
  if (ok()) {
    puts("Yes");
  } else {
    puts("No");
    return 0;
  }
  while (l < r) {
    int mid = (l + r) >> 1;
    build(mid);
    if (ok()) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%d ", l);
  build(l);
  for (int i = 1; i <= pc; i++) {
    for (auto j : G[i]) {
      if (bel[j] != bel[i]) {
        P[bel[j]].push_back(bel[i]);
        deg[bel[i]]++;
      }
    }
  }
  queue<int> q;
  for (int i = 1; i <= cnt; i++) if (!deg[i]) {
    q.push(i);
  }
  int tt = 0;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    tim[x] = ++tt;
    for (auto y : P[x]) {
      if (--deg[y] == 0) {
        q.push(y);
      }
    }
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (tim[bel[i << 1]] < tim[bel[i << 1 | 1]]) {
      ans.push_back(i);
    }
  }
  printf("%d\n", (int) ans.size());
  for (auto x : ans) {
    printf("%d ", x);
  }
}
