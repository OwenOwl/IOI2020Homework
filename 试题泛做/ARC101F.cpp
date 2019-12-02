#include <bits/stdc++.h>
using namespace std;

const int N = 100233, mod = 1000000007;
int n, m, p, x[N], y[N], uni[N];
pair<int, int> q[N];
int tr[N];
void add(int x, int y) {
  for (; x <= m; x += x & -x) {
    tr[x] = (tr[x] + y) % mod;
  }
}
int ask(int x) {
  int r = 1;
  for (; x; x -= x & -x) {
    r = (r + tr[x]) % mod;
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &y[i]);
  }
  sort(x + 1, x + 1 + n);
  sort(y + 1, y + 1 + m);
  for (int i = 1; i <= n; i++) {
    int t = (int) (upper_bound(y + 1, y + 1 + m, x[i]) - y);
    if (t == 1 || t == m + 1) continue;
    ++p;
    q[p].first = x[i] - y[t - 1];
    q[p].second = uni[p] = y[t] - x[i];
  }
  sort(uni + 1, uni + 1 + p);
  m = (int) (unique(uni + 1, uni + 1 + p) - uni - 1);
  sort(q + 1, q + 1 + p, [&](pair<int, int> &a, pair<int, int> &b){return a.first == b.first ? a.second > b.second : a.first < b.first;});
  n = (int) (unique(q + 1, q + 1 + p) - q - 1);
  for (int i = 1; i <= n; i++) {
    int t = (int) (lower_bound(uni + 1, uni + 1 + m, q[i].second) - uni);
    add(t, ask(t - 1));
  }
  printf("%d\n", ask(m));
}
