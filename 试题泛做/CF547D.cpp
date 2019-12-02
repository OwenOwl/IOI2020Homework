#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, x[N], y[N], v[N];
vector<int> G[N];
void dfs(int x) {
  for (auto y : G[x]) if (!~v[y]) v[y] = !v[x], dfs(y);
}
int main() {
  scanf("%d", &n);
  for (int i = 1, a, b; i <= n; i++) {
    scanf("%d%d", &a, &b);
    if (x[a]) {
      G[x[a]].push_back(i);
      G[i].push_back(x[a]);
      x[a] = 0;
    } else {
      x[a] = i;
    }
    if (y[b]) {
      G[y[b]].push_back(i);
      G[i].push_back(y[b]);
      y[b] = 0;
    } else {
      y[b] = i;
    }
  }
  memset(v, -1, sizeof v);
  for (int i = 1; i <= n; i++) {
    if (!~v[i]) {
      v[i] = 0;
      dfs(i);
    }
    putchar(v[i] ? 'b' : 'r');
  }
}
