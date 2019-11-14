#include <bits/stdc++.h>
using namespace std;

const int N = 1005, M = 200233;
int n, m;
bool ok1[M], ok2[M], visit[N];
vector<pair<int, int>> G[N], rG[N];
void dfs(int x) {
  visit[x] = true;
  for (auto y : G[x]) if (!visit[y.first]) dfs(y.first);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    G[x].emplace_back(y, i);
    rG[y].emplace_back(x, i);
  }
  for (int x = 1; x <= n; x++) {
    for (int j = 1; j <= n; j++) visit[j] = false;
    dfs(x);
    for (auto y : rG[x]) ok1[y.second] = visit[y.first];
    for (int j = 1; j <= n; j++) visit[j] = false;
    visit[x] = true;
    for (auto y : G[x]) ok2[y.second] |= visit[y.first], dfs(y.first);
    reverse(G[x].begin(), G[x].end());
    for (int j = 1; j <= n; j++) visit[j] = false;
    visit[x] = true;
    for (auto y : G[x]) ok2[y.second] |= visit[y.first], dfs(y.first);
  }
  for (int i = 1; i <= m; i++) {
    puts(ok1[i] == ok2[i] ? "same" : "diff");
  }
}
