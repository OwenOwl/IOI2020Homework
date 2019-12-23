#include <bits/stdc++.h>
using namespace std;

const int N = 444, M = N * N * 4;

vector<int> G[N], st;
int dfn[N], low[N], vis[N], bel[N], cnt, dfc;
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
int n, m, cx1[M], cy1[M], cx2[M], cy2[M];
int fix, cur[N], all = -1;
char ans[N];
bool check() {
  cnt = dfc = 0;
  st.clear();
  for (int i = 0; i < n << 1; i++) {
    dfn[i] = low[i] = vis[i] = bel[i] = 0;
    G[i].clear();
  }
  for (int i = 0; i < m; i++) {
    G[cx1[i] << 1 |  cy1[i]].push_back(cx2[i] << 1 |  cy2[i]);
    G[cx2[i] << 1 | !cy2[i]].push_back(cx1[i] << 1 | !cy1[i]);
  }
  for (int i = 0; i < fix; i++) {
    G[i << 1 | !cur[i]].push_back(i << 1 | cur[i]);
  }
  if (~all) {
    for (int i = 0; i < n; i++) {
      G[i << 1 | !all].push_back(i << 1 | all);
    }
  }
  for (int i = 0; i < n << 1; i++) if (!dfn[i]) {
    tarjan(i);
  }
  for (int i = 0; i < n; i++) {
    if (bel[i << 1] == bel[i << 1 | 1]) {
      return false;
    }
  }
  return true;
}

char typ[30], s[N];
int type[30], L;

int diff(int x) {
  for (int i = x + 1; i < L; i++) {
    if (type[i] != type[x]) return i;
  }
  return -1;
}
int main() {
  scanf("%s%d%d", typ, &n, &m);
  L = (int) strlen(typ);
  for (int i = 0; i < L; i++) {
    type[i] = typ[i] == 'V';
  }
  if (*max_element(type, type + L) == 0) all = 0;
  if (*min_element(type, type + L) == 1) all = 1;
  for (int i = 0; i < m; i++) {
    char e[3], f[3];
    scanf("%d%s%d%s", &cx1[i], e, &cx2[i], f);
    --cx1[i], --cx2[i];
    cy1[i] = e[0] == 'V';
    cy2[i] = f[0] == 'V';
  }
  scanf("%s", s);
  for (int i = 0; i < n; i++) {
    ans[i] = s[i];
    s[i] -= 'a';
    cur[i] = type[s[i]];
  }
  fix = n;
  if (check()) {
    printf("%s\n", ans);
    return 0;
  }
  int mx;
  for (mx = n - 1; mx >= 0; mx--) {
    fix = mx + 1;
    if (s[mx] == L - 1) continue;
    cur[mx] = type[s[mx] + 1];
    ans[mx] = s[mx] + 1 + 'a';
    if (check()) break;
    if (!~diff(s[mx] + 1)) continue;
    cur[mx] = !cur[mx];
    ans[mx] = diff(s[mx] + 1) + 'a';
    if (check()) break;
  }
  if (mx < 0) {
    puts("-1");
    return 0;
  }
  for (int i = mx + 1; i < n; i++) {
    cur[i] = type[0];
    ans[i] = 'a';
    fix = i + 1;
    if (check()) continue;
    cur[i] = !type[0];
    ans[i] = diff(0) + 'a';
  }
  printf("%s\n", ans);
}
