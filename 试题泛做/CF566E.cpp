#include <bits/stdc++.h>
using namespace std;

const int N = 1024;
typedef bitset<N> Set;
int n, m, color[N], deg[N], fix[N];
Set a[N], c[N];
set<pair<int, int>> mp;
vector<int> G[N];

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d", &x);
    while (x--) {
      scanf("%d", &y);
      a[i].set(y);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      Set d = a[i] & a[j];
      if (d.count() == 2) {
        int x = (int) d._Find_first(), y = (int) d._Find_next(x);
        if (x > y) swap(x, y);
        color[x] = color[y] = 1;
        if (mp.find(make_pair(x, y)) == mp.end()) {
          mp.insert(make_pair(x, y));
          G[x].push_back(y);
          G[y].push_back(x);
          deg[x]++;
          deg[y]++;
          ++m;
          printf("%d %d\n", x, y);
        }
      }
    }
  }
  if (m == 0) {
    for (int i = 2; i <= n; i++) {
      printf("1 %d\n", i);
    }
    return 0;
  } else if (m == 1) {
    int u = mp.begin()->first, v = mp.begin()->second;
    for (int i = 1; i <= n; i++) if ((int) a[i].count() != n) {
      for (int j = 1; j <= n; j++) if (j != u && j != v) {
        if (a[i].test(j)) {
          printf("%d %d\n", j, u);
        } else {
          printf("%d %d\n", j, v);
        }
      }
      return 0;
    }
  }
  memcpy(fix, color, sizeof color);
  for (int i = 1; i <= n; i++) if (color[i] == 1) {
    for (auto j : G[i]) {
      c[i].set(j);
    }
    c[i].set(i);
  }
  Set nonleaf;
  for (int i = 1; i <= n; i++) if (color[i] == 1) {
    nonleaf.set(i);
  }
  for (int x = 1; x <= n; x++) if (color[x] == 1 && deg[x] == 1) {
    int ok = 0;
    for (int i = 1; i <= n && !ok; i++) {
      Set d = a[i] & nonleaf;
      if (d == c[x]) {
        ok = 1;
        Set d2 = a[i] ^ c[x];
        for (int y = (int) d2._Find_first(); y != (int) d2.size(); y = (int) d2._Find_next(y)) {
          printf("%d %d\n", y, x);
          G[y].push_back(x);
          G[x].push_back(y);
          fix[y] = 1;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) if (fix[i] == 1) {
    for (auto j : G[i]) {
      c[i].set(j);
    }
    c[i].set(i);
  }
  for (int i = 1; i <= n; i++) if (fix[i] == 1) {
    nonleaf.set(i);
  }
  for (int x = 1; x <= n; x++) if (color[x] == 1 && deg[x] != 1) {
    int ok = 0;
    for (int i = 1; i <= n && !ok; i++) {
      Set d = a[i] & nonleaf;
      if (d == c[x]) {
        ok = 1;
        Set d2 = a[i] ^ c[x];
        for (int y = (int) d2._Find_first(); y != (int) d2.size(); y = (int) d2._Find_next(y)) {
          printf("%d %d\n", y, x);
          G[y].push_back(x);
          G[x].push_back(y);
          fix[y] = 1;
        }
      }
    }
  }
}
