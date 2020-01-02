#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, m, fa[N], vis[N], ins[N], s[N], dep[N];
vector<int> G[N];
vector<pair<int, int>> v;

void dfs(int x, int pre) {
  vis[x] = 1;
  ins[x] = 1;
  fa[x] = pre;
  dep[x] = dep[pre] + 1;
  for (auto y : G[x]) if (y != pre) {
    if (ins[y]) {
      v.emplace_back(x, y);
    } else if (!vis[y]) {
      dfs(y, x);
    }
  }
  ins[x] = 0;
}
bool isfa(int x, int y) {
  for (; x; x = fa[x]) {
    if (x == y) return true;
  }
  return false;
}
int lca(int x, int y) {
  while (x != y) {
    if (dep[x] > dep[y]) x = fa[x];
    else y = fa[y];
  }
  return x;
}
vector<int> get(int x, int y) {
  vector<int> r(0);
  for (; x != y; x = fa[x]) {
    r.push_back(x);
  }
  r.push_back(y);
  return r;
}
vector<int> operator + (const vector<int> &a, const vector<int> &b) {
  vector<int> c(a);
  for (auto x : b) c.push_back(x);
  return c;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  memset(s, -1, sizeof s);
  for (int i = 1; i <= n; i++) if (!vis[i]) {
    v.clear();
    dfs(i, 0);
    int ok = 0;
    int A = 0, B = 0, S = 0, T = 0;
    for (int i = 0; i < (int) v.size() && !ok; i++) {
      for (int p = v[i].first; p != v[i].second; p = fa[p]) {
        if (~s[p]) {
          ok = 1;
          B = v[i].first, A = v[i].second;
          T = v[s[p]].first, S = v[s[p]].second;
          break;
        } else {
          s[p] = i;
        }
      }
    }
    if (!ok) {
      continue;
    }
    puts("YES");
    if (dep[A] > dep[S]) {
      swap(A, S);
      swap(B, T);
    }
    vector<int> a1, a2, a3;
    if (isfa(B, T)) {
      a1 = get(T, S);
      a2 = vector<int> {T, S};
      a3 = get(S, A) + get(B, T); reverse(a3.begin(), a3.end());
    } else if (isfa(T, B)) {
      a1 = get(B, S);
      a2 = get(S, A) + get(B, B); reverse(a2.begin(), a2.end());
      a3 = get(S, S) + get(T, B); reverse(a3.begin(), a3.end());
    } else {
      int W = lca(B, T);
      a1 = get(W, S);
      a2 = get(S, A) + get(B, W); reverse(a2.begin(), a2.end());
      a3 = get(S, S) + get(T, W); reverse(a3.begin(), a3.end());
    }
    printf("%d ", (int) a1.size());
    for (auto x : a1) printf("%d ", x);
    puts("");
    printf("%d ", (int) a2.size());
    for (auto x : a2) printf("%d ", x);
    puts("");
    printf("%d ", (int) a3.size());
    for (auto x : a3) printf("%d ", x);
    puts("");
    return 0;
  }
  puts("NO");
}
