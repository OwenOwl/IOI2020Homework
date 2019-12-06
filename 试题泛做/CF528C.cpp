#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, m, e_num = 1, deg[N], hed[N], ban[N << 1], to[N << 2], nxt[N << 2];
void adde(int x, int y) {
  to[++e_num] = y;
  nxt[e_num] = hed[x];
  hed[x] = e_num;
  to[++e_num] = x;
  nxt[e_num] = hed[y];
  hed[y] = e_num;
  ++deg[x];
  ++deg[y];
}
vector<int> cir;
void euler(int x) {
  for (int &e = hed[x]; e; e = nxt[e]) if (!ban[e >> 1]) {
    ban[e >> 1] = 1;
    euler(to[e]);
    cir.push_back(x);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    adde(x, y);
  }
  for (int i = 1, lst = 0; i <= n; i++) if (deg[i] & 1) {
    if (lst) {
      adde(lst, i);
      lst = 0;
      ++m;
    } else {
      lst = i;
    }
  }
  if (m & 1) adde(1, 1);
  euler(1);
  printf("%d\n", (int) cir.size());
  for (int i = 0; i < (int) cir.size(); i++) {
    if (i & 1) {
      printf("%d %d\n", cir[i], cir[(i + 1) % cir.size()]);
    } else {
      printf("%d %d\n", cir[(i + 1) % cir.size()], cir[i]);
    }
  }
}
