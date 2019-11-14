#include <bits/stdc++.h>
using namespace std;

const int N = 2022;
int n, dis[N], size[N];
vector<int> G[N];
char s[N];

void dfs(int x, int pre) {
  size[x] = s[x] - '0';
  dis[x] = 0;
  for (auto y : G[x]) if (y != pre) {
    dfs(y, x);
    size[x] += size[y];
    dis[x] += dis[y] + size[y];
  }
}
bool dfs2(int x, int pre, int d) {
  if (!d) return true;
  if (d > dis[x]) return false;
  int mx = -1, mp = 0;
  for (auto y : G[x]) if (y != pre) {
    if (dis[y] + size[y] > mx) {
      mx = dis[y] + size[y];
      mp = y;
    }
  }
  int my = dis[x] - mx;
  if (my >= mx || 2 * my >= d) return true;
  return dfs2(mp, x, d - 2 * my);
}

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  int ans = 0x3f3f3f3f;
  for (int rt = 1; rt <= n; rt++) {
    dfs(rt, 0);
    if (dis[rt] & 1) continue;
    if (dfs2(rt, 0, dis[rt])) ans = min(ans, dis[rt]);
  }
  printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans / 2);
}
