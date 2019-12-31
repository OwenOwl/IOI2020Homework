#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, w[N];
vector<pair<int, int>> G[N];

int visit[N], size[N], son[N];
void dfs1(int x, int pre) {
  size[x] = 1;
  son[x] = 0;
  for (auto e : G[x]) {
    int y = e.first;
    if (y == pre || visit[y]) continue;
    dfs1(y, x);
    size[x] += size[y];
    if (!son[x] || size[son[x]] < size[y]) {
      son[x] = y;
    }
  }
}
double der[N];
double calc(int x, int pre, int dis) {
  double ret = pow(dis, 0.5) * 1.5 * w[x];
  for (auto e : G[x]) {
    int y = e.first, d = e.second;
    if (y == pre) continue;
    ret += calc(y, x, dis + d);
  }
  return ret;
}
double calc2(int x, int pre, int dis) {
  double ret = pow(dis, 1.5) * w[x];
  for (auto e : G[x]) {
    int y = e.first, d = e.second;
    if (y == pre) continue;
    ret += calc2(y, x, dis + d);
  }
  return ret;
}
void divide(int g) {
  dfs1(g, 0);
  int n = size[g];
  while (son[g] && size[son[g]] << 1 >= n) {
    g = son[g];
  }
  visit[g] = 1;
  double s = 0;
  for (auto e : G[g]) {
    int y = e.first, d = e.second;
    der[y] = calc(y, g, d);
    s += der[y];
  }
  for (auto e : G[g]) {
    int y = e.first;
    if (der[y] * 2 > s) {
      if (!visit[y]) {
        divide(y);
      } else {
        double a = calc2(g, 0, 0);
        double b = calc2(y, 0, 0);
        printf("%d %.10lf\n", a < b ? g : y, a < b ? a : b);
      }
      return;
    }
  }
  printf("%d %.10lf\n", g, calc2(g, 0, 0));
}
int main() {
  scanf("%d", &n);
  if (n == 1) {
    puts("1 0");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
  }
  for (int i = 1, x, y, z; i < n; i++) {
    scanf("%d%d%d", &x, &y, &z);
    G[x].emplace_back(y, z);
    G[y].emplace_back(x, z);
  }
  divide(1);
}
