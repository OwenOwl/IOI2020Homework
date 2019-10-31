#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, c[N];
vector<int> G[N];

int reach(int x, int fa, int lim) {
  int ret = 0;
  for (auto y : G[x]) if (y != fa) {
    if (y < lim) {
      ret += reach(y, x, lim) + 1;
    }
  }
  return ret;
}
void dfs(int x, int fa, int m0, int m1) {
  if (x > m1) {
    c[x] = c[fa] + 1 + reach(x, fa, m0);
  } else if (m0 > m1) {
    c[x] = c[fa] + reach(x, fa, m0) - reach(x, fa, m1);
  } else {
    c[x] = c[fa];
  }
  for (auto y : G[x]) if (y != fa) {
    dfs(y, x, max(m0, x), max(m1, fa));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  c[1] = 0;
  dfs(1, 0, 1, 1);
  for (int i = 2; i <= n; i++) {
    printf("%d ", c[i]);
  }
}
