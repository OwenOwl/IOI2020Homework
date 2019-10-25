#include <bits/stdc++.h>
using namespace std;

const int N = 630;
int n, D1, D2, col[N][N], ban[N][N];
vector<pair<int, int>> c, v[2];

void dfs(int x, int y) {
  for (auto d : c) {
    int ux = x + d.first, uy = y + d.second;
    if (ux < 0 || ux >= n || uy < 0 || uy >= n || ban[ux][uy] || ~col[ux][uy]) continue;
    col[ux][uy] = !col[x][y];
    v[col[ux][uy]].emplace_back(ux, uy);
    dfs(ux, uy);
  }
}
void solve(int D) {
  for (int i = -n; i <= n; i++) {
    for (int j = -n; j <= n; j++) {
      if (i * i + j * j == D) {
        c.emplace_back(i, j);
      }
    }
  }
  memset(col, -1, sizeof col);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!ban[i][j] && !~col[i][j]) {
        v[0].clear(), v[1].clear();
        col[i][j] = 0;
        v[0].emplace_back(i, j);
        dfs(i, j);
        if ((int) v[0].size() > (int) v[1].size()) swap(v[0], v[1]);
        for (auto d : v[0]) {
          ban[d.first][d.second] = 1;
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &D1, &D2);
  n <<= 1;
  solve(D1);
  solve(D2);
  for (int i = 0, b = (n >> 1) * (n >> 1); i < n && b; i++) {
    for (int j = 0; j < n && b; j++) {
      if (!ban[i][j]) {
        --b;
        printf("%d %d\n", i, j);
      }
    }
  }
}
